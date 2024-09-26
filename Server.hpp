//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SERVER_HPP
#define TP_SERVER_HPP
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <string>
class Server {
private:
    std::filesystem::path server_log_path;
    bool file_logs;
    bool console_logs;
    std::time_t current_time;

    /**
     * @brief Fonction permettant de visualiser les données reçues des capteurs dans la console
     * @param data : Tuple contenant les données à ecrire dans la console de logs
     */
    template<typename T>
    void consoleWrite(const std::tuple<size_t ,std::string,std::string, T>& data){
        this->writting_format(std::cout,data);
    }

    /**
     * @brief Fonction permettant de stockées les données des capteurs dans des fichiers de logs selon le type de capteurs
     * @param file : fichier dans lequel les données seront ecrites
     * @param data : Tuple contenant les données à ecrire dans le fichier de logs
     */
    template<typename T>
    void fileWrite(std::ostream& open_file ,const std::tuple<size_t ,std::string,std::string, T> &data){
        this->writting_format(open_file,data);
    }

    /**
     * @brief write_data
     * @param os :
     * @param data :
     */
    template<typename T>
    void writting_format(std::ostream& os,const std::tuple<size_t ,std::string,std::string, T> &data){
        current_time = time(nullptr);
        std::string str_time = ctime(&current_time);

        str_time.pop_back(); // supprime le "\n"

        os << str_time << " " << // current Time
                   std::get<0>(data) << " " << // Sensor ID
                   std::get<1>(data) << " " << // Sensor Type
                   std::get<2>(data) << " " << // Senor name
                   std::get<3>(data) << std::endl; // current data
    }

    /**
     * @brief write_data
     */
    template<typename T>
    void writeData(const std::tuple<size_t ,std::string,std::string, T> &data){
        if(console_logs){
            consoleWrite(data);
        }
        if(file_logs){
            bool file_exist(true);
            // Création du dossier log server si non existant
            if(!std::filesystem::exists(server_log_path)){
                std::cout << "Dossier inexistant : creation du dossier parent" << std::endl;
                if(!std::filesystem::create_directories(server_log_path)){
                    std::cerr << "Erreur lors de la creation du dossier" << std::endl;
                }
            }

            std::string sensor_logs_folder =(server_log_path / (std::get<1>(data) + "_" + std::get<2>(data) + ".txt")).string();
            std::cout << sensor_logs_folder;
            // Creation du fichier log associé au capteur si non existant
            try {
                if(!std::filesystem::exists(sensor_logs_folder)){
                    file_exist = false;
                }
                std::ofstream log(sensor_logs_folder, std::ofstream::out | std::ofstream::app);

                log.exceptions(std::ofstream::failbit | std::ofstream::badbit); // active les exceptions failbit / badbit

                if(!file_exist){
                    log << "Date ID Type Name Value" << std::endl;
                }
                fileWrite(log, data);

                log.close();
            } catch (const std::ofstream::failure &e) {
                std::cerr << "Erreur lors de l'ouverture du fichier "<< e.what() << std::endl;
            }


        }
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
    ~Server() = default;
    /**
     * @brief Opérateur d'affectation de la classe Server
     * @param server : le server à recopier
     * @return une reference vers le server copié
     */
    Server& operator=(const Server& server);

    /**
     * @brief Opérateur d'entrée de données vers le server
     * @param data
     **/
    template<typename T>
    void operator<<(const std::tuple<size_t ,std::string,std::string, T>& data) {
        this->writeData(data);
    }
    void enableFileLog();
    void disableFileLog();
};


#endif //TP_SERVER_HPP
