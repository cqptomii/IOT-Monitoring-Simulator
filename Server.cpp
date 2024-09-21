//
// Created by tomfr on 15/09/2024.
//

#include "Server.hpp"

Server::Server() : console_logs(true), file_logs(false) {
    server_log_file = std::filesystem::current_path();
    std::cout << server_log_file << std::endl;
}

Server::Server(const Server &server) = default;

Server::Server(bool write_console_logs, bool write_file_report) :console_logs(write_console_logs), file_logs(write_file_report) {
    server_log_file = std::filesystem::current_path();
    current_time = time(nullptr);
}

Server &Server::operator=(const Server& server) {
    console_logs = server.console_logs;
    server_log_file = server.server_log_file;
    file_logs = server.file_logs;
    current_time = server.current_time;
    return *this;
}



