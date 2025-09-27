
#ifndef TALLER_1_USUARIO_H
#define TALLER_1_USUARIO_H

#include <string>

class Usuario {
private:
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
    int getId() const;
    std::string getNombre() const;
    float getReputacion() const;
    std::string getCorreo() const;
    int getEdad() const;

    // (Incluir documentación aquí)
};

#endif //TALLER_1_USUARIO_H