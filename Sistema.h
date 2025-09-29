
#ifndef TALLER_1_SISTEMA_H
#define TALLER_1_SISTEMA_H

#include <string>
// Incluir las clases gestoras desde la carpeta "managers/" y los modelos
#include "managers/ListaUsuarios.h"   // Para gestionar el Arreglo Dinámico
#include "managers/ListaVehiculos.h" // Para gestionar la Lista Enlazada Circular
#include "model/Usuario.h"

class Sistema {

    ListaUsuarios* gestorUsuarios;
    ListaVehiculos* gestorVehiculos;

    Usuario* usuarioActual;

    void leerUsuarios(std::string archivo);
    void leerVehiculos(std::string archivo);

public:
    Sistema();

    void menuInicial();
    void menuPrincipal();
    void inicioSesion();
    void registroUsuario();
    void mostrarTodos();
    void buscarUsuario(int id);
    void publicarVehiculo();
    void visualizarOfertas();
    void eliminarUsuario();
    void generarReporte();
    void salir();

    ~Sistema();

};

#endif //TALLER_1_SISTEMA_H