//
// Created by tomfr on 17/10/2024.
//
#include "Sensor.hpp"

Sensor::Sensor() : name("sensor"),read_interval(generateInterval(1000,2000)),type("default"),ID(),associed_server(nullptr){
    this->last_read = std::chrono::high_resolution_clock::now();
}
Sensor::Sensor(const Sensor &sensor) : ID(sensor.ID),name(sensor.name),type(sensor.type), read_interval(sensor.read_interval){
    this->associed_server = sensor.associed_server;
    last_read = std::chrono::high_resolution_clock::now();
}
Sensor::Sensor(std::string sensor_name) : name(std::move(sensor_name)), read_interval(1000), associed_server(nullptr),ID(0){
    last_read = std::chrono::high_resolution_clock::now();
}

Sensor &Sensor::operator=(const Sensor &sensor){
    if(this != &sensor){
        ID = sensor.ID;
        name = sensor.name;
        type = sensor.type;
        read_interval = sensor.read_interval;
        associed_server = sensor.associed_server;
    }
    return *this;
}

void Sensor::setIntervalRead(unsigned int interval) {
    {
        if(interval >=1000){
            this->read_interval = interval;
        }
    }
}

int Sensor::generateInterval(int min, int max) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<> distribution(min,max);
    return distribution(generator);
}

void Sensor::update() {
    if(execute()){
        this->send_data();
    }
}

bool Sensor::isReady() {
    std::chrono::time_point<std::chrono::high_resolution_clock > currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration(currentTime - this->last_read);

    return (duration.count() >= this->read_interval);
}

bool Sensor::execute() {
    if (isReady()){
        last_read = std::chrono::high_resolution_clock::now();
        readValue();
        return true;
    }

    return false;
}

void Sensor::generateId() {
    std::string id_unhashed = this->type;
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<> distribution(15, 9999);
    int value = distribution(generator);

    id_unhashed += std::to_string(value);
    std::hash<std::string> hash_id;
    this->ID = hash_id(id_unhashed);
}