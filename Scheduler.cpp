//
// Created by tomfr on 15/09/2024.
//

#include "Scheduler.hpp"

Scheduler::Scheduler() : server_ptr(),l_sensor(),s_sensor(),h_sensor(),t_sensor(),interval(5000),is_running(false), last_update(){}

Scheduler::Scheduler(const Scheduler &scheduler) : interval(scheduler.interval),last_update(scheduler.last_update) {
    if(scheduler.server_ptr){
        this->server_ptr = scheduler.server_ptr;
    }else{
        this->server_ptr.reset();
    }
    is_running.store(scheduler.is_running);
    for(const std::unique_ptr<Sound> &tempS : scheduler.s_sensor){
        this->s_sensor.push_back(std::make_unique<Sound>(*tempS));
    }
    for(const std::unique_ptr<Light> &tempL : scheduler.l_sensor){
        this->l_sensor.push_back(std::make_unique<Light>(*tempL));
    }
    for(const std::unique_ptr<Humidity> &tempH : scheduler.h_sensor){
        this->h_sensor.push_back(std::make_unique<Humidity>(*tempH));
    }
    for(const std::unique_ptr<Temperature> &tempT : scheduler.t_sensor){
        this->t_sensor.push_back(std::make_unique<Temperature>(*tempT));
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

        for(const std::unique_ptr<Sound> &tempS : scheduler.s_sensor){
            this->s_sensor.push_back(std::make_unique<Sound>(*tempS));
        }
        for(const std::unique_ptr<Light> &tempL : scheduler.l_sensor){
            this->l_sensor.push_back(std::make_unique<Light>(*tempL));
        }
        for(const std::unique_ptr<Humidity> &tempH : scheduler.h_sensor){
            this->h_sensor.push_back(std::make_unique<Humidity>(*tempH));
        }
        for(const std::unique_ptr<Temperature> &tempT : scheduler.t_sensor){
            this->t_sensor.push_back(std::make_unique<Temperature>(*tempT));
        }
    }
    return *this;
}
void Scheduler::operator<<(const Server& server) {
    linkServer(std::make_shared<Server>(server));
}
void Scheduler::operator<<(const Light &sensor) {
    linkSensor(std::make_unique<Light>(sensor));
}
void Scheduler::operator<<(const Sound &sensor) {
    linkSensor(std::make_unique<Sound>(sensor));
}
void Scheduler::operator<<(const Humidity &sensor) {
    linkSensor(std::make_unique<Humidity>(sensor));
}
void Scheduler::operator<<(const Temperature &sensor) {
    linkSensor(std::make_unique<Temperature>(sensor));
}

void Scheduler::linkServer(const std::shared_ptr<Server>& server) {
    if(server == nullptr)
        return;
    if(server != this->server_ptr){
        this->server_ptr = server;

    }
}

void Scheduler::linkSensor(std::unique_ptr<Sound> sound_sensor) {
    sound_sensor->associed_server = this->server_ptr;
    this->s_sensor.push_back(std::move(sound_sensor));
}

void Scheduler::linkSensor(std::unique_ptr<Humidity> hum_sensor) {
    hum_sensor->associed_server = this->server_ptr;
    this->h_sensor.push_back(std::move(hum_sensor));
}
void Scheduler::linkSensor(std::unique_ptr<Temperature> temp_sensor) {
    temp_sensor->associed_server = this->server_ptr;
    this->t_sensor.push_back(std::move(temp_sensor));
}
void Scheduler::linkSensor(std::unique_ptr<Light> light_sensor) {
    light_sensor->associed_server = this->server_ptr;
    this->l_sensor.push_back(std::move(light_sensor));
}

void Scheduler::simulation(unsigned int thread_id) {
    if(isReady()){
        switch (thread_id) {
            case 5: {
                last_update = std::chrono::high_resolution_clock::now();
                for (const std::unique_ptr<Light> &l: this->l_sensor) {
                    l->update();
                }
                break;
            }
            case 4:{
                for(const std::unique_ptr<Sound> &s : this->s_sensor){
                    s->update();
                }
                break;
            }
            case 3:{
                for(const std::unique_ptr<Humidity> &h : this->h_sensor){
                    h->update();
                }
                break;
            }
            case 2:{
                for(const std::unique_ptr<Temperature> &t : this->t_sensor){
                    t->update();
                }
                break;
            }
            default:
                std::cerr << "Thread non reconnue " << std::this_thread::get_id()  << " " <<thread_id<< std::endl;
                break;
        }
    }
}
void Scheduler::runTasks(unsigned int thread_id) {
    try {
        while (is_running) {
            simulation(thread_id);
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
    if(is_running){
        return true;
    }
    is_running = true;
    for(int i = 1; i<=NB_THREADS_SCHEDULER;++i){
        thread_tasks.emplace_back([this, &i]{
            runTasks(i);
        });
    }
    thread_tasks.emplace_back([this]{
        while(is_running){
            this->server_ptr->useData();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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
