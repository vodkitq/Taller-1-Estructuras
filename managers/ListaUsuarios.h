
#ifndef TALLER1_MANEJADORUSUARIOS_H
#define TALLER1_MANEJADORUSUARIOS_H

#include "../model/Usuario.h" // Se debe incluir el modelo
#include <cstdlib> // Necesario para 'realloc' y 'free'

class ListaUsuarios {

    // Puntero doble: El arreglo dinámico que almacena punteros a objetos Usuario
    Usuario** arregloUsuarios;
    int capacidad;              // Capacidad máxima actual del arreglo
    int cantidadActual;               // Número actual de usuarios insertados
    int redimensiones;          // Contador de veces que se usó realloc

    // Metodo auxiliar para el crecimiento manual del arreglo
    void redimensionarArreglo();

public:
    // Constructor y Destructor (para liberar memoria - Opción G)
    ListaUsuarios();
    ~ListaUsuarios();

    // Inserción: Debe mantener el orden por Id
    void insertarUsuario(Usuario* nuevoUsuario);

    // Búsqueda: Debe implementar Búsqueda Binaria (O(log n) - Opción B) [2]
    Usuario* buscarUsuario(int idBuscado) const;

    // Getter para el reporte (Opción F)
    int getRedimensiones() const;

    // Métodos auxiliares necesarios
    int getCantidadActual() const;
    Usuario* getUsuario(int indice) const;
};


#endif //TALLER_1_MANEJADORUSUARIOS_H