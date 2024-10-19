//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_TEMPERATURE_HPP
#define TP_TEMPERATURE_HPP
#include "src/Sensor/Sensor.hpp"

class Temperature : public Sensor{
private:
    float data;
    /**
     * @brief méthode qui permet de générer une valeur de type float entre 8.5 et 27.0
     */
    void readValue() override;
    void send_data() override;
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
    Temperature(std::string sensor_name);
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
    std::unique_ptr<Sensor> clone() const override;
};


#endif //TP_TEMPERATURE_HPP
