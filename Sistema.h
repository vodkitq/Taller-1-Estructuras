
#ifndef TALLER_1_SISTEMA_H
#define TALLER_1_SISTEMA_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "managers/ListaUsuarios.h"
#include "managers/ListaVehiculos.h"

#include "model/Usuario.h"
#include "model/Vehiculo.h"

class Sistema {
private:
    /**
     * Gestor del Arreglo Dinámico Ordenado de usuarios.
     */
    ListaUsuarios* gestorUsuarios;

    /**
     * Gestor de la Lista Enlazada Circular de vehículos.
     */
    ListaVehiculos* gestorVehiculos;

    /**
     * Puntero al usuario que ha iniciado sesión actualmente. nullptr si nadie está autenticado.
     */
    Usuario* usuarioActual;

    /**
     * @brief Carga los usuarios desde el archivo 'usuarios.csv'.
     * Utiliza stringstream para parsear los datos delimitados por coma y los inserta en el gestorUsuarios.
     * @param archivo Nombre del archivo CSV de usuarios.
     */
    void leerUsuarios(std::string archivo);

    /**
     * @brief Carga los vehículos desde el archivo 'vehiculos.csv'.
     * Parsea los datos y los inserta en el gestorVehiculos.
     * @param archivo Nombre del archivo CSV de vehículos.
     */
    void leerVehiculos(std::string archivo);

    /**
    * @brief Escribe la información de todos los usuarios actualmente en el sistema de vuelta al archivo CSV.
    * @param archivo Nombre del archivo CSV de usuarios a sobrescribir.
    */
    void escribirUsuarios(std::string archivo);

    /**
    * @brief Escribe la información de todos los vehículos actualmente en el sistema de vuelta al archivo CSV.
    * @param archivo Nombre del archivo CSV de vehículos a sobrescribir.
    */
    void escribirVehiculos(std::string archivo);

    /**
     * @brief Genera un nuevo ID aleatorio (entre 100 y 999) y verifica que sea único.
     * @return ID único.
     */
    int generarIdUnico();

public:
    /**
     * @brief Constructor del sistema.
     * Inicializa los gestores de estructuras de datos y realiza la carga inicial de archivos.
     */
    Sistema();

    /**
     * @brief Destructor del sistema.
     * Llama al método salir() para garantizar la liberación de memoria y el guardado de datos.
     */
    ~Sistema();

    /**
     * @brief Despliega y gestiona el Menú Inicial (Iniciar Sesión, Registrarse, Salir).
     */
    void menuInicial();

    /**
     * @brief Despliega y gestiona el Menú Principal (Opciones A a G).
     * Solo accesible si un usuario ha iniciado sesión.
     */
    void menuPrincipal();

    /**
     * @brief Gestiona el proceso de autenticación del usuario (Opción 1 del Menú Inicial).
     */
    void inicioSesion();

    /**
     * @brief Gestiona el proceso de registro de un nuevo usuario (Opción 2 del Menú Inicial).
     * Debe validar correo, edad, clave y generar un ID único.
     */
    void registroUsuario();

    /**
     * @brief Opción A: Muestra la patente de todos los vehículos y el ID de todos los usuarios registrados.
     */
    void mostrarTodos();

    /**
     * @brief Opción B: Busca y despliega la información de un usuario dado su ID.
     * Debe utilizar el método de búsqueda binaria O(log₂n) en ListaUsuarios.
     * @param id ID del usuario a buscar.
     */
    void buscarUsuario(int id);

    /**
     * @brief Opción C: Permite al usuario activo publicar un nuevo vehículo.
     * Requiere la validación exhaustiva de Patente, Monto, Modelo, etc.
     */
    void publicarVehiculo();

    /**
     * @brief Opción D: Permite al usuario visualizar las ofertas en modo circular (anterior/siguiente).
     * Llama a ListaVehiculos::visualizarOfertas.
     */
    void visualizarOfertas();

    /**
     * @brief Opción E: Elimina un usuario del sistema dado su ID.
     * Al eliminar, se deben borrar todos los vehículos asociados a dicho usuario.
     */
    void eliminarUsuario();

    /**
     * @brief Opción F: Genera un reporte de estadísticas en un archivo de texto.
     * Incluye redimensiones del arreglo, vehículo más barato, media de precios, etc.
     */
    void generarReporte();

    /**
     * @brief Opción G / Salida: Realiza las tareas de cierre del sistema [12].
     * Debe borrar todos los punteros asociados a las estructuras (liberación de memoria).
     * Debe actualizar los archivos CSV ('vehiculos.csv' y 'usuarios.csv') con la información actual en el sistema.
     */
    void salir();
};

#endif //TALLER_1_SISTEMA_H