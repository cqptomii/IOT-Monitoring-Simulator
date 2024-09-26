//
// Created by tomfr on 15/09/2024.
//

#include "Server.hpp"

Server::Server() : console_logs(true), file_logs(false) {
    server_log_path = "../logs";
    current_time = time(nullptr);
}

Server::Server(const Server &server) = default;

Server::Server(bool write_console_logs, bool write_file_report) :console_logs(write_console_logs), file_logs(write_file_report) {
    server_log_path = "../logs";
    current_time = time(nullptr);
}

Server &Server::operator=(const Server& server) {
    console_logs = server.console_logs;
    server_log_path = server.server_log_path;
    file_logs = server.file_logs;
    current_time = server.current_time;
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



