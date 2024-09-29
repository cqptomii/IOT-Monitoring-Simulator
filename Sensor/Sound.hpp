//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SOUND_HPP
#define TP_SOUND_HPP
#include "Sensor.h"

class Sound : public Sensor<int>{
private:
    /**
     * @brief méthode qui permet de générer une valeur de type int entre 0 et 120
     */
    void readValue() override;
public:
    /**
     * @brief Constructeur par default de la classe
     */
    Sound();
    /**
     * @brief Constructeur par recopie
     * @param s : capteur de son à recopier
     */
    Sound(const Sound& s);
    /**
     * @brief Constructeur surchargé
     * @param sensor_name : nom donnée au capteur crée
     */
    Sound(std::string sensor_name);
    /**
     * @brief destructeur par default de la classe
     */
    ~Sound() override = default;
    /**
     * @brief opérateur d'affectation
     * @param s : Capteur de son à copier
     * @return référence vers l'objet courant
     */
    Sound& operator=(const Sound& s);
};


#endif //TP_SOUND_HPP
