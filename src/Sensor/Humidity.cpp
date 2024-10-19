//
// Created by tomfr on 15/09/2024.
//

#include "headers/Humidity.hpp"

Humidity::Humidity() : Sensor("H_sensor") {
    this->type = "Humidity";
    generateId();
}

Humidity::Humidity(const Humidity &hum) : Sensor(hum) {}

Humidity::Humidity(std::string sensor_name) : Sensor(std::move(sensor_name)) {
    this->type = "Humidity";
    generateId();
}
Humidity &Humidity::operator=(const Humidity &hum) {
    Sensor::operator=(hum);
    return *this;
}

void Humidity::readValue() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> distribution(0.0,100.0);

    this->data = distribution(generator);
}

void Humidity::send_data() {
    std::tuple<time_t,size_t,std::string, std::string , float> message(time(nullptr),ID,type,name,data);
    if(associed_server)
        *this->associed_server << message;
}

std::unique_ptr<Sensor> Humidity::clone() const {
    return std::make_unique<Humidity>(*this);
}
