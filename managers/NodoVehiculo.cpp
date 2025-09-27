// managers/NodoVehiculo.cpp

#include "NodoVehiculo.h"
#include <iostream>

// Implementación del constructor
NodoVehiculo::NodoVehiculo(Vehiculo* v) : dato(v), siguiente(nullptr) {
    // Cuando se crea un nodo, el puntero 'siguiente' se inicializa a nullptr.
    // La clase ManejadorVehiculos se encargará de enlazarlo.
}

// Implementación del destructor (CRÍTICO para la Opción G: Salir [4])
NodoVehiculo::~NodoVehiculo() {
    // Liberar la memoria del Vehiculo que el nodo contiene, si existe
    if (dato != nullptr) {
        delete dato;
        dato = nullptr;
    }
}

// Getters
Vehiculo* NodoVehiculo::getDato() const {
    return dato;
}

NodoVehiculo* NodoVehiculo::getSiguiente() const {
    return siguiente;
}

// Setter
void NodoVehiculo::setSiguiente(NodoVehiculo* nuevoSiguiente) {
    siguiente = nuevoSiguiente;
}
