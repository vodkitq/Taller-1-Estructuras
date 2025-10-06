
#ifndef TALLER1_MANEJADORUSUARIOS_H
#define TALLER1_MANEJADORUSUARIOS_H

#include "../model/Usuario.h"
#include <cstdlib>

class ListaUsuarios {
private:
    /**
     * Puntero a puntero que almacena los objetos Usuario* de forma dinamica
     */
    Usuario** arregloUsuarios;

    /**
     * Capacidad máxima actual del arreglo dinámico.
     */
    int capacidad;

    /**
     * Cantidad real de usuarios almacenados en el arreglo.
     */
    int cantidadActual;

    /**
     * Contador de cuántas veces se ha redimensionado el arreglo, requerido para el reporte.
     */
    int redimensiones;

    /**
     * Metodo auxiliar para aumentar la capacidad del arreglo en 1 usando realloc.
     */
    void redimensionarArreglo();

public:
    /**
     * Constructor que inicializa el arreglo dinámico con una capacidad inicial y los contadores a cero.
     */
    ListaUsuarios();

    /**
     * Destructor que se encarga de liberar toda la memoria dinámica reservada (objetos Usuario* y el arreglo de punteros).
     */
    ~ListaUsuarios();

    /**
     * Inserta un nuevo usuario en el arreglo, manteniendo el orden ascendente por ID.
     * Si la capacidad es excedida, llama a redimensionarArreglo().
     * @param nuevoUsuario Puntero al objeto Usuario a insertar.
     */
    void insertarUsuario(Usuario* nuevoUsuario);

    /**
     * Busca un usuario por su ID utilizando Búsqueda Binaria.
     * El costo algorítmico asociado a la búsqueda es O(log₂n).
     * @param idBuscado El ID del usuario a encontrar.
     * @return Puntero al objeto Usuario si es encontrado, o nullptr en caso contrario.
     */
    Usuario* buscarUsuario(int idBuscado) const;

    /**
     * Elimina un usuario dado su ID. Utiliza Búsqueda Binaria para localizar el índice de eliminación.
     * Al eliminar, se debe liberar la memoria del objeto Usuario y desplazar los elementos para mantener el orden y contigüidad [6, 13].
     * @param idUsuario ID del usuario a eliminar.
     */
    void eliminarUsuario(int idUsuario);

    // Getter para el reporte

    /**
     * Obtiene la cantidad de veces que se ha redimensionado el arreglo.
     * @return Número de redimensiones.
     */
    int getRedimensiones() const;

    /**
     * Obtiene la cantidad actual de usuarios en el arreglo.
     * @return Cantidad de elementos.
     */
    int getCantidadActual() const;

    /**
     * Obtiene un puntero a Usuario en un índice específico del arreglo.
     * @param indice Posición del usuario.
     * @return Puntero al objeto Usuario.
     */
    Usuario* getUsuario(int indice) const;
};

#endif //TALLER_1_MANEJADORUSUARIOS_H