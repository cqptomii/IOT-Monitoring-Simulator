//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_TEMPERATURE_HPP
#define TP_TEMPERATURE_HPP
#include "src/Sensor/Sensor.h"

class Temperature : public Sensor<float>{
private:
    /**
     * @brief méthode qui permet de générer une valeur de type float entre 8.5 et 27.0
     */
    void readValue() override;
public:
    /**
     * @brief Constructeur par default
     */
    Temperature();
    /**
     * @brief Constructeur par recopie
     * @param temp : capteur de température à recopier
     */
    Temperature(const Temperature& temp);
    /**
     * @brief Constructeur surchargé de la classe
     * @param sensor_name : nom donné au capteur
     */
    Temperature(const std::string sensor_name);
    /**
     * @brief Destructeur par default
     */
    ~Temperature() override = default;
    /**
     * @brief opérateur d'affectation
     * @param temp : capteur de température à copier
     * @return référence vers l'objet courant
     */
    Temperature& operator=(const Temperature& temp);
};


#endif //TP_TEMPERATURE_HPP
