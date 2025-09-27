
#ifndef TALLER_1_NODOVEHICULO_H
#define TALLER_1_NODOVEHICULO_H

#include "../model/Vehiculo.h"

class NodoVehiculo {
private:
    // 1. Puntero al dato (El Vehiculo almacenado)
    Vehiculo* dato;

    // 2. Puntero al siguiente nodo (La dirección de memoria del próximo NodoVehiculo)
    NodoVehiculo* siguiente;

public:
    // Constructor: Recibe un puntero a un Vehiculo
    NodoVehiculo(Vehiculo* v);

    // Getters
    Vehiculo* getDato() const;
    NodoVehiculo* getSiguiente() const;

    // Setter
    void setSiguiente(NodoVehiculo* nuevoSiguiente);

    // El destructor debe liberar la memoria del Vehiculo que contiene
    ~NodoVehiculo();
};


#endif //TALLER_1_NODOVEHICULO_H