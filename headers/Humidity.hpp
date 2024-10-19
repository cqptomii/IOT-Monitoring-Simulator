//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_HUMIDITY_HPP
#define TP_HUMIDITY_HPP
#include "src/Sensor/Sensor.hpp"

class Humidity : public Sensor{
private:
    float data;
    /**
     * @brief méthode qui permet de générer une valeur de type float entre 0 et 100.0
     */
    void readValue() override;
    void send_data() override;
public:
    /**
     * @brief Constructeur par default
     */
    Humidity();
    /**
     * @brief Constructeur par recopie 
     * @param hum : capteur d'humidité à recopier
     */
    Humidity(const Humidity& hum);
    /**
     * @brief Constructeur surchargé
     * @param sensor_name : nom donné au capteur
     */
    Humidity(std::string sensor_name);
    /**
     * @brief Destructeur par default
     */
    ~Humidity() override = default;
    /**
     * @brief opérateur d'affectation
     * @param hum : capteur à copier
     * @return référence vers l'objet courant
     */
    Humidity& operator=(const Humidity& hum);
    std::unique_ptr<Sensor> clone() const override;
};


#endif //TP_HUMIDITY_HPP
