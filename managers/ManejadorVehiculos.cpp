
#include "ManejadorVehiculos.h"
#include <iostream>

ManejadorVehiculos::ManejadorVehiculos() : cabeza(nullptr), cola(nullptr) {
    // Los punteros de control se inicializan a nulo cuando la lista está vacía.
}

ManejadorVehiculos::~ManejadorVehiculos() {
    // Implementación para liberar toda la memoria de la lista circular (Opción G)
    if (cabeza == nullptr) {
        return; // Lista vacía
    }

    NodoVehiculo* actual = cabeza;
    NodoVehiculo* siguiente = nullptr;

    // Romper la circularidad para poder iterar sin fin
    cola->setSiguiente(nullptr);

    while (actual != nullptr) {
        siguiente = actual->getSiguiente();
        // El destructor de NodoVehiculo debe encargarse de liberar el Vehiculo*
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
}

void ManejadorVehiculos::insertarVehiculo(Vehiculo* nuevoVehiculo) {
    NodoVehiculo* nuevoNodo = new NodoVehiculo(nuevoVehiculo);

    if (cabeza == nullptr) {
        // Caso 1: La lista está vacía
        cabeza = nuevoNodo;
        cola = nuevoNodo;
        // En una lista circular, el primer nodo se apunta a sí mismo
        nuevoNodo->setSiguiente(cabeza);
    } else {
        // Caso 2: La lista ya tiene elementos
        // 1. El nuevo nodo apunta a la cabeza
        nuevoNodo->setSiguiente(cabeza);

        // 2. El nodo que era la 'cola' debe apuntar al nuevo nodo
        cola->setSiguiente(nuevoNodo);

        // 3. El nuevo nodo se convierte en la nueva 'cola'
        cola = nuevoNodo;
    }
}
