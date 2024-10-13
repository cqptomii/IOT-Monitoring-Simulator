//
// Created by tomfr on 15/09/2024.
//

#include "headers/Temperature.hpp"

#include <utility>

Temperature::Temperature() :Sensor<float>() {
    this->type = "Temperature";
    generateId();
}

Temperature::Temperature(const Temperature &temp) : Sensor<float>(temp){
    this->type = temp.type;
}

Temperature::Temperature(std::string sensor_name) : Sensor(std::move(sensor_name)) {
    this->type = "Temperature";
    generateId();
}

Temperature &Temperature::operator=(const Temperature &temp) {
    Sensor<float>::operator=(temp);
    return *this;
}

void Temperature::readValue() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> distribution(8.5,27.0);

    this->data = distribution(generator);
}
