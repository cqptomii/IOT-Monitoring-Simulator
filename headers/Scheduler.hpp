//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SCHEDULER_HPP
#define TP_SCHEDULER_HPP
#include "src/Sensor/Sensor.h"
#include "headers/Sound.hpp"
#include "headers/Light.hpp"
#include "headers/Temperature.hpp"
#include "headers/Humidity.hpp"
#include "headers/Server.hpp"
#include "headers/Barrier.hpp"
#include <memory>
#include <list>
#include <thread>
#include <atomic>
#include <QObject>

class Scheduler : public QObject{
    Q_OBJECT
private:
    Server *server_ptr;

    std::list< std::unique_ptr<Light> > l_sensor;
    std::list< std::unique_ptr<Humidity> > h_sensor;
    std::list< std::unique_ptr<Sound> > s_sensor;
    std::list< std::unique_ptr<Temperature> > t_sensor;

    unsigned int interval;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_update;
    std::atomic<bool> is_running;

    unsigned int thread_amount = 1;
    std::vector<std::thread> thread_tasks;
    std::unique_ptr<Barrier> scheduler_barrier;


    /**
     * @brief méthode qui organise le séquencement des capteurs. Permet d'appeler la fonction update sur l'ensemble des capteurs enregistré dans le scheduler
     * @param thread_id : identifiants des différents threads parcourant cette fonction : permet d'affecter des taches précises à chaque threads
     */
    void simulation(unsigned int thread_id);
    /**
     * @brief
     * @param thread_id : identifiants des différents threads
     */
    void runTasks(unsigned int thread_id);
    /**
     * @brief méthode qui appel la fonction update sur une des listes de capteurs en fonctions de de la variable thread-id
     * @param thread_id : identifiants des différents threads
     */
    void updateList(unsigned int thread_id);
    /**
     * @brief méthode qui permet d'associer un Server à notre Scheduler
     * @param server : pointeur partagée vers le server
     */
    void linkServer(Server *server);
    /**
     * @brief méthode qui permet d'ajouter un capteur de son dans la liste du Scheduler
     * @param sound_sensor : pointeur unique vers le capteur de son
     */
    void linkSensor(std::unique_ptr<Sound> sound_sensor);
    /**
     * @brief méthode qui permet d'ajouter un capteur d'humidité dans la liste du Scheduler
     * @param hum_sensor : pointeur unique vers le capteur d'humidité
     */
    void linkSensor(std::unique_ptr<Humidity> hum_sensor);
    /**
     * @brief méthode qui permet d'ajouter un capteur de temperature dans la liste du Scheduler
     * @param temp_sensor : pointeur unique vers le capteur de temperature
     */
    void linkSensor(std::unique_ptr<Temperature> temp_sensor);
    /**
     * @brief méthode qui permet d'ajouter un capteur de lumière dans la liste du Scheduler
     * @param light_sensor : pointeur unique vers le capteur de lumière
     */
    void linkSensor(std::unique_ptr<Light> light_sensor);
    /**
     * @brief méthode permettant de savoir si le Scheduler est prêt à envoyer une requête aux capteurs
     * @return true / false
     */
    bool isReady();
    void UpdateSensorDisplay(unsigned int sensor_type,bool server);
    void send_message_to_window(const QString& s);
public:

    /**
     * @brief Constructeur par default de la classe Scheduler
     */
    Scheduler(QObject *parent);
    /**
     * @brief Constructeur de recopie de la classe Scheduler
     * effectue une copie profonde des attribut de scheduler
     *
     * @param scheduler : Scheduleur à recopier
     */
    Scheduler(const Scheduler& scheduler) = delete;
    /**
     * @brief Destructeur de la classe Scheduler
     */
    ~Scheduler();
    /**
     * @brief Opérateur d'affectation de la classe Scheduler
     *  effectue une copie profonde des attributs de scheduler
     *
     * @param scheduler : Scheduler à copier
       */
    Scheduler& operator=(const Scheduler& scheduler) = delete;
    /**
     * @brief Surcharge opérateur de sortie permettant d'envoyer au scheduler un server
     * @param server : server transmis au scheduler
     */
    void operator<<(Server *server);
    /**
     * @brief Surcharge opérateur de sortie permettant d'envoyer au scheduler un capteur de son
     * @param sensor : capteur de son transmis au scheduler
     */
    void operator<<(const Sound& sensor);
    /**
     * @brief Surcharge opérateur de sortie permettant d'envoyer au scheduler un capteur de lumière
     * @param sensor : capteur de lumière transmis au scheduler
     */
    void operator<<(const Light& sensor);
    /**
     * @brief Surcharge opérateur de sortie permettant d'envoyer au scheduler un capteur d'humidité
     * @param sensor : capteur d'humidité transmis au scheduler
     */
    void operator<<(const Humidity& sensor);
    /**
     * @brief Sucharge opérateur de sortie permettant d'envoyer au scheduler un capteur de température
     * @param sensor : capteur de temperature transmis au scheduler
     */
    void operator<<(const Temperature& sensor);

    bool remove_sensor(const std::string name,const std::string type);
    /**
     * @brief méthode qui permet de lancer la simulation par le Scheduler
     * @return true / false
     */
    bool start();
    /**
     * @brief méthode qui permet d'arreter la simulation
     */
    void stop();
signals:
    void drawArrow(unsigned int sensor_type,bool server);
    void send_message(const QString &s);
};


#endif //TP_SCHEDULER_HPP
