#include "Sistema.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

Sistema::Sistema() {
    srand(time(nullptr));
    usuarioActual = nullptr;

    gestorUsuarios = new ListaUsuarios();
    gestorVehiculos = new ListaVehiculos();

    std::cout << "Inicializando sistema..." << std::endl;

    leerVehiculos("vehiculos.csv");
    leerUsuarios("usuarios.csv");
}

Sistema::~Sistema() {
    delete gestorUsuarios;
    delete gestorVehiculos;
}

void Sistema::leerUsuarios(std::string archivo) {
    // Paso Uno: Abrir el archivo
    std::ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de usuarios." << std::endl;
        exit(1);
    }

    std::string linea;

    while (std::getline(archivoEntrada, linea)) {
        // Crear un stringstream que necesita la línea leída del archivo
        std::stringstream ss(linea);
        std::string id_str, nombre, reputacion_str, correo, clave, edad_str;

        // Obtiene los datos delimitados por coma
        getline(ss, id_str, ',');
        getline(ss, nombre, ',');
        getline(ss, reputacion_str, ',');
        getline(ss, correo, ',');
        getline(ss, clave, ',');
        getline(ss, edad_str);

        try {
            // Conversión de datos segura (usuarios)
            int id = 0;
            float reputacion = 0.0f;
            int edad = 0;

            // id
            try {
                id = std::stoi(id_str);
            } catch (...) {
                id = 0; // valor por defecto si no es numérico
            }

            // reputación (float)
            try {
                reputacion = std::stof(reputacion_str);
            } catch (...) {
                reputacion = 0.0f; // valor por defecto si no es numérico
            }

            // edad
            try {
                edad = std::stoi(edad_str);
            } catch (...) {
                edad = 0; // valor por defecto si no es numérico
            }

            // Se crea un objeto de la clase Usuario (igual que antes)
            Usuario* nuevoUsuario = new Usuario(id, nombre, reputacion, correo, clave, edad);

            // Se inserta en el arreglo dinámico ordenado
            if (gestorUsuarios != nullptr) {
                gestorUsuarios->insertarUsuario(nuevoUsuario);
            }

        } catch (const std::exception& e) {
            std::cerr << "Error al procesar línea de usuario: " << e.what() << std::endl;
        }

    }
    archivoEntrada.close();
    std::cout << "Usuarios cargados correctamente." << std::endl;
}

void Sistema::leerVehiculos(std::string archivo) {
    std::ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de vehiculos." << std::endl;
        exit(1);
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
            int idUsuario = 0;
            int monto = 0;

            try {
                idUsuario = std::stoi(idUsuario_str);
            } catch (...) {
                idUsuario = 0; // valor por defecto si no es numérico
            }

            try {
                monto = std::stoi(monto_str);
            } catch (...) {
                monto = 0; // valor por defecto si no es numérico
            }

            // Conversión simple de true/false a bool
            bool papelesAlDia = (papelesAlDia_str == "true");
            bool fallaTecnica = (fallaTecnica_str == "true");

            // Se crea un objeto de la clase Vehiculo
            Vehiculo* nuevoVehiculo = new Vehiculo(
                patente, idUsuario, modelo, monto,
                papelesAlDia, fallaTecnica, mensaje
            );

            // Se inserta en el arreglo dinámico circular
            if (gestorVehiculos != nullptr) {
                gestorVehiculos->insertarVehiculo(nuevoVehiculo);
            }

        } catch (const std::exception& e) {
            std::cerr << "Error al procesar línea de vehiculo: " << e.what() << std::endl;
        }

    }
    archivoEntrada.close();
    std::cout << "Vehiculos cargados correctamente." << std::endl;
}

int Sistema::generarIdUnico() {
    int nuevoId;
    bool existe;

    do {
        nuevoId = 100 + (rand() % 900);
        existe = (gestorUsuarios->buscarUsuario(nuevoId) != nullptr);
    } while (existe);
    return nuevoId;
}

void Sistema::menuInicial() {
    int opcion = 0;
    while (opcion != 3) {
        // Mostrar Menú Inicial
        std::cout << "\n--- MENU INICIAL ---" << std::endl;
        std::cout << "1. Iniciar sesion" << std::endl;
        std::cout << "2. Registrarse" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            // Manejo de errores de entrada, limpiar y reintentar
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            opcion = 0; // Para forzar la repetición
        }

        switch (opcion) {
            case 1:
                inicioSesion();
                break;
            case 2:
                registroUsuario();
                break;
            case 3:
                salir();
                return;
            default:
                std::cout << "Opcion invalida." << std::endl;
        }
    }
}

void Sistema::menuPrincipal() {
    char opcion;

    do {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "          MENU PRINCIPAL DE OFERTAS       " << std::endl;
        std::cout << "==========================================" << std::endl;

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

void Sistema::inicioSesion() {
    while (true) {
        std::cout << "======== INICIO DE SESION ==========" << std::endl;

        std::string correo;
        std::cout << "Ingrese su correo (0 para salir): ";
        std::cin >> correo;

        if (correo == "0") {
            return; // Salir al menú principal
        }

        std::string contrasenia;
        std::cout << "Ingrese su contrasenia: ";
        std::cin >> contrasenia;

        Usuario* usuarioEncontrado = nullptr;

        // Buscar el usuario por correo en la lista dinámica
        for (int i = 0; i < gestorUsuarios->getCantidadActual(); i++) {
            Usuario* u = gestorUsuarios->getUsuario(i);
            if (u->getCorreo() == correo) {
                usuarioEncontrado = u;
                break;
            }
        }

        if (usuarioEncontrado != nullptr && usuarioEncontrado->getClave() == contrasenia) {
            std::cout << "Usuario encontrado: " << usuarioEncontrado->getNombre() << std::endl;
            std::cout << "ID: " << usuarioEncontrado->getId() << std::endl;
            std::cout << "Reputacion: " << usuarioEncontrado->getReputacion() * 100 << "%" << std::endl;
            std::cout << "Correo electronico: " << usuarioEncontrado->getCorreo() << std::endl;

            usuarioActual = usuarioEncontrado;  // Guardar sesión activa
            menuPrincipal();                    // Ir al menú principal
            return;
        }

        std::cout << "Credenciales incorrectas, intente nuevamente." << std::endl;
    }
}


void Sistema::registroUsuario() {
    using namespace std;

    // La variable exitoso controlara si se debe salir o repetir la entrada
    bool registroExitoso = false;

    // Bucle para el registro
    while (!registroExitoso) {
        cout << "======== REGISTRO DE USUARIO ==========" << endl;

        string nombre = "";
        string correo = "";
        int edad = 0;
        string clave = "";
        string claveRepetida = "";
        bool datosValidos = true;

        cout << "Ingrese su nombre y apellido (0 para salir): ";
        std::getline(std::cin >> std::ws, nombre);

        if (nombre == "0") {
            return;
        }

        // Validacion, busca al menos 1 espacio en el medio
        if (nombre.find(' ') == string::npos || nombre.find(' ') == 0 || nombre.find(' ') == nombre.length() - 1) {
            cout << ("El nombre y el apellido deben estar separados por un espacio. ") << endl;
            datosValidos = false;
        }

        if (datosValidos) {
            cout << "Ingrese su correo: ";
            cin >> correo;

            if (correo.find('@') == string::npos || correo.find('.') == string::npos) {
                cout << ("Formato de correo electronico invalido. ") << endl;
                datosValidos = false;
            }
        }

        if (datosValidos) {
            cout << "Ingrese su edad: ";
            if (!(cin >> edad)) {
                cout << ("Entrada invalida. La edad debe ser un numero entero. ") << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                datosValidos = false;
            } else if (edad < 0 || edad >= 75) { // Edad debe ser inferior a 75
                cout << ("La edad debe ser mayor o igual a 0 y estrictamente menor a 75.") << endl;
                datosValidos = false;
            }
        }

        // Clave y confirmacion
        if (datosValidos) {
            cout << "Ingrese su clave: ";
            cin >> clave;

            cout << "Confirme su clave: ";
            cin >> claveRepetida;

            if (clave != claveRepetida) {
                cout << ("La clave ingresada no coincide con la ingresada anteriormente. ") << endl;
                datosValidos = false;
            }
        }

        // Insercion y fin del bucle
        if (datosValidos) {
            int id = generarIdUnico();
            float reputacion = 0.50; // Reputacion por defecto

            Usuario* usuario = new Usuario(id, nombre, reputacion, correo, clave, edad);
            gestorUsuarios->insertarUsuario(usuario);

            usuarioActual = usuario;
            cout << ("Registro exitoso. Iniciando sesión...") << endl;

            menuPrincipal();
            registroExitoso = true;
        }

        if (registroExitoso) {
            return;
        }
    }
}

void Sistema::mostrarTodos() {
    using namespace std;

    cout << "\n=============================================\n";
    cout << ("OPCION A: MOSTRAR TODOS\n");
    cout << "=============================================\n";

    // 1. Mostrar IDs de todos los usuarios
    cout << ("USUARIOS REGISTRADOS (IDs): ") << gestorUsuarios->getCantidadActual() << endl;
    for (int i = 0 ; i < gestorUsuarios->getCantidadActual(); i++) {
        Usuario* usuario = gestorUsuarios->getUsuario(i);

        if (usuario != nullptr) {
            cout << "ID: " << usuario->getId() << "\n";
        }
    }

    // 2. Mostrar patententes de todos los vehiculos
    cout << "\n" << ("VEHICULOS OFERTADOS (Patentes): ") << gestorVehiculos->cantidadActual() << endl;
    NodoVehiculo* actual = gestorVehiculos->getCabeza();

    if (actual != nullptr) {
        do {
            Vehiculo* vehiculo = actual->getVehiculo(); // Obtenemos vehiculo almacenado en el nodo

            if (vehiculo != nullptr) {
                cout << "Patente: " << vehiculo->getPatente() << "\n"; // Obtenemos la patente
            }
            actual = actual->getSiguiente(); // Avanzamos al siguiente nodo
        } while (actual != gestorVehiculos->getCabeza()); // Continuamos hasta volver al inicio
    } else {
        cout << "(No hay vehiculos ofertados)" << "\n";
    }
    cout << "=============================================\n";
}

void Sistema::buscarUsuario(int idBuscado) {
    using namespace std;

    cout << "\n=============================================\n";
    cout << ("OPCION B: BUSCAR UN USUARIO") << "\n";
    cout << "ID buscado: " << idBuscado << "\n";
    cout << "=============================================\n";

    Usuario* usuarioEncontrado = gestorUsuarios->buscarUsuario(idBuscado);

    if (usuarioEncontrado != nullptr) {
        // Usuario encontrado, se despliega la informacion requerida

        // Nombre
        cout << ("Usuario encontrado: ") << usuarioEncontrado->getNombre() << "\n";

        // ID
        cout << "ID: " << usuarioEncontrado->getId() << "\n";

        // Reputación (llevada a porcentaje), multiplicamos la reputación (0.0 a 1.0) por 100
        float reputacionPorcentaje = usuarioEncontrado->getReputacion() * 100.0f;
        cout << "Reputacion: " << reputacionPorcentaje << "%\n";

        // Correo electrónico
        cout << "Correo electronico: " << usuarioEncontrado->getCorreo() << "\n";
    } else {
        // Usuario no encontrado
        cout << ("Error: Usuario con ID ") << idBuscado << (" no encontrado en el sistema.") << "\n";
    }
    cout << "=============================================\n";
}

bool esVocal(char c) {
    c = std::toupper(c);
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

bool validarPatente(const std::string& patente) {
    // Validamos que la patente tenga largo de 6 caracteres
    if (patente.length() != 6) {
        return false;
    }

    // El formato de la pantente es LLLLNN (4 Letras, 2 Numeros)

    // Validamos que las primeras 4 posiciones sean letras no vocales
    for (int i = 0; i < 4; i++) {
        if (!std::isalpha(patente[i]) || esVocal(patente[i])) {
            return false;
        }
    }

    // Validamos que las ultimas 2 posiciones sean numeros
    for (int i = 4; i < 6; i++) {
        if (!std::isdigit(patente[i])) {
            return false;
        }
    }

    // El primer digito no puede ser 0
    if (patente[4] == '0') {
        return false;
    }

    // Si pasa todas las pruebas
    return true;
}

void Sistema::publicarVehiculo() {
    using namespace std;

    if (usuarioActual == nullptr) {
        cout << ("Error: Debe iniciar sesión para publicar un vehiculo.") << endl;
        return;
    }

    // Definimos variables para capturar la entrada
    string patente, modelo, mensaje;
    string papelesStr, fallaStr;
    int monto = -1;
    bool papelesAlDia, fallaTecnica;

    // Bucle de validacion
    while (true) {
        vector<string> errores;

        cout << "\n======== PUBLICAR VEHICULO =========" << endl;
        cout << "(Ingrese '0' en cualquier campo para cancelar)" << endl;

        cin.ignore(10000, '\n');

        // Patente
        cout << "a. Patente (4 no-vocales, 2 digitos, Ej: AABB12): ";
        std::getline(std::cin, patente);
        if (patente == "0") return;

        // Validacion de patente
        if (!validarPatente(patente)) {
            errores.push_back("Patente: Debe tener 4 letras (no vocales) y 2 dígitos (el primero no es 0). ");
        }

        // Modelo
        cout << "b. Modelo (Marca, modelo y anio entre parentesis): ";
        std::getline(std::cin, modelo);
        if (modelo == "0") return;

        // Validación básica de modelo
        if (modelo.empty()) {
            errores.push_back("Modelo: No puede estar vacio.");
        }

        // Papeles al dia
        cout << "c. Papeles al dia (si/no): ";
        cin >> papelesStr;
        std::transform(papelesStr.begin(), papelesStr.end(), papelesStr.begin(), ::tolower); // Convertir a minúsculas

        if (papelesStr == "si") {
            papelesAlDia = true;
        } else if (papelesStr == "no") {
            papelesAlDia = false;
        } else if (papelesStr == "0") {
            return;
        } else {
            errores.push_back("Papeles al dia: Debe ser 'si' o 'no'.");
        }

        // Monto
        cout << "d. Monto (Precio, máx. 1,000,000): $";

        if (!(cin >> monto) || monto < 0) {
            errores.push_back("Monto: Debe ser un numero entero positivo.");
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (monto > 1000000) { // No debe superar el millón de pesos chilenos [1]
            errores.push_back("Monto: No debe superar el limite de $1,000,000.");
        }

        // Falla tecnica
        cout << "e. Tiene falla tecnica (si/no): ";
        cin >> fallaStr;
        std::transform(fallaStr.begin(), fallaStr.end(), fallaStr.begin(), ::tolower);

        if (fallaStr == "si") {
            fallaTecnica = true;
        } else if (fallaStr == "no") {
            fallaTecnica = false;
        } else if (fallaStr == "0") {
            return;
        } else {
            errores.push_back("Falla tecnica: Debe ser 'si' o 'no'.");
        }

        // Mensaje
        cout << "f. Mensaje (Max. 450 caracteres, sin comas/saltos): ";
        cin.ignore(10000, '\n'); // Limpiar buffer después del último cin >>
        std::getline(std::cin, mensaje);
        if (mensaje == "0") return;

        // Validación de mensaje [4]
        if (mensaje.length() > 450) {
            errores.push_back("Mensaje: El texto no debe superar los 450 caracteres.");
        }
        if (mensaje.find(',') != string::npos) { // No debe contener comas [4]
            errores.push_back("Mensaje: El texto no debe contener comas.");
        }

        // Resultado de la validacion
        if (errores.empty()) {
            // Todos los datos son válidos

            // Creamos el nuevo Vehiculo (usando el ID del usuario logueado)
            Vehiculo* nuevoVehiculo = new Vehiculo(
                patente,
                usuarioActual->getId(), // Obtenemos el ID del usuario autenticado
                modelo,
                monto,
                papelesAlDia,
                fallaTecnica,
                mensaje
            );
            // Insertamos en la Lista Enlazada Circular
            gestorVehiculos->insertarVehiculo(nuevoVehiculo);

            cout << ("\nVehiculo publicado exitosamente.") << endl;
            break; // Salir del bucle while(true)
        } else {
            // Mostrar todos los errores
            cout << ("\n=============================================") << endl;
            cout << ("ERROR: Se encontraron los siguientes problemas:") << endl;

            for (const string& error : errores) {
                cout << ("* ") << error << endl;
            }

            cout << ("Por favor, intentelo de nuevo.") << endl;
            cout << ("=============================================\n") << endl;
        }
    }
}

void Sistema::visualizarOfertas() {
    using namespace std;
    gestorVehiculos->visualizarOfertas(gestorUsuarios);
}

void Sistema::eliminarUsuario() {
    using namespace std;

    cout << "\n=============================================\n";
    cout << ("OPCION E: ELIMINAR UN USUARIO") << "\n";
    cout << "=============================================\n";

    int idEliminar;
    cout << "Ingrese el ID del usuario a eliminar (0 para cancelar): ";

    if (!(cin >> idEliminar) || idEliminar == 0) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << ("Operacion cancelada.") << "\n";
        return;
    }

    // Verificar si el usuario a eliminar es el usuario activo
    if (usuarioActual != nullptr && usuarioActual->getId() == idEliminar) {
        cout << ("Error: No puedes eliminar tu propia cuenta mientras esta activa. Cierra sesión primero (Opción G).") << "\n";
        return;
    }

    // Eliminar vehiculos asociados
    cout << "Eliminando vehiculos publicados por el ID " << idEliminar << "..." << "\n";
    gestorVehiculos->eliminarVehiculoPorIdUsuario(idEliminar);

    // Eliminar usuario
    cout << "Eliminando usuario del sistema..." << "\n";
    gestorUsuarios->eliminarUsuario(idEliminar);

    cout << "=============================================\n";
}

void Sistema::generarReporte() {
    using namespace std;

    cout << "\n=============================================\n";
    cout << ("OPCION F: GENERAR REPORTE") << "\n";
    cout << "=============================================\n";

    // Generar nombre del archivo
    time_t now = time(0);
    tm* ltm = localtime(&now);

    // Formateo de fecha: DD-MM-YYYY_Mi-SS
    char buffer[25];
    // Se usa %M (minuto) y %S (segundo)
    strftime(buffer, sizeof(buffer), "%d-%m-%Y_%M-%S", ltm);
    string fechaStr(buffer);
    string nombreArchivo = "estadisticas_" + fechaStr + ".txt";

    ofstream reporte(nombreArchivo);

    if (!reporte.is_open()) {
        cout << ("Error al crear el archivo de reporte: ") << nombreArchivo << "\n";
        return;
    }

    reporte << "======== REPORTE DE ESTADISTICAS DEL SITIO ========\n\n";

    // a. Cantidad de redimensiones (Mantenido)
    int redimensiones = gestorUsuarios->getRedimensiones();
    reporte << "a. Cantidad de redimensiones del arreglo dinamico: " << redimensiones << "\n\n";

    // b. Vehículo más barato (Patente, dueño, monto)
    Vehiculo* masBarato = gestorVehiculos->buscarVehiculoMasBarato(); // Método disponible [12]
    if (masBarato != nullptr) {
        // Buscar el nombre del dueño en el arreglo ordenado de usuarios
        Usuario* duenoBarato = gestorUsuarios->buscarUsuario(masBarato->getIdUsuario());
        string nombreDueno = (duenoBarato != nullptr) ? duenoBarato->getNombre() : "ID Desconocido";

        reporte << "b. Vehiculo más barato:\n";
        reporte << "   Patente: " << masBarato->getPatente() << "\n";
        reporte << "   Duenio: " << nombreDueno << "\n";
        reporte << "   Monto: $" << masBarato->getMonto() << "\n\n";
    } else {
        reporte << "b. Vehiculo más barato: No hay vehículos ofertados.\n\n";
    }

    // c. Media aritmética de precios
    float media = gestorVehiculos->calcularMediaPrecios(); // Método disponible [12]
    reporte << "c. Media aritmetica de los precios: $" << std::fixed << std::setprecision(2) << media << "\n\n";

    // d. Usuario confiable que más vehículos ha ofertado
    string nombreMejorOferente = "N/A";
    string correoMejorOferente = "N/A";
    int maxOfertas = -1;
    int usuariosTotal = gestorUsuarios->getCantidadActual(); // Necesario para punto e.
    int usuariosConOfertasAntiguas = 0; // Se usará para punto e.

    for (int i = 0; i < usuariosTotal; ++i) {
        Usuario* u = gestorUsuarios->getUsuario(i);

        if (u->getReputacion() > 0.65) { // Usuario confiable
            int conteo = gestorVehiculos->contarVehiculosPorUsuario(u->getId()); // Método disponible [12]

            if (conteo > maxOfertas) {
                maxOfertas = conteo;
                nombreMejorOferente = u->getNombre();
                correoMejorOferente = u->getCorreo();
            }
        }

        // Lógica para el punto e. (Dentro del mismo bucle de usuarios)
        const int ANIO_LIMITE = 1970; // Anteriores a 1970
        const int MIN_VEHICULOS_ANTIGUOS = 3; // Más de 3

        int conteoAntiguo = gestorVehiculos->contarVehiculosAntiguos(u->getId(), ANIO_LIMITE); // Implementado en paso 3

        if (conteoAntiguo > MIN_VEHICULOS_ANTIGUOS) {
            usuariosConOfertasAntiguas++;
        }
    }

    reporte << "d. Usuario confiable (r > 0.65) que mas vehiculos ha ofertado:\n";
    if (maxOfertas > 0) {
        reporte << "   Nombre: " << nombreMejorOferente << "\n";
        reporte << "   Correo: " << correoMejorOferente << "\n";
        reporte << "   Vehiculos ofertados: " << maxOfertas << "\n\n";
    } else {
        reporte << "d. No se encontraron usuarios confiables con ofertas.\n\n";
    }

    // e. Porcentaje de usuarios que han ofertado más de 3 vehículos antiguos
    float porcentaje = 0.0f;
    if (usuariosTotal > 0) {
        porcentaje = (float)usuariosConOfertasAntiguas / usuariosTotal * 100.0f;
    }

    reporte << "e. Porcentaje de usuarios con más de 3 vehículos antiguos (anteriores a 1970):\n";
    reporte << "   Usuarios que cumplen el criterio: " << usuariosConOfertasAntiguas << " de " << usuariosTotal << "\n";
    reporte << "   Porcentaje: " << std::fixed << std::setprecision(2) << porcentaje << "%\n\n";

    // Cierre
    reporte.close();
    cout << ("Reporte generado exitosamente en: ") << nombreArchivo << "\n";
    cout << "=============================================\n";
}

// Metodos adicionales para salir
void Sistema::escribirUsuarios(std::string archivo) {
    std::ofstream archivoSalida(archivo, std::ios::trunc); // Abrir para sobrescribir
    if (!archivoSalida.is_open()) return;

    for (int i = 0; i < gestorUsuarios->getCantidadActual(); ++i) {
        Usuario* u = gestorUsuarios->getUsuario(i);
        // Formato: Id, nombre, reputación, correo, clave, edad [25]
        archivoSalida << u->getId() << ","
                      << u->getNombre() << ","
                      << std::fixed << std::setprecision(2) << u->getReputacion() << ","
                      << u->getCorreo() << ","
                      << u->getClave() << ","
                      << u->getEdad() << "\n";
    }
    archivoSalida.close();
}

void Sistema::escribirVehiculos(std::string archivo) {
    std::ofstream archivoSalida(archivo, std::ios::trunc);
    if (!archivoSalida.is_open()) return;

    // Recorrido Circular para escribir todos los vehículos
    NodoVehiculo* actual = gestorVehiculos->getCabeza();
    do {
        Vehiculo* v = actual->getVehiculo();
        // Formato: Patente, id del usuario, modelo, monto, papeles al día, tiene falla técnica, mensaje [26]
        archivoSalida << v->getPatente() << ","
                      << v->getIdUsuario() << ","
                      << v->getModelo() << ","
                      << v->getMonto() << ","
                      << (v->getPapelesAlDia() ? "true" : "false") << ","
                      << (v->getFallaTecnica() ? "true" : "false") << ","
                      << v->getMensaje() << "\n"; // El último campo no lleva coma
        actual = actual->getSiguiente();
    } while (actual != gestorVehiculos->getCabeza());

    archivoSalida.close();
}

void Sistema::salir() {
    using namespace std;
    // Persistencia de Datos (Actualizar archivos CSV)
    cout << ("Guardando cambios en archivos CSV...") << endl;
    escribirUsuarios("usuarios.csv");
    escribirVehiculos("vehiculos.csv");

    // Liberación de memoria
    if (gestorUsuarios != nullptr) {
        delete gestorUsuarios; // El destructor de ListaUsuarios libera todos los Usuario*
        gestorUsuarios = nullptr;
    }

    if (gestorVehiculos != nullptr) {
        delete gestorVehiculos; // El destructor de ListaVehiculos libera todos los NodoVehiculo/Vehiculo*
        gestorVehiculos = nullptr;
    }

    cout << ("Guardado y finalizacion exitosa. Memoria liberada.") << endl;
}