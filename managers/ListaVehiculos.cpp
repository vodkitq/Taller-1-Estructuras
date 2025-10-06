
#include "ListaVehiculos.h"
#include "../model/Usuario.h"
#include "../model/Vehiculo.h"
#include "ListaUsuarios.h"
#include <iostream>

// Constructor
ListaVehiculos::ListaVehiculos() {
    cabeza = nullptr;
    cola = nullptr;
    cantidadNodos = 0;
}

// Destructor
ListaVehiculos::~ListaVehiculos() {
    // Logica para liberar memoria
    if (cabeza == nullptr) {
        return;
    }

    NodoVehiculo* actual = cabeza;
    NodoVehiculo* siguiente = nullptr;

    // Romper la circularidad para poder iterar sin fin
    cola->setSiguiente(nullptr);

    while (actual != nullptr) {
        siguiente = actual->getSiguiente();

        // El destructor de NodoVehiculo debe encargarse de liberar el Vehiculo*
        delete actual;
        actual = siguiente;
    }

    cabeza = nullptr;
    cola = nullptr;
}

void ListaVehiculos::insertarVehiculo(Vehiculo* nuevoVehiculo) {
    NodoVehiculo* nuevoNodo = new NodoVehiculo(nuevoVehiculo);

    if (cabeza == nullptr) {
        // Lista vacia
        cabeza = nuevoNodo;
        cola = nuevoNodo;
        nuevoNodo->setSiguiente(cabeza);
    } else { // La lista ya tiene elementos
        // El nuevo nodo apunta a la cabeza
        nuevoNodo->setSiguiente(cabeza);

        // El nodo que era la cola debe apuntar al nuevo nodo
        cola->setSiguiente(nuevoNodo);

        // El nuevo nodo se convierte en la nueva cola
        cola = nuevoNodo;
    }
    // Incrementa el contador tras la insercion exitosa
    cantidadNodos++;
}

NodoVehiculo *ListaVehiculos::buscarPorPatente(const std::string &patente) {
    // Manejo de lista vacia
    if (cabeza == nullptr) {
        return nullptr;
    }

    // Inicializacion
    NodoVehiculo *actual = cabeza;

    // El ciclo do=while asegura que revisemos `cabeza` almenos una vez
    do {
        if (actual->getVehiculo()->getPatente() == patente) {
            return actual; // Patente encontrada
        }

        actual = actual->getSiguiente(); // Condicion para que avance

    } while (actual != cabeza); // El bucle continua hasta que volvamos al inicio

    return nullptr; // Se recorrio toda la lista y no se encontro
}

// Eliminacion por ID de usuario
void ListaVehiculos::eliminarVehiculoPorIdUsuario(int idUsuario) {
    // Caso lista vacia
    if (cabeza == nullptr) {
        return;
    }

    // Inicializamos punteros para la iteracion circular
    NodoVehiculo *actual = cabeza;
    NodoVehiculo *anterior = cola;

    // `Bandera` para asegurar la primera pasada del bucle
    bool primeraPasada = true;

    // Bucle do-while se ejecuta almenos una vez y continua hasta que `actual` vuelva a ser cabeza.
    do {
        // Marcamos que ya se reviso la cabeza la primera vez
        primeraPasada = false;

        // Verificamos si el vehiculo actual debe ser eliminado
        if (actual->getVehiculo()->getIdUsuario() == idUsuario) {

            // Caso de eliminacion
            NodoVehiculo* toDelete = actual;

            // Caso de que sea un unico nodo en la lista
            if (actual == cabeza && actual == cola) {
                cabeza = nullptr;
                cola = nullptr;
                actual = nullptr;
            } else {
                // El nodo anterior apunta al siguiente del nodo que se va a eliminar
                anterior->setSiguiente(actual->getSiguiente());

                // Movemos actual al siguiente antes de que el puntero se pierda
                actual = actual->getSiguiente();

                // Actualizacion de puntero de control
                if (toDelete == cabeza) {
                    cabeza = actual; // La nueva cabeza es el siguiente nodo
                }
                if (toDelete == cola) {
                    cola = anterior; // La nueva cola es el nodo anterior
                }
            }
            delete toDelete; // Liberamos memoria
            this->cantidadNodos--; // Actualizamos contador
        } else {
            // Caso de no eliminacion
            anterior = actual;
            actual = actual->getSiguiente();
        }
    // El ciclo termina si la lista queda vacia o el puntero `actual` vuelve a apuntar a la `cabeza` original o la nueva cabeza
    } while (cabeza != nullptr && actual != cabeza || primeraPasada);

    if (cabeza != nullptr) {
        cola = nullptr;
    }
}

void fragmentarMensaje(const std::string &mensaje) { // Funcion auxiliar para fragmentar el mensaje
    const int MAX_CARACTERES = 57;
    size_t i = 0;

    while (i < mensaje.size()) {
        std::cout << mensaje.substr(i, MAX_CARACTERES) << "\n";
        i += MAX_CARACTERES; // Avanza el indice al siguiente fragmento
    }
}

NodoVehiculo *ListaVehiculos::getCabeza() const {
    return cabeza;
}


int ListaVehiculos::cantidadActual() const {
    return cantidadNodos;
}

NodoVehiculo* encontrarAnterior(NodoVehiculo* cabeza, NodoVehiculo* objetivo) { // Funcion auxiliar para encontrar el nodo anterior
    if (cabeza == nullptr || cabeza->getSiguiente() == cabeza) {
        return nullptr; // Lista vacia o un solo nodo
    }

    NodoVehiculo *actual = cabeza;

    do {
        // Si el siguiente nodo es el objetivo, entonces el actual es el anterior
        if (actual->getSiguiente() == objetivo) {
            return actual;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return nullptr; // No deberia sucedes si 1objetivo1 esta en la lista
}

void ListaVehiculos::visualizarOfertas(ListaUsuarios* gestorUsuarios) {
    if (cabeza == nullptr) {
        std::cout << "No hay vehiculos disponibles para ofertas.\n";
        return;
    }

    // Inicializamos el puntero de recorrido
    NodoVehiculo* actual = cabeza;
    std::string opcion = "";

    do {
        Vehiculo* vehiculo = actual->getVehiculo();

        // Obtener reputacion del vendedor
        Usuario* vendedor = gestorUsuarios->buscarUsuario(vehiculo->getIdUsuario());

        // Reputacion 0.0 si el vendedor no se encuentra
        double reputacion = (vendedor != nullptr) ? vendedor->getReputacion() : 0.0f;

        // Determinar recomendacion
        std::string recomendacion;
        if (reputacion <0.2) {
            recomendacion = "No deberia adquirir el vehiculo.";
        } else if (reputacion <= 0.65) {
            recomendacion = "Pienselo bien.";
        } else if (reputacion > 0.65) {
            recomendacion = "Le recomendamos comprar el vehiculo.";
        }

        // Despliegue de informacion
        std::cout << "\n=============================================\n";
        std::cout << ("OFERTA ACTUAL:") << "\n";
        std::cout << "Patente: " << vehiculo->getPatente() << "\n";

        std::cout << "Modelo: " << vehiculo->getModeloMarca() << "\n";
        std::cout << "Anio: " << vehiculo->getAnio() << "\n";

        std::cout << "Papeles al dia: " << (vehiculo->getPapelesAlDia() ? "Si" : "No") << "\n";
        std::cout << "Precio: $" << vehiculo->getMonto() << "\n";
        std::cout << "Falla tecnica: " << (vehiculo->getFallaTecnica() ? "Si" : "No") << "\n";
        std::cout << "Recomendacion: " << recomendacion << "\n";

        // Mensaje
        std::cout << ("Mensaje:") << "\n";
        fragmentarMensaje(vehiculo->getMensaje());

        std::cout << "=============================================\n";

        std::cout << "Opciones: [S]iguiente / [A]nterior / [Q]uit (Salir): ";
        std::cin >> opcion;

        if (opcion == "S" || opcion == "s") {
            // Navega al siguiente, solo avanza gracias a la circularidad
            actual = actual->getSiguiente();
        } else if (opcion == "A" || opcion == "a") {
            // Navega al anterior
            NodoVehiculo* anterior = encontrarAnterior(cabeza, actual);
            // Si es la cabeza, encontrarAnterior retorna la cola
            if (anterior != nullptr) {
                actual = anterior;
            }
            // Si anterior es nullptr, `actual` se mantiene en su sitio.
        } else if (opcion == "Q" || opcion == "q") {
            break;
        } else {
            std::cout << "Opcion no valida. Por favor, intentelo nuevamente.\n";
        }
    } while (true);
}

Vehiculo* ListaVehiculos::buscarVehiculoMasBarato() const {
    if (cabeza == nullptr) {
        return nullptr;
    }

    Vehiculo* masBarato = cabeza->getVehiculo();
    NodoVehiculo* actual = cabeza->getSiguiente();

    // Recorrido circular
    while (actual != cabeza) {
        if (actual->getVehiculo()->getMonto() < masBarato->getMonto()) {
            masBarato = actual->getVehiculo();
        }
        actual = actual->getSiguiente();
    }
    return masBarato;
}

float ListaVehiculos::calcularMediaPrecios() const {
    if (cantidadNodos == 0) {
        return 0.0f;
    }

    long long sumaTotal = 0;
    NodoVehiculo* actual = cabeza;

    // Recorrido circular
    do {
        sumaTotal += actual->getVehiculo()->getMonto();
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    return (float)sumaTotal / cantidadNodos;
}

int ListaVehiculos::contarVehiculosPorUsuario(int idUsuario) const {
    if (cabeza == nullptr) {
        return 0;
    }

    int contador = 0;
    NodoVehiculo* actual = cabeza;

    // Recorrido circular
    do {
        if (actual->getVehiculo()->getIdUsuario() == idUsuario) {
            contador++;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    return contador;
}

int ListaVehiculos::contarVehiculosAntiguos(int idUsuario, int anioLimite) {
    if (cabeza == nullptr) {
        return 0;
    }

    int contador = 0;
    NodoVehiculo* actual = cabeza;

    // Recorrido circular
    do {
        Vehiculo* v = actual->getVehiculo();

        // Comprobar que el vehículo pertenezca al usuario y sea anterior al límite (e.g., < 1970) [6]
        if (v->getIdUsuario() == idUsuario && v->getAnio() < anioLimite) {
            contador++;
        }

        actual = actual->getSiguiente();
    } while (actual != cabeza); // Continuar hasta volver al inicio [8]

    return contador;
}