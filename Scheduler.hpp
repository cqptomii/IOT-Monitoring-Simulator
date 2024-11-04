//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SCHEDULER_HPP
#define TP_SCHEDULER_HPP
#include "Sensor/Sensor.hpp"
#include "Sensor/Sound.hpp"
#include "Sensor/Light.hpp"
#include "Sensor/Temperature.hpp"
#include "Sensor/Humidity.hpp"
#include "Server.hpp"
#include <memory>
#include <list>
#include <thread>
#include <atomic>
#include "Barrier.hpp"

class Scheduler {
private:
    std::shared_ptr<Server> server_ptr;

    std::list< std::unique_ptr<Sensor>> sensor_list;

    unsigned int interval;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_update;
    std::atomic<bool> is_running;

    std::vector<std::thread> thread_tasks;

    /**
     * @brief méthode qui organise le séquencement des capteurs. Permet d'appeler la fonction update sur l'ensemble des capteurs enregistré dans le scheduler
     * @param thread_id : identifiants des différents threads parcourant cette fonction : permet d'affecter des taches précises à chaque threads
     */
    void simulation();
    /**
     * @brief
     * @param thread_id : identifiants des différents threads
     */
    void runTasks();
    /**
     * @brief méthode qui permet d'associer un Server à notre Scheduler
     * @param server : pointeur partagée vers le server
     */
    void linkServer(const std::shared_ptr<Server>& server);
    /**
     * @brief méthode qui permet d'ajouter un capteur dans la liste du scheduler
     * @param sound_sensor : pointeur unique vers le capteur de son
     */
    void linkSensor(std::unique_ptr<Sensor> sensor);
    /**
     * @brief méthode permettant de savoir si le Scheduler est prêt à envoyer une requête aux capteurs
     * @return true / false
     */
    bool isReady();
public:
    /**
     * @brief Constructeur par default de la classe Scheduler
     */
    Scheduler();
    /**
     * @brief Constructeur de recopie de la classe Scheduler
     * effectue une copie profonde des attribut de scheduler
     *
     * @param scheduler : Scheduleur à recopier
     */
    Scheduler(const Scheduler& scheduler);
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
    Scheduler& operator=(const Scheduler& scheduler);
    /**
     * @brief Surcharge opérateur de sortie permettant d'envoyer au scheduler un server
     * @param server : server transmis au scheduler
     */
    void operator<<(const Server& server);
    /**
     * @brief Surcharge opérateur de sortie permettant d'envoyer au scheduler un capteur
     * @param sensor : capteur de son transmis au scheduler
     */
    void operator<<(std::unique_ptr<Sensor> s);

    /**
     * @brief méthode qui permet de lancer la simulation par le Scheduler
     * @return true / false
     */
    bool start();
    /**
     * @brief méthode qui permet d'arreter la simulation
     */
    void stop();
};


#endif //TP_SCHEDULER_HPP
