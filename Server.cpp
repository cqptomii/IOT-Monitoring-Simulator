//
// Created by tomfr on 15/09/2024.
//

#include "Server.hpp"

Server::Server() : console_logs(true), file_report(false) {
    logfile_path = std::filesystem::current_path();
    std::cout << logfile_path << std::endl;
}

Server::Server(const Server &server) = default;

Server::Server(bool write_console_logs, bool write_file_report) :console_logs(write_console_logs), file_report(write_file_report) {
    logfile_path = std::filesystem::current_path();
}

Server &Server::operator=(const Server &server) {
    console_logs = server.console_logs;
    logfile_path = server.logfile_path;
    file_report = server.file_report;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Server &server) {

}

std::ostream &operator>>(std::ostream &os, const Server &server){

}
