//
// Created by tomfr on 15/09/2024.
//

#ifndef TP_SERVER_HPP
#define TP_SERVER_HPP
#include <iostream>
#include <filesystem>
class Server {
private:
    std::filesystem::path log_path;

    /**
     * @brief Fonction permettant de visualiser les données reçues des capteurs dans la console
     */
    void consoleWrite();
    /**
     * @brief Fonction permettant de stockées les données des capteurs dans des fichiers de logs selon le type de capteurs
     */
    void fileWrite();
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
     * @brief Destructeur de la classe Server
     */
    ~Server() = default;
    /**
     * @brief Opérateur d'affectation de la classe Server
     * @param server : le server à recopier
     * @return une reference vers le server copié
     */
    Server& operator=(const Server& server);
};


#endif //TP_SERVER_HPP
