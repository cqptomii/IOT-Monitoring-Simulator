//
// Created by tomfr on 15/09/2024.
//

#include "headers/Scheduler.hpp"
#include <QTimer>
#include <QDebug>

Scheduler::Scheduler(QObject *parent) : QObject(parent),server_ptr(),sensor_list(),interval(5000), last_update(),is_running(false){}
void Scheduler::operator<<(Server *server) {
    linkServer(server);
}
void Scheduler::operator<<(std::unique_ptr<Sensor> s){
    s->associed_server = this->server_ptr;
    linkSensor(std::move(s));
}
void Scheduler::linkServer(Server *server) {
    if(server != this->server_ptr){
        this->server_ptr = server;
        send_message_to_window("Ajout du server au Scheduler");
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
            UpdateSensorDisplay(s->type,true);
        }
        last_update = std::chrono::high_resolution_clock::now();
    }
}
void Scheduler::runTasks() {
    try {
        while (is_running) {
            simulation();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }catch(std::exception& e){
        qDebug() << "Exception dans le thread - Fin du thread";
    }
}
bool Scheduler::start() {
    if(!this->server_ptr){
        qDebug() << "ERROR - pas de server associe au scheduler" ;
        return false;
    }
    if(is_running) {
        return true;
    }
    qDebug() << "start";

    is_running = true;
    thread_tasks.emplace_back([this]{
        runTasks();
    });
    thread_tasks.emplace_back([this]{
        while(is_running){
            this->server_ptr->useData();
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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
    qDebug() << "Simulation end";
}

bool Scheduler::isReady() {
    std::chrono::time_point<std::chrono::high_resolution_clock > currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::milli> duration(currentTime - this->last_update);
    return (duration.count() >= this->interval);
}

Scheduler::~Scheduler() {
    stop();
}
bool Scheduler::remove_sensor(const std::string name,const std::string type){
    auto it = std::remove_if(sensor_list.begin(),sensor_list.end(),[&name,&type](const std::unique_ptr<Sensor>& s){
        return (s->name == name && s->type == type);
    });
    if(it != sensor_list.end()){
        sensor_list.erase(it,sensor_list.end());
        return true;
    }
    return false;
}

void Scheduler::UpdateSensorDisplay(const std::string& sensor_type,bool server){
    int type = 0;
    if(sensor_type == "Temperature"){
        type = 1;
    }else if(sensor_type == "Humidity"){
        type = 2;
    }else if(sensor_type == "Sound"){
        type = 3;
    }else if(sensor_type == "Light"){
        type = 4;
    }

    emit drawArrow(type,server);
}
void Scheduler::send_message_to_window(const QString &s){
    emit send_message(s);
}
