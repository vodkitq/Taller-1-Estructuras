
#ifndef TALLER_1_MANEJADORVEHICULOS_H
#define TALLER_1_MANEJADORVEHICULOS_H

#include "NodoVehiculo.h"
#include <string>

class ManejadorVehiculos {
private:
    // Punteros de control para la Lista Enlazada Circular [2]
    NodoVehiculo* cabeza; // Puntero al primer nodo
    NodoVehiculo* cola;   // Puntero al último nodo (útil para la inserción y la circularidad)

public:
    // Constructor
    ManejadorVehiculos();

    // Inserción: Lógica para agregar un nuevo vehículo y mantener la circularidad
    void insertarVehiculo(Vehiculo* nuevoVehiculo);

    // Opción D: Visualizar ofertas. Debe permitir el recorrido circular
    void visualizarOfertas();

    // Métodos auxiliares para la lógica
    NodoVehiculo* buscarPorPatente(const std::string& patente);

    // Destructor
    ~ManejadorVehiculos();
};

#endif //TALLER_1_MANEJADORVEHICULOS_H