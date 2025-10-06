
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

std::string Vehiculo::getModeloMarca() const {
    size_t pos = modelo.find('(');
    if (pos != std::string::npos && pos > 0) {
        return modelo.substr(0, pos - 1);
    }
    return modelo;
}

int Vehiculo::getAnio() const {
    // Busca el parentesis de apertura
    size_t inicio = modelo.find('(');
    // Busca el parentesis de cierre
    size_t fin = modelo.find(')');

    // Verifica que ambos esten presentes
    if (inicio != std::string::npos && fin != std::string::npos && fin > inicio) {
        // Extrae la subcadena que contiene solo el anio
        std::string anio_str = modelo.substr(inicio + 1, fin - inicio - 1);
        try {
            // Convierte la subcadena a entero
            return std::stoi(anio_str);
        } catch (const std::exception& e) {
            // Manejo de error si la conversion falla
            return 0;
        }
    }
    // Retorna 0 si el formato es incorrecto
    return 0;
}
