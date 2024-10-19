//
// Created by tomfr on 15/09/2024.
//

#include "headers/Light.hpp"

#include <utility>

Light::Light() : Sensor("L_sensor") {
    this->type = "Light";
    generateId();
}

Light::Light(const Light &l) : Sensor(l){}

Light &Light::operator=(const Light &l) {
    Sensor::operator=(l);
    return *this;
}

Light::Light(std::string sensor_name) : Sensor(std::move(sensor_name)) {
    this->type = "Light";
    generateId();
}

void Light::readValue(){
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::bernoulli_distribution bool_distrib(0.5);

    this->data = bool_distrib(generator);
}

void Light::send_data() {
    std::tuple<time_t,size_t,std::string, std::string , bool> message(time(nullptr),ID,type,name,data);
    if(associed_server)
        *this->associed_server << message;
}

std::unique_ptr<Sensor> Light::clone() const {
    return std::make_unique<Light>(*this);
}
