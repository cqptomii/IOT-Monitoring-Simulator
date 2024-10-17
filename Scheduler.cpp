//
// Created by tomfr on 15/09/2024.
//

#include "Scheduler.hpp"

Scheduler::Scheduler() : server_ptr(),sensor_list(),interval(5000),is_running(false), last_update(){}

Scheduler::Scheduler(const Scheduler &scheduler) : interval(scheduler.interval),last_update(scheduler.last_update) {
    if(scheduler.server_ptr){
        this->server_ptr = scheduler.server_ptr;
    }else{
        this->server_ptr.reset();
    }
    is_running.store(scheduler.is_running);
    for(const std::unique_ptr<Sensor> &sensor : scheduler.sensor_list){
        this->sensor_list.push_back(sensor->clone());
    }
}

Scheduler &Scheduler::operator=(const Scheduler& scheduler){
    if(this != &scheduler){
        if(scheduler.server_ptr)
            this->server_ptr = scheduler.server_ptr;
        else
            this->server_ptr.reset();

        this->last_update = scheduler.last_update;
        this->is_running.store(scheduler.is_running);

        for(const std::unique_ptr<Sensor> &s : scheduler.sensor_list){
            this->sensor_list.push_back(s->clone());
        }
    }
    return *this;
}
void Scheduler::operator<<(const Server& server) {
    linkServer(std::make_shared<Server>(server));
}
void Scheduler::operator<<(std::unique_ptr<Sensor> s){
    s->associed_server = this->server_ptr;
    linkSensor(std::move(s));
}

void Scheduler::linkServer(const std::shared_ptr<Server>& server) {
    if(server == nullptr)
        return;
    if(server != this->server_ptr){
        this->server_ptr = server;

    }
}
void Scheduler::linkSensor(std::unique_ptr<Sensor> sensor){
    if(sensor == nullptr)
        return;
    this->sensor_list.push_back(std::move(sensor));
}
void Scheduler::simulation() {
    if(isReady()){
        for(const std::unique_ptr<Sensor> &s : this->sensor_list){
            s->update();
        }
        last_update = std::chrono::high_resolution_clock::now();
    }
}
void Scheduler::runTasks() {
    try {
        while (is_running) {
            simulation();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }catch(std::exception& e){
        std::cerr << "Exception dans le thread - Fin du thread" << std::endl;
    }
}
bool Scheduler::start() {
    if(!this->server_ptr){
        std::cerr<< "ERROR - pas de server associe au scheduler" << std::endl;
        return false;
    }
    if(is_running) {
        return true;
    }

    is_running = true;

    thread_tasks.emplace_back([this]{
        runTasks();
    });

    thread_tasks.emplace_back([this]{
        while(is_running){
            this->server_ptr->useData();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });

    return true;
}

void Scheduler::stop() {
    is_running.store(false);

    for(std::thread& t : this->thread_tasks){
        if(t.joinable()){
            t.join();
        }
    }

    thread_tasks.clear();
}

bool Scheduler::isReady() {
    std::chrono::time_point<std::chrono::high_resolution_clock > currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::milli> duration(currentTime - this->last_update);


    return (duration.count() >= this->interval);
}

Scheduler::~Scheduler() {
    stop();
}
