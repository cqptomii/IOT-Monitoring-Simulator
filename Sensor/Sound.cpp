//
// Created by tomfr on 15/09/2024.
//

#include "Sound.hpp"

#include <utility>

Sound::Sound() : Sensor("S_sensor"){
    this->type = "Sound";
    generateId();
}

Sound::Sound(const Sound &s) : Sensor(s) {
    this->data = s.data;
}

Sound::Sound(std::string sensor_name) : Sensor(std::move(sensor_name)) {
    this->type = "Sound";
    generateId();
}

Sound &Sound::operator=(const Sound &s) {
    Sensor::operator=(s);
    return *this;
}

void Sound::readValue()  {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution distribution(0,120);

    this->data = distribution(generator);
}

void Sound::send_data() {
    std::tuple<time_t,size_t,std::string, std::string , int> message(time(nullptr),ID,type,name,data);
    if(associed_server)
        *this->associed_server << message;
}

std::unique_ptr<Sensor> Sound::clone() const {
    return std::make_unique<Sound>(*this);
}
