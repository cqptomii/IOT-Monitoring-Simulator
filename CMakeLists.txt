cmake_minimum_required(VERSION 3.27)
project(TP)

set(CMAKE_CXX_STANDARD 17)

add_executable(TP main.cpp
        Server.hpp
        Sensor.hpp
        Scheduler.cpp
        Server.cpp
        Sensor.cpp)
