//
// Created by tomfr on 15/09/2024.
//

#include "Server.hpp"

Server::Server() : console_logs(true), file_logs(false),interval(20),count(0){
    server_log_path = "../logs";
}

Server::Server(const Server &server) = default;

Server::Server(bool write_console_logs, bool write_file_report) :console_logs(write_console_logs), file_logs(write_file_report),interval(20),count(0) {
    server_log_path = "../logs";
}

Server &Server::operator=(const Server& server) {
    console_logs = server.console_logs;
    server_log_path = server.server_log_path;
    file_logs = server.file_logs;
    return *this;
}

void Server::enableFileLog() {
    if(this->file_logs)
        return;

    this->file_logs = true;
}
void Server::disableFileLog() {
    if(!this->file_logs)
        return;

    this->file_logs = false;
}
void Server::useData() {
    if(count>=interval){
        std::cout << " Affichage des dernières données obtenues : " << std::endl << std::endl;

       for(const auto & temperature_value : temperature_values){
           writeData(temperature_value);
       }
        for(const auto & humidity_value  : humidity_values){
            writeData(humidity_value);
        }
        for(const auto & sound_value : sound_values){
            writeData(sound_value);
        }
        for(const auto & light_value : light_values){
            writeData(light_value);
        }

        this->light_values.clear();
        this->humidity_values.clear();
        this->sound_values.clear();
        this->temperature_values.clear();
        this->count = 0;
    }
}



