//
// Created by tomfr on 15/09/2024.
//

#include "Temperature.hpp"

#include <utility>

Temperature::Temperature() :Sensor<float>() {
    this->type = "Temperature";
    generateId();
}

Temperature::Temperature(const Temperature &temp) : Sensor<float>(temp){}

Temperature::Temperature(std::string sensor_name) : Sensor(std::move(sensor_name)) {
    this->type = "Temperature";
    generateId();
}

Temperature &Temperature::operator=(const Temperature &temp) {
    Sensor<float>::operator=(temp);
    return *this;
}

float Temperature::readValue() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> distribution(8.5,27.0);

    return distribution(generator);
}
