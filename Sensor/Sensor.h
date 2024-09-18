//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SENSOR_H
#define TP_SENSOR_H
#include <string>
#include <functional>
#include "../Server.hpp"

template<typename T>
class Sensor {
private:
    size_t ID;
    std::string name;
    std::string type;
    Server *associed_server;


    unsigned int read_interval;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_read;

protected:
    T data;
public:
    /**
     * @brief Constructeur par default de la classe Sensor
     */
    Sensor(){

    }
    /**
     * @brief Constructeur par recopie de la classe Sensor
     *
     * @param sensor : capteur à recopier
     */
    Sensor(const Sensor& sensor){

    }
    /**
     * @brief Destructeur de la classe Sensor
    */
    virtual ~Sensor() =default ;
    /**
     * @brief Opérateur de copie de la classe Sensor
     *
     * @param sensor : capteur à copier
     */
    Sensor &operator=(const Sensor& sensor){
        return *this;
    }

    void updtate();
    void execute();



};


#endif //TP_SENSOR_H
