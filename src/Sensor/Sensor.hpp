//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SENSOR_HPP
#define TP_SENSOR_HPP
#include <string>
#include <functional>
#include <utility>
#include <random>
#include <memory>
#include "headers/Server.hpp"

class Sensor {
private:
    unsigned int read_interval;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_read;

    /**
     * @brief méthode virtuelle pure qui permet de générer une valeur aléatoire en fonction du type de capteur
     */
    virtual void readValue() = 0;

    virtual void send_data() = 0;
    /**
     * @brief met à jour la valeur du capteur si le capteur est prêt à lire une valeur
     */
    bool execute();
    /**
     * @brief méthode qui vérifie si le capteur est prêt à lire une donnée
     * @return vrai si oui, faux sinon
     */
    bool isReady();

protected:
    size_t ID;
    std::string type;
    std::string name;
    Server *associed_server;
    /**
     * @brief simule le comportement dynamique du capteur en envoyant un message au server associé
     */
    void update();

    /**
     * @brief permet de générer une identifiant unique aléatoire avec l'aide de la bibliothèque random
     */
    void generateId();

    /**
     * @brief méthode permettant de générer l'interval de lecture des capteurs de manière aléatoire selon l'ordre de grandeur donnée
     * @param
     */
     virtual int generateInterval(int min, int max);

public:
    /**
     * @brief Constructeur par default de la classe Sensor
     */
    Sensor();
    /**
     * @brief Constructeur par recopie de la classe Sensor
     *        Copie profonde du unique_ptr<Server>
     * @param sensor : capteur à recopier
     */
    Sensor(const Sensor& sensor);

    /**
     * @brief Constructeur surchargé de la classe Sensor
     * @param sensor_name : nom attribué au capteur
     * @param interval : interval de temps entre chaque lecture de valeur
     */
    Sensor(std::string sensor_name);
    /**
     * @brief Destructeur de la classe Sensor
    */
    virtual ~Sensor() = default ;
    /**
     * @brief Opérateur de copie de la classe Sensor
     * @param sensor : capteur à copier
     * @return référence vers la copie du capteur
     */
     Sensor &operator=(const Sensor& sensor);
    /**
     * @brief méthode qui permet de configurer l'interval propre de chaque capteur
     * @param interval : interval modifié
     */
    void setIntervalRead(unsigned int interval);
    virtual std::unique_ptr<Sensor> clone() const = 0;
    
    friend class Scheduler;
};

#endif //TP_SENSOR_HPP
