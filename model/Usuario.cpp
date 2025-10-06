
#include "Usuario.h"
#include <string>



// Implementacion del Constructor
Usuario::Usuario(int id, std::string nombre, float reputacion, std::string correo, std::string clave, int edad) {
    this->id = id;
    this->nombre = nombre;
    this->reputacion = reputacion;
    this->correo = correo;
    this->clave = clave;
    this->edad = edad;
}

// Implementacion de los Getters
int Usuario::getId() {
    return id;
}

std::string Usuario::getNombre() {
    return nombre;
}

float Usuario::getReputacion() {
    return reputacion;
}

std::string Usuario::getCorreo() {
    return correo;
}

std::string Usuario::getClave() {
    return clave;
}

int Usuario::getEdad() {
    return edad;
}

