
#include "Usuario.h"
#include <string>

Usuario::Usuario(int id, std::string nombre, float reputacion, std::string correo, std::string clave, int edad)
    : id(id), nombre(nombre), reputacion(reputacion), correo(correo), clave(clave), edad(edad) {
}

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

