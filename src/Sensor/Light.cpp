//
// Created by tomfr on 15/09/2024.
//

#include "headers/Light.hpp"

#include <utility>

Light::Light() : Sensor<bool>("L_sensor") {
    this->type = "Light";
    generateId();
}

Light::Light(const Light &l) : Sensor<bool>(l){
    this->type = l.type;
}

Light &Light::operator=(const Light &l) {
    Sensor<bool>::operator=(l);
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
