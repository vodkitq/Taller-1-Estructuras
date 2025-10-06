
#ifndef TALLER_1_MANEJADORVEHICULOS_H
#define TALLER_1_MANEJADORVEHICULOS_H

#include "NodoVehiculo.h"
#include <string>

class ListaUsuarios; // Declaración anticipada de la clase ListaUsuarios para evitar dependencia circular

class ListaVehiculos {
private:
    /**
     * Puntero al primer nodo de la lista circular.
     */
    NodoVehiculo* cabeza;

    /**
     * Puntero al último nodo de la lista circular, que apunta a cabeza.
     */
    NodoVehiculo* cola;

    /**
     * Contador interno para llevar el registro exacto de vehículos en la lista.
     */
    int cantidadNodos;

public:
    /**
     * Constructor que inicializa los punteros de control y el contador de nodos.
     */
    ListaVehiculos();

    /**
     * Destructor que libera toda la memoria dinámica de los nodos y vehículos.
     */
    ~ListaVehiculos();

    /**
     * Inserta un nuevo vehículo al final de la lista, manteniendo la circularidad.
     * @param nuevoVehiculo Puntero al objeto Vehiculo a insertar.
     */
    void insertarVehiculo(Vehiculo* nuevoVehiculo);

    /**
     * Permite la navegación circular (Siguiente/Anterior) a través de las ofertas.
     * Recibe el gestor de usuarios para obtener la reputación del vendedor y calcular la recomendación.
     * @param gestorUsuarios Puntero al gestor de usuarios (ListaUsuarios).
     */
    void visualizarOfertas(ListaUsuarios* gestorUsuarios);

    /**
     * Elimina todos los vehículos asociados a un ID de usuario específico.
     * @param idUsuario ID del usuario cuyos vehículos serán eliminados.
     */
    void eliminarVehiculoPorIdUsuario(int idUsuario);

    /**
     * Busca un nodo por la patente del vehículo.
     * @param patente Patente del vehículo a buscar.
     * @return Puntero al NodoVehiculo encontrado, o nullptr.
     */
    NodoVehiculo* buscarPorPatente(const std::string& patente);

    /**
     * Documentar !!!! 732489237489327648932748923784
     * @return
     */
    NodoVehiculo* getCabeza() const;

    /**
     * Retorna la cantidad actual de nodos (vehículos) en la lista.
     */
    int cantidadActual() const;

    // Metodos para el reporte

    // b. Vehículo más barato
    Vehiculo* buscarVehiculoMasBarato() const;

    // c. Media aritmética de precios
    float calcularMediaPrecios() const;

    // d. Cantidad de vehículos ofertados por un ID específico
    int contarVehiculosPorUsuario(int idUsuario) const;

    // e. Conteo de vehículos antiguos (para el porcentaje)
    int contarVehiculosAntiguos(int idUsuario, int anioLimite);
};

#endif //TALLER_1_MANEJADORVEHICULOS_H