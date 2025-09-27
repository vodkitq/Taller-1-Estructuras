
#include "Vehiculo.h"
#include <string>

// Implementación del constructor
Vehiculo::Vehiculo(std::string patente, int idUsuario, std::string modelo, int monto,
                   bool papelesAlDia, bool fallaTecnica, std::string mensaje)
    : patente(patente), idUsuario(idUsuario), modelo(modelo), monto(monto),
      papelesAlDia(papelesAlDia), fallaTecnica(fallaTecnica), mensaje(mensaje) {
}

// Implementación de los Getters
std::string Vehiculo::getPatente() const {
    return patente;
}

int Vehiculo::getIdUsuario() const {
    return idUsuario;
}

std::string Vehiculo::getModelo() const {
    return modelo;
}

int Vehiculo::getMonto() const {
    return monto;
}

bool Vehiculo::getPapelesAlDia() const {
    return papelesAlDia;
}

bool Vehiculo::getFallaTecnica() const {
    return fallaTecnica;
}

std::string Vehiculo::getMensaje() const {
    return mensaje;
}
