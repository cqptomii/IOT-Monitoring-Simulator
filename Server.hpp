//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SERVER_HPP
#define TP_SERVER_HPP
#include <iostream>
#include <filesystem>
#include <ctime>
#include <string>
#include "Sensor/Sensor.h"

class Server {
private:
    std::filesystem::path logfile_path;
    bool file_report;
    bool console_logs;

    /**
     * @brief Fonction permettant de visualiser les données reçues des capteurs dans la console
     * @param os :
     * @param data :
     */
    template<typename T>
    void consoleWrite(std::ostream& os,T data){
        std::time_t current_time = std::time(nullptr);

        std::string dt = ctime(&current_time);

        std::cout << dt << std::endl << std::endl;
        std::cout << "Sensor : " << "    Value: " << data << std::endl;
    }
    /**
     * @brief Fonction permettant de stockées les données des capteurs dans des fichiers de logs selon le type de capteurs
     * @param file
     * @param data
     */
    template<typename T>
    void fileWrite(std::ofstream& file,T data){

    }
public:
    /**
     * @brief Constructeur par défault de la classe Server
     */
    Server();
    /**
     * @brief Constructeur par recopie de la classe Server
     * @param server : le serveur à recopier
     */
    Server(const Server& server);

    /**
     * @brief Constructeur permettant de choisir le mode de rapport
     * @param write_console_logs : permet d'activer l'affichage de logs dans la console
     * @param write_file_report  : permet d'activer la production de rapport texte
     */
    Server(bool write_console_logs, bool write_file_report);
    /**
     * @brief Destructeur de la classe Server
     */
    virtual ~Server() = default;
    /**
     * @brief Opérateur d'affectation de la classe Server
     * @param server : le server à recopier
     * @return une reference vers le server copié
     */
    Server& operator=(const Server& server);
    friend std::ostream& operator<<(std::ostream& os, const Server& server);
    friend std::ostream& operator>>(std::ostream& os, const Server& server);
};


#endif //TP_SERVER_HPP
