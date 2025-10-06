
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

// Destructor
ListaUsuarios::~ListaUsuarios() {
    // Liberamos la memoria de los objetos usuario individuales
    for (int i = 0 ; i < cantidadActual; i++) {
        delete arregloUsuarios[i];
    }

    // Liberamos el bloque de memoria del arreglo de punteros
    if (arregloUsuarios != nullptr) {
        free(arregloUsuarios);
        arregloUsuarios = nullptr;
    }
}

void ListaUsuarios::redimensionarArreglo() {
    // La capacidad debe sumarse 1 espacio usando realloc
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
    if (cantidadActual == capacidad) {
        redimensionarArreglo(); // Se agranda la lista en el caso de que esté llena
    }

    int nuevoId = nuevoUsuario->getId();
    int indiceInsercion = cantidadActual;

    for (int i = 0; i < cantidadActual; i++) { // Se recorre la lista de usuarios (punteros)
        if (arregloUsuarios[i]->getId() > nuevoId) { // Se busca el primer id que sea mayor al nuevo ID
            indiceInsercion = i;
            break;
        }
    }

    for (int i = cantidadActual; i > indiceInsercion; i--) { // Se recorre la lista desde el final hasta indiceInsercion
        arregloUsuarios[i] = arregloUsuarios[i - 1]; // Se mueven los datos hacia la derecha
    }

    // Insertar el nuevo usuario en el indice encontrado
    arregloUsuarios[indiceInsercion] = nuevoUsuario;
    cantidadActual++;
}

Usuario *ListaUsuarios::buscarUsuario(int idBuscado) const {
    // Inicializamos los punteros de limite (low y high)
    int low = 0;
    int high = cantidadActual - 1; // Usamos la cantidad actual de elementos

    // Bucle que continua mientras el rango de busqueda sea valido
    while (low <= high) {
        // Calculamos un indice medio
        int mid = low + (high - low) / 2;

        // Accedemos al puntero de Usuario y llamamos a si getId()
        int idEncontrado = arregloUsuarios[mid]->getId();

        // Id encontrado
        if (idEncontrado == idBuscado) {
            return arregloUsuarios[mid];
        }

        // El id buscado es mayor, buscamos en la mitad derecha
        else if (idEncontrado < idBuscado) {
            low = mid + 1;
        }

        // El id buscado es menor, buscamos en la mitad izquierda
        else {
            high = mid - 1;
        }
    }
    // Si el bucle termina, es porque el usuario no fue encontrado
    return nullptr;
}

void ListaUsuarios::eliminarUsuario(int idUsuario) {
    int low = 0;
    int high = cantidadActual - 1;
    int indiceEliminar = -1;

    // Busqueda binaria
    while (low <= high) {
        int mid = low + (high - low) / 2;

        int idEncontrado = arregloUsuarios[mid]->getId();

        if (idEncontrado == idUsuario) {
            indiceEliminar = mid;
            break;
        }  else if (idEncontrado < idUsuario) {
            low = mid + 1;
        }  else {
            high = mid - 1;
        }
    }

    if (indiceEliminar == -1) {
        // Usuario no encontrado
        std::cout << "Error: No se puede eliminar el usuario. ID " << idUsuario << " no encontrado." << std::endl;
        return;
    }

    // Se obtiene el nombre antes de liberar la memoria
    std::string nombreUsuario = arregloUsuarios[indiceEliminar]->getNombre();

    // Se libera la memoria del objeto Usuario
    delete arregloUsuarios[indiceEliminar];

    // Desplazamiento de elementos
    for (int i = indiceEliminar; i < cantidadActual - 1; i++) {
        arregloUsuarios[i] = arregloUsuarios[i + 1];
    }

    // Actualiza el contador de elementos
    cantidadActual--;

    // Mensaje de exito
    std::cout << "Usuario " << nombreUsuario << " eliminado exitosamente." << std::endl;
}

// Getters

int ListaUsuarios::getRedimensiones() const {
    return redimensiones;
}

int ListaUsuarios::getCantidadActual() const {
    return cantidadActual;
}

Usuario* ListaUsuarios::getUsuario(int indice) const {
    return arregloUsuarios[indice];
}