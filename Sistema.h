
#ifndef TALLER_1_SISTEMA_H
#define TALLER_1_SISTEMA_H

#include <string>
// Incluir las clases gestoras desde la carpeta "managers/" y los modelos
#include "managers/ManejadorUsuarios.h"   // Para gestionar el Arreglo Dinámico
#include "managers/ManejadorVehiculos.h" // Para gestionar la Lista Enlazada Circular
#include "model/Usuario.h"

class Sistema {
private:
    ManejadorUsuarios* gestorUsuarios;
    ManejadorVehiculos* gestorVehiculos;

    Usuario* usuarioActual;

    void leerUsuarios(const std::string& archivo);
    void leerVehiculos(const std::string& archivo);

public:
    Sistema();

    void menuInicial();
    void menuPrincipal();
    void mostrarTodos();
    void buscarUsuarios(int id);
    void publicarVehiculo();
    void visualizarOfertas();
    void eliminarUsuario();
    void generarReporte();
    void salir();

    ~Sistema();

};

#endif //TALLER_1_SISTEMA_H