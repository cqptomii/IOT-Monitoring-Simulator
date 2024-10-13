#include <iostream>
#include "Scheduler.hpp"

int main() {
    bool console_log = false, file_log = false, add = true;
    char temp;

    std::cout << "---" << std::endl << "Bienvenue sur le simulateur IOT" << std::endl << "---" << std::endl;

    Scheduler Mainprocess;

    std::cout << "Configuration du serveur :" << std::endl;

    // Configuration des logs de console
    do {
        std::cout << " Activer les logs de console (Y/N) : ";
        std::cin >> temp;
    } while (toupper(temp) != 'Y' && toupper(temp) != 'N');
    console_log = (toupper(temp) == 'Y');  // Conversion de la réponse en booléen

    // Configuration des logs de fichier
    do {
        std::cout << " Activer les logs de fichier (Y/N) : ";
        std::cin >> temp;
    } while (toupper(temp) != 'Y' && toupper(temp) != 'N');
    file_log = (toupper(temp) == 'Y');  // Conversion de la réponse en booléen

    Server server(console_log, file_log);
    Mainprocess << server;

    std::cout << "Ajout de Capteurs dans la simulation" << std::endl;
    do {
        std::string sensor_n;
        std::cout << "Donner le nom du capteur : ";
        std::cin >> sensor_n;

        std::cout << "Choisir le type de Capteur : T: température / H: humidité / S: sound / L: lumière : ";
        std::cin >> temp;

        switch (toupper(temp)) {
            case 'T': {
                Temperature addT(sensor_n);
                Mainprocess << addT;
                break;
            }
            case 'H': {
                Humidity addT(sensor_n);
                Mainprocess << addT;
                break;
            }
            case 'S': {
                Sound addT(sensor_n);
                Mainprocess << addT;
                break;
            }
            case 'L': {
                Light addT(sensor_n);
                Mainprocess << addT;
                break;
            }
            default:
                std::cout << "Type de capteur non reconnu." << std::endl;
                break;
        }

        do {
            std::cout << "Ajouter un autre capteur (Y/N) ? ";
            std::cin >> temp;
        } while (toupper(temp) != 'Y' && toupper(temp) != 'N');
        add = (toupper(temp) == 'Y');  // Si la réponse est 'Y', on continue d'ajouter des capteurs
    } while (add);

    // Démarrage de la simulation
    do {
        std::cout << "Voulez-vous lancer la simulation (Y/N) ? ";
        std::cin >> temp;
    } while (toupper(temp) != 'Y' && toupper(temp) != 'N');

    if (toupper(temp) == 'Y') {
        Mainprocess.start();
    }
    do {
        std::cout << "Voulez-vous stopper la simulation (Y/N) ? ";
        std::cin >> temp;
    } while (toupper(temp) != 'Y');
    if(temp){
        Mainprocess.stop();
    }
    return 0;
}