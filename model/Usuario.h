
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
    /**
     * @brief Constructor de la clase Usuario.
     */
    Usuario(int id, std::string nombre, float reputacion, std::string correo, std::string clave, int edad);

    // Getters

    /**
     * @brief Obtiene el ID del usuario (único, siempre mayor a cien).
     */
    int getId();

    /**
     * @brief Obtiene el nombre y apellido del usuario.
     */
    std::string getNombre();

    /**
     * @brief Obtiene el valor de reputación del usuario (entre 0 y 1).
     */
    float getReputacion();

    /**
     * @brief Obtiene el correo electrónico del usuario.
     */
    std::string getCorreo();

    /**
     * @brief Obtiene la clave (contraseña) del usuario.
     */
    std::string getClave();

    /**
     * @brief Obtiene la edad del usuario (entero positivo, inferior a 75).
     */
    int getEdad();
};

#endif //TALLER_1_USUARIO_H