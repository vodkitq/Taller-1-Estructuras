// managers/NodoVehiculo.cpp

#include "NodoVehiculo.h"
#include <cstddef>
#include <iostream>


// Constructor y Destructor

/**
 * @brief Implementación del constructor del nodo.
 * Inicializa el puntero de datos y el puntero al siguiente nodo.
 */
NodoVehiculo::NodoVehiculo(Vehiculo* vehiculo) {
    this->dato = vehiculo;
    this->siguiente = nullptr;
}

/**
 * @brief Implementación del destructor del nodo.
 * Es CRÍTICO para la liberación de memoria (Opción G).
 * Se encarga de llamar a 'delete' sobre el objeto Vehiculo* almacenado.
 */
NodoVehiculo::~NodoVehiculo() {
    // Liberar la memoria del Vehiculo que el nodo contiene, si existe
    if (dato != nullptr) {
        delete dato;
        dato = nullptr;
    }
}

// Getters

/**
 * @brief Obtiene el puntero al vehículo almacenado.
 */
Vehiculo* NodoVehiculo::getVehiculo() const {
    return dato;
}

/**
 * @brief Obtiene el puntero al siguiente nodo.
 */
NodoVehiculo* NodoVehiculo::getSiguiente() const {
    return siguiente;
}

// Setter

/**
 * @brief Establece el puntero al siguiente nodo.
 */
void NodoVehiculo::setSiguiente(NodoVehiculo* nuevoSiguiente) {
    siguiente = nuevoSiguiente;
}