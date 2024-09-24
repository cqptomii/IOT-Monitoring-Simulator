//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SOUND_HPP
#define TP_SOUND_HPP
#include "Sensor.h"

class Sound : public Sensor<int>{
private:
    void readValue() override;
public:
    Sound();
    Sound(const Sound& s);
    Sound(std::string sensor_name);
    ~Sound() override = default;
    Sound& operator=(const Sound& s);
};


#endif //TP_SOUND_HPP
