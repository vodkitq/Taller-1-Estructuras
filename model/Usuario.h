
#ifndef TALLER_1_USUARIO_H
#define TALLER_1_USUARIO_H

#include <string>

class Usuario {
    int id;
    std::string nombre;
    float reputacion;
    std::string correo;
    std::string clave;
    int edad;

public:
    // Constructor
    Usuario(int id, std::string nombre, float reputacion, std::string correo, std::string clave, int edad);

    // Getters
    int getId();
    std::string getNombre();
    float getReputacion();
    std::string getCorreo();
    std::string getClave();
    int getEdad();

    // (Incluir documentación aquí)
};

#endif //TALLER_1_USUARIO_H