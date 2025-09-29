
#include "ListaUsuarios.h"

#include <iostream>
#include <ostream>

// Constructor
ListaUsuarios::ListaUsuarios() {
    capacidad = 4; // Capacidad inicial
    cantidadActual = 0;
    redimensiones = 0;

    arregloUsuarios = (Usuario**) malloc(sizeof(Usuario*) * capacidad); // Se reserva espacio en la memoria

    if (arregloUsuarios == nullptr) {
        std::cout << "Error a la hora de reservar memoria para los usuarios" << std::endl;
        exit(1);
    }
}

void ListaUsuarios::redimensionarArreglo() {
    int nuevaCapacidad = capacidad + 1;

    // Se aumenta el espacio de la memoria reservada
    Usuario** nuevoArreglo = (Usuario**) realloc(arregloUsuarios, sizeof(Usuario*) * nuevaCapacidad);

    if (nuevoArreglo == nullptr) { // El realloc falló, por lo tanto arregloUsuarios sigue siendo valido
        std::cerr << "Error: Falla al redimensionar memoria (realloc)." << std::endl;
        exit(1);

    } else { // El realloc ha funcionado con éxito
        arregloUsuarios = nuevoArreglo;
        capacidad = nuevaCapacidad;
        redimensiones++;
    }
}

void ListaUsuarios::insertarUsuario(Usuario *nuevoUsuario) {
    if (cantidadActual == capacidad) { // Se agranda la lista en el caso de que esté llena
        redimensionarArreglo();
    }

    int nuevoId = nuevoUsuario->getId();
    int indiceInsercion = cantidadActual;

    for (int i = 0; i < capacidad; i++) { // Se recorre la lista de usuarios (punteros)
        if (arregloUsuarios[i]->getId() > nuevoId) { // Se busca el primer id que sea mayor al nuevo ID
            indiceInsercion = i;
            break;
        }
    }

    for (int i = cantidadActual; i > indiceInsercion; i--) { // Se recorre la lista desde el final hasta indiceInsercion
        arregloUsuarios[i] = arregloUsuarios[i - 1]; // Se mueven los datos hacia la derecha
    }

    arregloUsuarios[indiceInsercion] = nuevoUsuario;

    cantidadActual++;
}

int ListaUsuarios::getRedimensiones() const {
    return redimensiones;
}

int ListaUsuarios::getCantidadActual() const {
    return cantidadActual;
}

Usuario* ListaUsuarios::getUsuario(int indice) const {
    return arregloUsuarios[indice];
}


