//
// Created by tomfr on 15/09/2024.
//

#include "headers/Humidity.hpp"

Humidity::Humidity() : Sensor<float>("H_sensor") {
    this->type = "Humidity";
    generateId();
}

Humidity::Humidity(const Humidity &hum) : Sensor<float>(hum) {
    this->type = hum.type;
}

Humidity::Humidity(std::string sensor_name) : Sensor(std::move(sensor_name)) {
    this->type = "Humidity";
    generateId();
}
Humidity &Humidity::operator=(const Humidity &hum) {
    Sensor<float>::operator=(hum);
    return *this;
}

void Humidity::readValue() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> distribution(0.0,100.0);

    this->data = distribution(generator);
}
