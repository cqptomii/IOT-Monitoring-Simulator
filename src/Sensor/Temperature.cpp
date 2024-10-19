//
// Created by tomfr on 15/09/2024.
//

#include "headers/Temperature.hpp"

#include <utility>

Temperature::Temperature() :Sensor("T_sensor") {
    this->type = "Temperature";
    generateId();
}

Temperature::Temperature(const Temperature &temp) : Sensor(temp){}

Temperature::Temperature(std::string sensor_name) : Sensor(std::move(sensor_name)) {
    this->type = "Temperature";
    generateId();
}

Temperature &Temperature::operator=(const Temperature &temp) {
    Sensor::operator=(temp);
    return *this;
}

void Temperature::readValue() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> distribution(8.5,27.0);

    this->data = distribution(generator);
}

void Temperature::send_data() {
    std::tuple<time_t, size_t, std::string, std::string, float> message(time(nullptr), ID, type, name, data);
    if (associed_server)
        *this->associed_server << message;
}

std::unique_ptr<Sensor> Temperature::clone() const {
    return std::make_unique<Temperature>(*this);
}
