//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SENSOR_HPP
#define TP_SENSOR_HPP


class Sensor {
private:

public:
    /**
     * @brief Constructeur par default de la classe Sensor
     */
    Sensor();
    /**
     * @brief Constructeur par recopie de la classe Sensor
     *
     * @param sensor : capteur à recopier
     */
    Sensor(const Sensor& sensor);
    /**
     * @brief Destructeur de la classe Sensor
    */
    ~Sensor() =default ;
    /**
     * @brief Opérateur de copie de la classe Sensor
     *
     * @param sensor : capteur à copier
     */
    Sensor &operator=(const Sensor& sensor);
};


#endif //TP_SENSOR_HPP
