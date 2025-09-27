cmake_minimum_required(VERSION 4.0)
project(Taller_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller_1 main.cpp
        Sistema.cpp
        Sistema.h
        model/Usuario.cpp
        model/Usuario.h
        model/Vehiculo.cpp
        model/Vehiculo.h
        managers/NodoVehiculo.cpp
        managers/NodoVehiculo.h
        managers/ManejadorUsuarios.cpp
        managers/ManejadorUsuarios.h
        managers/ManejadorVehiculos.cpp
        managers/ManejadorVehiculos.h)
