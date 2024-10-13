//
// Created by tomfr on 15/09/2024.
//

#include "headers/Scheduler.hpp"
#include <QTimer>
#include <QDebug>

Scheduler::Scheduler(QObject *parent) : QObject(parent),server_ptr(),l_sensor(),h_sensor(),s_sensor(),t_sensor(),interval(5000), last_update(),is_running(false){}
void Scheduler::operator<<(Server *server) {
    linkServer(server);
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

void Scheduler::linkServer(Server *server) {
    if(server != this->server_ptr){
        this->server_ptr = server;
        send_message_to_window("Ajout du server au Scheduler");
    }
}
void Scheduler::linkSensor(std::unique_ptr<Sound> sound_sensor) {
    sound_sensor->associed_server = this->server_ptr;
    this->s_sensor.push_back(std::move(sound_sensor));
    send_message_to_window("Ajout d'un capteur de son au Scheduler");
    qDebug() << "Add sensor" + this->s_sensor.back()->name;
}

void Scheduler::linkSensor(std::unique_ptr<Humidity> hum_sensor) {
    hum_sensor->associed_server = this->server_ptr;
    this->h_sensor.push_back(std::move(hum_sensor));
    send_message_to_window("Ajout d'un capteur d'Humidité au Scheduler");
    qDebug() << "Add sensor" + this->h_sensor.back()->name;
}
void Scheduler::linkSensor(std::unique_ptr<Temperature> temp_sensor) {
    temp_sensor->associed_server = this->server_ptr;
    this->t_sensor.push_back(std::move(temp_sensor));
    send_message_to_window("Ajout d'un capteur de température au Scheduler");
    qDebug() << "Add sensor" + this->t_sensor.back()->name;
}
void Scheduler::linkSensor(std::unique_ptr<Light> light_sensor) {
    light_sensor->associed_server = this->server_ptr;
    this->l_sensor.push_back(std::move(light_sensor));
    send_message_to_window("Ajout d'un capteur de lumière au Scheduler");
    qDebug() << "Add sensor" + this->l_sensor.back()->name;
}
void Scheduler::updateList(unsigned int thread_id){
    qDebug() << "envoie des données vers le server";
    switch (thread_id) {
        case 1: {
            if(t_sensor.size() == 0){
                UpdateSensorDisplay(1,false);
                break;
            }
            for (const std::unique_ptr<Temperature> &t: this->t_sensor) {
                t->update();
            }
            UpdateSensorDisplay(1,true);
            break;
        }
        case 2:{
            if(h_sensor.size() == 0){
                UpdateSensorDisplay(2,false);
                break;
            }
            for(const std::unique_ptr<Humidity> &h : this->h_sensor){
                h->update();
            }
            UpdateSensorDisplay(2,true);
            break;
        }
        case 3:{
            if(s_sensor.size() == 0){
                UpdateSensorDisplay(3,false);
                break;
            }
            for(const std::unique_ptr<Sound> &s : this->s_sensor){
                s->update();
            }
            UpdateSensorDisplay(3,true);
            break;
        }
        case 4:{
            if(l_sensor.size() == 0){
                UpdateSensorDisplay(4,false);
                break;
            }
            for(const std::unique_ptr<Light> &l : this->l_sensor){
                l->update();
            }
            UpdateSensorDisplay(4,true);
            break;
        }
        default:
            qDebug() << "Thread non reconnue "  << thread_id;
            break;
    }
}
void Scheduler::simulation(unsigned int thread_id) {
    if(isReady()){
        qDebug() << "Read sensor Data";
        if(thread_amount == 3){ // Si on ne dispose que de 3 threads un unique thread met à jour les listes
            updateList(1);
            updateList(2);
            updateList(3);
            updateList(4);
        }else{
            updateList(thread_id);  // Sinon chacun des 4 threads met à jour une des listes de capteurs selon son identifiant
        }
        //Synchronisation de tous les threads à la barrière avant de rafraichir le timer
        scheduler_barrier->wait();
        // if statement to ensure that the timer is updated once
        if(thread_id == 1){
            qDebug() << "update Scheduler Timer";
            last_update = std::chrono::high_resolution_clock::now();
        }
    }
}
void Scheduler::runTasks(unsigned int thread_id) {
    try {
        while (is_running) {
            simulation(thread_id);
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
    if(this->thread_amount < 3) // Minimal multithreading implementation statement
        thread_amount = 3;
    else if(this->thread_amount > 6) // General multithreading implementation statement
        thread_amount = 6;

    // initialisation de la Barrier pour synchroniser les threads gérant les capteurs
    this->scheduler_barrier = std::make_unique<Barrier>(thread_amount-2);

    is_running = true;
    for(unsigned int i = 1; i<=thread_amount - 2;++i){
        int currentID = i;
        thread_tasks.emplace_back([this,currentID]{
            runTasks(currentID);
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
    if(type == "Temperature"){
        auto it = std::remove_if(t_sensor.begin(), t_sensor.end(),
                                      [&name](const std::unique_ptr<Temperature>& sensor) {
                                          return sensor->name == name; // Si sensor name est bien le nom d'un capteur
                                      });
        if(it != t_sensor.end()){
            t_sensor.erase(it,t_sensor.end());
            return true;
        }
    }else if(type == "Humidity"){
        auto it = std::remove_if(h_sensor.begin(), h_sensor.end(),
                                      [&name](const std::unique_ptr<Humidity>& sensor) {
                                          return sensor->name == name; // Si sensor name est bien le nom d'un capteur
                                      });
        if (it != h_sensor.end()) {
            h_sensor.erase(it, h_sensor.end());
            return true;
        }
    }else if(type == "Sound"){
       auto it = std::remove_if(s_sensor.begin(), s_sensor.end(),
                                      [&name](const std::unique_ptr<Sound>& sensor) {
                                          return sensor->name == name; // Si sensor name est bien le nom d'un capteur
                                      });
        if (it != s_sensor.end()) {
            s_sensor.erase(it, s_sensor.end());
            return true;
        }
    }else if(type == "Ligth"){
        auto it = std::remove_if(l_sensor.begin(), l_sensor.end(),
                                      [&name](const std::unique_ptr<Light>& sensor) {
                                          return sensor->name == name; // Si sensor name est bien le nom d'un capteur
                                      });
        if (it != l_sensor.end()) {
            l_sensor.erase(it, l_sensor.end());
            return true;
        }

    }
    return false;
}

void Scheduler::UpdateSensorDisplay(unsigned int sensor_type,bool server){
    emit drawArrow(sensor_type,server);
}
void Scheduler::send_message_to_window(const QString &s){
    emit send_message(s);
}
