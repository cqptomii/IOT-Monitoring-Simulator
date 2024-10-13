//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SENSOR_H
#define TP_SENSOR_H
#include <string>
#include <functional>
#include <utility>
#include <random>
#include <memory>
#include "../Server.hpp"

template<typename T>
class Sensor {
private:
    size_t ID;
    std::string name;
    std::shared_ptr<Server> associed_server;


    unsigned int read_interval;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_read;

    /**
     * @brief méthode virtuelle pure qui permet de générer une valeur aléatoire en fonction du type de capteur
     */
    virtual void readValue() = 0;
    /**
     * @brief met à jour la valeur du capteur si le capteur est prêt à lire une valeur
     */
    bool execute(){
        if (isReady()){
            last_read = std::chrono::high_resolution_clock::now();
            readValue();
            return true;
        }

        return false;
    }
    /**
     * @brief méthode qui vérifie si le capteur est prêt à lire une donnée
     * @return vrai si oui, faux sinon
     */
    bool isReady(){
        std::chrono::time_point<std::chrono::high_resolution_clock > currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration(currentTime - this->last_read);

        return (duration.count() >= this->read_interval);
    }

protected:
    T data;
    std::string type;
    /**
     * @brief simule le comportement dynamique du capteur en envoyant un message au server associé
     */
    void update(){
        if(execute()){
            std::tuple<time_t,size_t,std::string, std::string , T> message(time(nullptr),ID,type,name,data);
            if(associed_server)
                *this->associed_server << message;
        }
    }

    /**
     * @brief permet de générer une identifiant unique aléatoire avec l'aide de la bibliothèque random
     */
    void generateId(){
        std::string id_unhashed = this->type;
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<> distribution(15, 9999);
        int value = distribution(generator);

        id_unhashed += std::to_string(value);
        std::hash<std::string> hash_id;
        this->ID = hash_id(id_unhashed);
    }

    /**
     * @brief méthode permettant de générer l'interval de lecture des capteurs de manière aléatoire selon l'ordre de grandeur donnée
     * @param
     */
     int generateInterval(int min, int max){
         std::random_device rd;
         std::default_random_engine generator(rd());
         std::uniform_int_distribution<> distribution(min,max);
         return distribution(generator);
     }

public:
    /**
     * @brief Constructeur par default de la classe Sensor
     */
    Sensor() : name("sensor"),read_interval(generateInterval(1000,2000)),data(),type("default"),ID(),associed_server(nullptr){
        this->last_read = std::chrono::high_resolution_clock::now();
    }
    /**
     * @brief Constructeur par recopie de la classe Sensor
     *        Copie profonde du unique_ptr<Server>
     * @param sensor : capteur à recopier
     */
    Sensor(const Sensor& sensor) : ID(sensor.ID),name(sensor.name),type(sensor.type),data(sensor.data), read_interval(sensor.read_interval){
        this->associed_server = sensor.associed_server;
        last_read = std::chrono::high_resolution_clock::now();
    }

    /**
     * @brief Constructeur surchargé de la classe Sensor
     * @param sensor_name : nom attribué au capteur
     * @param interval : interval de temps entre chaque lecture de valeur
     */
    Sensor(std::string sensor_name) : name(std::move(sensor_name)), read_interval(1000), associed_server(nullptr),ID(0){
        last_read = std::chrono::high_resolution_clock::now();
    }
    /**
     * @brief Destructeur de la classe Sensor
    */
    virtual ~Sensor() = default ;
    /**
     * @brief Opérateur de copie de la classe Sensor
     * @param sensor : capteur à copier
     * @return référence vers la copie du capteur
     */
     Sensor &operator=(const Sensor& sensor){
        if(this != &sensor){
            ID = sensor.ID;
            name = sensor.name;
            type = sensor.type;
            read_interval = sensor.read_interval;
            associed_server = sensor.associed_server;
        }
        return *this;
    }
    /**
     * @brief méthode qui permet de configurer l'interval propre de chaque capteur
     * @param interval : interval modifié
     */
    void setIntervalRead(unsigned int interval){
        if(interval >=1000){
            this->read_interval = interval;
        }
    }

    friend class Scheduler;
};

#endif //TP_SENSOR_H
