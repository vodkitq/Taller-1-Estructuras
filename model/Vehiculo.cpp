
#include "Vehiculo.h"
#include <string>

// Implementación del constructor
Vehiculo::Vehiculo(std::string patente, int idUsuario, std::string modelo, int monto,
                   bool papelesAlDia, bool fallaTecnica, std::string mensaje) {
    this->patente = patente;
    this->idUsuario = idUsuario;
    this->modelo = modelo;
    this->monto = monto;
    this->papelesAlDia = papelesAlDia;
    this->fallaTecnica = fallaTecnica;
    this->mensaje = mensaje;
}

// Implementación de los Getters
std::string Vehiculo::getPatente() {
    return patente;
}

int Vehiculo::getIdUsuario() {
    return idUsuario;
}

std::string Vehiculo::getModelo() {
    return modelo;
}

int Vehiculo::getMonto() {
    return monto;
}

bool Vehiculo::getPapelesAlDia() {
    return papelesAlDia;
}

bool Vehiculo::getFallaTecnica() {
    return fallaTecnica;
}

std::string Vehiculo::getMensaje() {
    return mensaje;
}
