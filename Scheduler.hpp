//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SCHEDULER_HPP
#define TP_SCHEDULER_HPP
#include "Sensor/Sensor.h"
#include "Sensor/Sound.hpp"
#include "Sensor/Light.hpp"
#include "Sensor/Temperature.hpp"
#include "Sensor/Humidity.hpp"
#include "Server.hpp"
#include <memory>
#include <list>
#include <thread>
#include <atomic>

#define NB_THREADS_SCHEDULER 4

class Scheduler {
private:
    std::shared_ptr<Server> server_ptr;

    std::list< std::unique_ptr<Light> > l_sensor;
    std::list< std::unique_ptr<Humidity> > h_sensor;
    std::list< std::unique_ptr<Sound> > s_sensor;
    std::list< std::unique_ptr<Temperature> > t_sensor;

    unsigned int interval;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_update;

    std::atomic<bool> is_running;
    std::vector<std::thread> thread_tasks;
    /**
     * @brief methode qui organise le sequencement des capteurs. Permet d'appeler la fonction update sur l'ensemble des capteurs enregistré dans le scheduler
     *
     */
    void simulation(unsigned int thread_id);
    void runTasks(unsigned int thread_id);
    void linkServer(const std::shared_ptr<Server>& server);
    void linkSensor(std::unique_ptr<Sound> sound_sensor);
    void linkSensor(std::unique_ptr<Humidity> hum_sensor);
    void linkSensor(std::unique_ptr<Temperature> temp_sensor);
    void linkSensor(std::unique_ptr<Light> light_sensor);
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
     * @brief Suchage opérateur de sortie permettant d'envoyer au scheduler un server
     * @param server : server transmis au scheduler
     */
    void operator<<(const Server& server);
    void operator<<(const Sound& sensor);
    void operator<<(const Light& sensor);
    void operator<<(const Humidity& sensor);
    void operator<<(const Temperature& sensor);


    bool start();
    void stop();
};


#endif //TP_SCHEDULER_HPP
