
#ifndef TALLER_1_NODOVEHICULO_H
#define TALLER_1_NODOVEHICULO_H

#include "../model/Vehiculo.h"

/**
 * @class NodoVehiculo
 * @brief Representa un nodo dentro de la Lista Enlazada Circular de vehículos.
 *
 * Cada nodo almacena un puntero a un objeto Vehiculo y un puntero al siguiente
 * nodo en la secuencia (que apunta a 'cabeza' si es el último nodo de la lista circular).
 */
class NodoVehiculo {
private:
    /**
     * Puntero al objeto Vehiculo que contiene la información de la oferta.
     */
    Vehiculo* dato;

    /**
     * Puntero al siguiente nodo en la lista.
     * En una lista circular, si es el último nodo (cola), apunta a la cabeza.
     */
    NodoVehiculo* siguiente;

public:
    /**
     * @brief Constructor del nodo.
     * Inicializa el nodo con el puntero al vehículo provisto y establece 'siguiente' a nullptr.
     * @param vehiculo Puntero al objeto Vehiculo que será almacenado en este nodo.
     */
    NodoVehiculo(Vehiculo* vehiculo);

    /**
     * @brief Destructor del nodo.
     * Es CRÍTICO para la liberación de memoria (Opción G).
     * Se encarga de liberar la memoria dinámica del objeto Vehiculo* almacenado en 'dato'.
     */
    ~NodoVehiculo();

    // Getters

    /**
     * @brief Obtiene el puntero al vehículo almacenado en el nodo.
     * @return Puntero al objeto Vehiculo.
     */
    Vehiculo* getVehiculo() const;

    /**
     * @brief Obtiene el puntero al siguiente nodo en la lista.
     * @return Puntero al siguiente NodoVehiculo.
     */
    NodoVehiculo* getSiguiente() const;

    // Setter

    /**
     * @brief Establece el puntero al siguiente nodo.
     * Utilizado por ListaVehiculos para manejar los enlaces de la lista circular.
     * @param nuevoSiguiente Puntero al nodo que seguirá a este.
     */
    void setSiguiente(NodoVehiculo* nuevoSiguiente);
};

#endif //TALLER_1_NODOVEHICULO_H