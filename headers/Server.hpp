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
#include <list>
#include <QObject>
#include <QDebug>

class Server : public QObject{
    Q_OBJECT
private:
    std::filesystem::path server_log_path;
    bool file_logs;
    bool console_logs;

    unsigned int interval;
    unsigned int count;

    // Conteneur permettant au server de stocker les valeurs reçu par les capteurs
    std::list<std::tuple<time_t ,size_t ,std::string,std::string, float>> temperature_values;
    std::list<std::tuple<time_t ,size_t ,std::string,std::string, float>> humidity_values;
    std::list<std::tuple<time_t ,size_t ,std::string,std::string, int>> sound_values;
    std::list<std::tuple<time_t ,size_t ,std::string,std::string, bool>> light_values;

    /**
     * @brief Fonction permettant de visualiser les données reçues des capteurs dans la console
     * @param data : Tuple contenant les données à écrire dans la console de logs
     */
    template<typename T>
    void consoleWrite(const std::tuple<time_t ,size_t ,std::string,std::string, T>& data){
        // Convertir les autres valeurs en QString
        QString sensorID = QString::number(std::get<1>(data));                      // Sensor ID (unsigned long long)
        QString sensorType = QString::fromStdString(std::get<2>(data));             // Sensor Type (std::string)
        QString sensorName = QString::fromStdString(std::get<3>(data));             // Sensor name (std::string)
        QString currentData = QString::number(std::get<4>(data));                   // Current data (float)

        // Concaténer tous les éléments
        QString str_time = sensorID + "    " +
                           sensorType + "    " +
                           sensorName + "    " +
                           currentData;

        send_data_to_window(str_time);
    }

    /**
     * @brief Fonction permettant de stockées les données des capteurs dans des fichiers de logs selon le type de capteurs
     * @param file : fichier dans lequel les données seront ecrites
     * @param data : Tuple contenant les données à ecrire dans le fichier de logs
     */
    template<typename T>
    void fileWrite(std::ostream& open_file ,const std::tuple<time_t ,size_t ,std::string,std::string, T> &data){
        this->writting_format(open_file,data);
    }

    /**
     * @brief affiche le paquet de données transmis par le capteurs dans l'ostream fournis selon un format prédéfinis :
     *       Date ID Type Nom Valeur
     * @param os : sortie vers laquelle les données sont écrites
     * @param data : paquets de données transmis qui doit être écrit
     */
    template<typename T>
    void writting_format(std::ostream& os,const std::tuple<time_t ,size_t ,std::string,std::string, T> &data){
        std::string str_time = ctime(&std::get<0>(data));

        str_time.pop_back(); // supprime le "\n"

        os << str_time << "    " << // current Time
                   std::get<1>(data) << "    " << // Sensor ID
                   std::get<2>(data) << "    " << // Sensor Type
                   std::get<3>(data) << "    " << // Senor name
                   std::get<4>(data) << std::endl; // current data
    }

    /**
     * @brief Methode appelant les différentes fonctions d'écriture de log selon les configurations du Server
     *
     * @param data : paquet de données transmis par le capteurs
     */
    template<typename T>
    void writeData(const std::tuple<time_t ,size_t ,std::string,std::string, T> &data){
        if(console_logs){
            consoleWrite(data);
        }
        if(file_logs){
            bool file_exist(true);
            // Création du dossier log server si non existant
            if(!std::filesystem::exists(server_log_path)){
                qDebug() << "Dossier inexistant : creation du dossier parent";
                if(!std::filesystem::create_directories(server_log_path)){
                    qDebug() << "Erreur lors de la creation du dossier";
                }
            }

            std::string sensor_logs_folder =(server_log_path / (std::get<2>(data) + "_" + std::get<3>(data) + ".csv")).string();
            qDebug() << sensor_logs_folder;
            // Creation du fichier log associé au capteur si non existant
            try {
                if(!std::filesystem::exists(sensor_logs_folder)){
                    file_exist = false;
                }
                std::ofstream log(sensor_logs_folder, std::ofstream::out | std::ofstream::app);

                log.exceptions(std::ofstream::failbit | std::ofstream::badbit); // active les exceptions failbit / badbit

                if(!file_exist){
                    log << "Date    ID    Type    Name    Value" << std::endl;
                }
                fileWrite(log, data);

                log.close();
            } catch (const std::ofstream::failure &e) {
                qDebug() << "Erreur lors de l'ouverture du fichier "<< e.what();
            }
        }
    }
public:
    void send_data_to_window(const QString &message);
    /**
     * @brief Constructeur par défault de la classe Server
     */
    explicit Server(QObject *parent);
    /**
     * @brief Constructeur par recopie de la classe Server
     * @param server : le serveur à recopier
     */
    Server(const Server& server) = delete;
    /**
     * @brief Constructeur permettant de choisir le mode de rapport
     * @param write_console_logs : permet d'activer l'affichage de logs dans la console
     * @param write_file_report  : permet d'activer la production de rapport texte
     */
    explicit Server(QObject *parent ,bool write_console_logs, bool write_file_report);

    /**
     * @brief Destructeur de la classe Server
     */
    ~Server() = default;
    /**
     * @brief Opérateur d'affectation de la classe Server
     * @param server : le server à recopier
     * @return une reference vers le server copié
     */
    Server& operator=(const Server& server) = delete;

    /**
     * @brief Opérateur d'entrée de données vers le server
     * @param data
     **/
    template<typename T>
    void operator<<(const std::tuple<time_t ,size_t ,std::string,std::string, T>& data) {
        ++count;
        if(std::is_same<T,int>::value){
            sound_values.push_back(data);
        }else if(std::is_same<T,bool>::value){
            light_values.push_back(data);
        }else if("Temperature" == std::get<3>(data)){
            temperature_values.push_back(data);
        }else{
            humidity_values.push_back(data);
        }
        qDebug() << "Server recieve sensor Data ";
    }
    /**
     * @brief Fonction qui demande au server d'afficher les données dans les sorties log.
     * L'affichage des données est gérer par le server : il choisit si il doit ou non afficher les données
     */
    void useData();
    /**
     * @brief Setter de l'attribut file_logs : permet d'activer l'écriture de log dans des fichiers annexes
     */
    void setFileLog(bool check);
    /**
     * @brief Setter de l'attribut file_logs : permet d'activer l'écriture de log dans des fichiers annexes
     */
    void setConsoleLog(bool check);
signals:
    void data_to_display(const QString& message);
};


#endif //TP_SERVER_HPP
