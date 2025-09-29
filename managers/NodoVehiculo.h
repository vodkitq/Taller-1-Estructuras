
#ifndef TALLER_1_NODOVEHICULO_H
#define TALLER_1_NODOVEHICULO_H

#include "../model/Vehiculo.h"

class NodoVehiculo {

    // Valor del nodo
    Vehiculo* dato;

    // Puntero al siguiente nodo
    NodoVehiculo* siguiente;

public:
    // Constructor: Recibe un puntero a un Vehiculo
    NodoVehiculo(Vehiculo* v);

    // Getters
    Vehiculo* getDato();
    NodoVehiculo* getSiguiente();

    // Setter
    void setSiguiente(NodoVehiculo* nuevoSiguiente);

    // El destructor debe liberar la memoria del Vehiculo que contiene
    ~NodoVehiculo();
};


#endif //TALLER_1_NODOVEHICULO_H