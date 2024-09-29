//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_LIGHT_HPP
#define TP_LIGHT_HPP
#include "Sensor.h"
class Light : public Sensor<bool>{
private:
    /**
     * @brief méthode qui permet de générer une valeur aléatoire de type bool
     */
    void readValue() override;
public:
    /**
     * @brief Constructeur par default de la classe
     */
    Light();
    /**
     * @brief Constructeur de recopie de la classe
     * @param l : capteur à recopier
     */
    Light(const Light& l);
    /**
     * @brief Constructeur surchargé de la classe
     * @param sensor_name : nom donné au sensor
     */
    Light(std::string sensor_name);
    /**
     * @brief Destructeur par default de la classe
     */
    ~Light() override = default;
    /**
     * @brief Operateur d'affectation
     * @param l : capteur à copier
     * @return référence vers l'objet courant
     */
    Light& operator=(const Light& l);
};


#endif //TP_LIGHT_HPP
