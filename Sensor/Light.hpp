//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_LIGHT_HPP
#define TP_LIGHT_HPP
#include "Sensor.h"
class Light : public Sensor<bool>{
private:
    bool readValue() override;
public:
    Light();
    Light(const Light& l);
    Light(std::string sensor_name);
    ~Light() override = default;
    Light& operator=(const Light& l);
};


#endif //TP_LIGHT_HPP
