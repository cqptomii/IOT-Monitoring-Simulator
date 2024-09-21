//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_HUMIDITY_HPP
#define TP_HUMIDITY_HPP
#include "Sensor.h"

class Humidity : public Sensor<float> {
private:
    float readValue() override;
public:
    Humidity();
    Humidity(const Humidity& hum);
    Humidity(std::string sensor_name);
    ~Humidity() override = default;
    Humidity& operator=(const Humidity& hum);
};


#endif //TP_HUMIDITY_HPP
