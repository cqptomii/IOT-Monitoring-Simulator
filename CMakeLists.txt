cmake_minimum_required(VERSION 3.27)
project(TP)

set(CMAKE_CXX_STANDARD 17)

add_executable(TP main.cpp
        Server.hpp
        Server.cpp
        Scheduler.cpp
        Scheduler.hpp
        Sensor/Sensor.h
        Sensor/Light.hpp
        Sensor/Light.cpp
        Sensor/Temperature.hpp
        Sensor/Temperature.cpp
        Sensor/Sound.hpp
        Sensor/Sound.cpp
        Sensor/Humidity.hpp
        Sensor/Humidity.cpp
)
