//
// Created by tomfr on 15/09/2024.
//

#include "headers/Sound.hpp"

#include <utility>

Sound::Sound() : Sensor<int>(){
    this->type = "Sound";
    generateId();
}

Sound::Sound(const Sound &s) : Sensor<int>(s) {
    this->type = s.type;
}

Sound::Sound(std::string sensor_name) : Sensor(std::move(sensor_name)) {
    this->type = "Sound";
    generateId();
}

Sound &Sound::operator=(const Sound &s) {
    Sensor<int>::operator=(s);
    return *this;
}

void Sound::readValue()  {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution distribution(0,120);

    this->data = distribution(generator);
}
