#include <iostream>
#include <stdlib.h>
#include "Scheduler.hpp"

int main(int argc,char *argv[]) {
    bool console_log = false, file_log = false, add = true;
    char temp;
    std::string argument;
    for (int i = 1; i < argc; i++) {
        argument = argv[i];
        if (argument == "-l" || argument == "--log") {
            file_log = true;
        } else if (argument == "-c" || argument == "--console") {
            console_log = true;
        } else if (argument == "-v" || argument == "--version") {
            std::cout << "AP4A Project - v1.0" << std::endl;
            std::cout << "Compilation date : " << __DATE__ << " " << __TIME__ << std::endl;
            return 0;
        } else if (argument == "-h" || argument == "--help") {
            std::cout << "Usage : " << argv[0] << " [options]\n\n"
                      << "Options : -h, --help      Print this help manual.\n"
                      << "          -v, --version   Print program's version and compilation date.\n"
                      << "          -l, --log       Turn on writing on log file.\n"
                      << "          -c, --console   Turn on console writing." << std::endl;
            return 0;
        }
    }
    std::cout << "---" << std::endl << "Bienvenue sur le simulateur IOT" << std::endl << "---" << std::endl;

    Scheduler Mainprocess;
    Server server(console_log, file_log);

    Mainprocess << server;

    do {
        std::cout << "Ajout de Capteurs dans la simulation" << std::endl;
        std::string sensor_n;
        std::cout << "Donner le nom du capteur : ";
        std::cin >> sensor_n;

        std::cout << "Choisir le type de Capteur : T: temperature - H: humidite - S: son - L: lumiere" << std::endl; ;
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
        system("cls");
    } while (add);

    // Démarrage de la simulation
    do {
        std::cout << "Voulez-vous lancer la simulation (Y/N) ? " << std::endl;
        std::cin >> temp;
    } while (toupper(temp) != 'Y' && toupper(temp) != 'N');

    if (toupper(temp) == 'Y') {
        system("cls");
        std::cout << "----Début de la simlation----" << std::endl;
        Mainprocess.start();
        do {
            std::cout << "Entrez Y pour stopper la simulation ";
            std::cin >> temp;
        } while (toupper(temp) != 'Y');
    }
    if(temp){
        Mainprocess.stop();
    }
    return 0;
}