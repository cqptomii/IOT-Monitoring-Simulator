//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_TEMPERATURE_HPP
#define TP_TEMPERATURE_HPP
#include "Sensor.h"

class Temperature : public Sensor<float>{
private:
    void readValue() override;
public:
    Temperature();
    Temperature(const Temperature& temp);
    Temperature(std::string sensor_name);
    ~Temperature() override = default;
    Temperature& operator=(const Temperature& temp);
};


#endif //TP_TEMPERATURE_HPP
