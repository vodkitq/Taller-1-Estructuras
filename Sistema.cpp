#include "Sistema.h"
#include <iostream>
#include <fstream>
#include <sstream>

Sistema::Sistema() : usuarioActual(nullptr) {
    // 1. Inicializar las clases gestoras (las estructuras de datos)
    gestorUsuarios = new ManejadorUsuarios();
    gestorVehiculos = new ManejadorVehiculos();

    std::cout << "Inicializando sistema..." << std::endl;

    // 2. Cargar los datos iniciales
    leerVehiculos("vehiculos.csv");
    leerUsuarios("usuarios.csv");
}

Sistema::~Sistema() {
    // Asegurar que si el objeto Sistema es destruido, se llame a la lógica de salir.
    salir();
}

void Sistema::leerUsuarios(const std::string& archivo) {
    // Paso Uno: Abrir el archivo
    std::ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de usuarios." << std::endl;
        return;
    }

    std::string linea;
    // Opcional: Omitir la cabecera si la tiene.
    // std::getline(archivoEntrada, linea);

    while (std::getline(archivoEntrada, linea)) {
        // Crear un stringstream que necesita la línea leída del archivo
        std::stringstream ss(linea);
        std::string id_str, nombre, reputacion_str, correo, clave, edad_str;

        // Paso Tres y Cuatro: Obtener los datos delimitados por coma
        std::getline(ss, id_str, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, reputacion_str, ',');
        std::getline(ss, correo, ',');
        std::getline(ss, clave, ',');
        std::getline(ss, edad_str, ',');

        try {
            // Conversión de strings a tipos de datos primitivos
            int id = std::stoi(id_str);
            float reputacion = std::stof(reputacion_str);
            int edad = std::stoi(edad_str);

            // Crear el objeto Usuario dinámicamente con new
            Usuario* nuevoUsuario = new Usuario(id, nombre, reputacion, correo, clave, edad);

            // Insertar en la estructura obligatoria (Arreglo Dinámico Ordenado)
            // ESTO REEMPLAZA EL PROHIBIDO 'emplace_back' [2-4]
            if (gestorUsuarios != nullptr) {
                gestorUsuarios->insertarUsuario(nuevoUsuario);
            }

        } catch (const std::exception& e) {
            // Manejo de errores de conversión de datos (usando try-catch [10])
            std::cerr << "Error al procesar línea de usuario: " << e.what() << std::endl;
        }
    }
    archivoEntrada.close();
    std::cout << "Usuarios cargados correctamente." << std::endl;
}

void Sistema::leerVehiculos(const std::string& archivo) {
    std::ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de vehículos." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        std::string patente, idUsuario_str, modelo, monto_str, papelesAlDia_str, fallaTecnica_str, mensaje;

        // Obtener los 7 campos
        std::getline(ss, patente, ',');
        std::getline(ss, idUsuario_str, ',');
        std::getline(ss, modelo, ',');
        std::getline(ss, monto_str, ',');
        std::getline(ss, papelesAlDia_str, ',');
        std::getline(ss, fallaTecnica_str, ',');
        std::getline(ss, mensaje); // El mensaje es el último campo, no está delimitado por coma al final

        try {
            // Conversión de datos
            int idUsuario = std::stoi(idUsuario_str);
            int monto = std::stoi(monto_str);
            // Conversión simple de "true"/"false" a bool
            bool papelesAlDia = (papelesAlDia_str == "true");
            bool fallaTecnica = (fallaTecnica_str == "true");

            // Crea el objeto Vehiculo dinámicamente con new
            Vehiculo* nuevoVehiculo = new Vehiculo(patente, idUsuario, modelo, monto,
                                                   papelesAlDia, fallaTecnica, mensaje);

            // Inserta en la estructura obligatoria (Lista Enlazada Circular)
            if (gestorVehiculos != nullptr) {
                gestorVehiculos->insertarVehiculo(nuevoVehiculo);
            }

        } catch (const std::exception& e) {
            std::cerr << "Error al procesar línea de vehículo: " << e.what() << std::endl;
        }
    }
    archivoEntrada.close();
    std::cout << "Vehiculos cargados correctamente." << std::endl;
}

void Sistema::menuInicial() {
    int opcion = 0;
    while (opcion != 3) {
        // Mostrar Menú Inicial
        std::cout << "\n--- MENÚ INICIAL ---" << std::endl;
        std::cout << "1. Iniciar sesión" << std::endl; // [18]
        std::cout << "2. Registrarse" << std::endl;   // [19]
        std::cout << "3. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";

        if (!(std::cin >> opcion)) {
            // Manejo de errores de entrada, limpiar y reintentar
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            opcion = 0; // Para forzar la repetición
        }

        switch (opcion) {
            case 1:
                // Lógica de Iniciar Sesión
                // Si la autenticación es exitosa, llamar a menuPrincipal()
                break;
            case 2:
                // Lógica de Registrarse
                // Generar Id aleatorio único y reputación por defecto (0.5)
                break;
            case 3:
                salir(); // Opción G
                return;
            default:
                std::cout << "Opción inválida." << std::endl;
        }
    }
}

void Sistema::menuPrincipal() {
    char opcion;

    // El menú debe repetirse hasta que el usuario decida salir.
    do {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "          MENU PRINCIPAL DE OFERTAS       " << std::endl;
        std::cout << "==========================================" << std::endl;

        // Opciones del Menú Principal
        std::cout << "A. Mostrar todos" << std::endl;
        std::cout << "B. Buscar un usuario" << std::endl;
        std::cout << "C. Publicar un vehiculo" << std::endl;
        std::cout << "D. Visualizar ofertas" << std::endl;
        std::cout << "E. Eliminar un usuario" << std::endl;
        std::cout << "F. Generar reporte" << std::endl;
        std::cout << "G. Salir" << std::endl;

        std::cout << "------------------------------------------" << std::endl;
        std::cout << "Ingrese su opcion (A-G): ";

        // Lectura de la opción
        if (!(std::cin >> opcion)) {
            // Manejo de errores de entrada para evitar fallos abruptos
            std::cin.clear();
            std::cin.ignore(100, '\n');
            opcion = 'Z';
        }

        // Convertir a mayúscula para simplificar el switch
        opcion = std::toupper(opcion);

        switch (opcion) {
            case 'A':
                this->mostrarTodos();
                break;
            case 'B':
            {
                int idBuscado;
                std::cout << "Ingrese el ID del usuario a buscar: ";
                if (std::cin >> idBuscado) {
                    this->buscarUsuario(idBuscado);
                } else {
                    std::cout << "Entrada invalida. Debe ser un numero." << std::endl;
                    // Limpiar el buffer si la entrada es errónea
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                }
                break;
            }
            case 'C':
                this->publicarVehiculo();
                break;
            case 'D':
                this->visualizarOfertas();
                break;
            case 'E':
                this->eliminarUsuario();
                break;
            case 'F':
                this->generarReporte();
                break;
            case 'G':
                this->salir();
                break;
            default:
                std::cout << "Opcion invalida. Por favor, intente de nuevo." << std::endl;
                break;
        }

    } while (opcion != 'G');
}

void mostrarTodos();

void buscarUsuarios(int id) {}

void publicarVehiculo() {}

void visualizarOfertas() {}

void eliminarUsuario() {}

void generarReporte() {}

void Sistema::salir() {
    // Opción G: Borrar todos los punteros asociados a las estructuras.

    // 1. Llamar a la lógica de liberación de memoria de los manejadores
    //    (Dentro del ManejadorUsuarios y ManejadorVehiculos se debe usar 'free' [11])
    if (gestorUsuarios != nullptr) {
        // El destructor de gestorUsuarios debe liberar cada Usuario* y luego llamar a free()
        delete gestorUsuarios;
        gestorUsuarios = nullptr;
    }
    if (gestorVehiculos != nullptr) {
        // El destructor de gestorVehiculos debe recorrer la lista y liberar cada Nodo/Vehiculo*
        delete gestorVehiculos;
        gestorVehiculos = nullptr;
    }

    // 2. Actualizar los archivos CSV
    std::cout << "Guardando datos y cerrando aplicación. Memoria liberada." << std::endl;
}


