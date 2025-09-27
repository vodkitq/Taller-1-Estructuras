
#include "Usuario.h"
#include <string>

Usuario::Usuario(int id, std::string nombre, float reputacion, std::string correo, std::string clave, int edad)
    : id(id), nombre(nombre), reputacion(reputacion), correo(correo), clave(clave), edad(edad) {
}

int Usuario::getId() const {
    return id;
}

std::string Usuario::getNombre() const {
    return nombre;
}

float Usuario::getReputacion() const {
    return reputacion;
}

std::string Usuario::getCorreo() const {
    return correo;
}

int Usuario::getEdad() const {
    return edad;
}

