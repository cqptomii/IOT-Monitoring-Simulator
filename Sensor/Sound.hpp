//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SOUND_HPP
#define TP_SOUND_HPP
#include "Sensor.hpp"

class Sound : public Sensor{
private:
    int data;
    /**
     * @brief méthode qui permet de générer une valeur de type int entre 0 et 120
     */
    void readValue() override;
    /**
     * #brief méthode virtuelle pure qui permet d'envoyer la valeur courante du capteur au serveur
     */
    void send_data() override;
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
    /**
     * @brief méthode virtuelle pure permettant de récupérer le pointeur unique de l'instance du capteur de son
     * @return instance du pointeur unique vers le capteur
     */
    std::unique_ptr<Sensor> clone() const override;
};


#endif //TP_SOUND_HPP
