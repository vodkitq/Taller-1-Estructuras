
#ifndef TALLER_1_VEHICULO_H
#define TALLER_1_VEHICULO_H

#include <string>

class Vehiculo {
private:
    std::string patente;
    int idUsuario;
    std::string modelo;
    int monto;
    bool papelesAlDia;
    bool fallaTecnica;
    std::string mensaje;

public:
    // Constructor
    /**
     * @brief Constructor de la clase Vehiculo.
     */
    Vehiculo(std::string patente, int idUsuario, std::string modelo, int monto,
             bool papelesAlDia, bool fallaTecnica, std::string mensaje);

    // Getters

    /**
     * @brief Obtiene la patente del vehículo.
     * @return Patente alfanumérica única.
     */
    std::string getPatente() const;

    /**
     * @brief Obtiene el ID del usuario que ofertó el vehículo.
     * @return ID del usuario.
     */
    int getIdUsuario() const;

    /**
     * @brief Obtiene el modelo completo del vehículo, incluyendo el año entre paréntesis.
     */
    std::string getModelo() const;

    /**
     * @brief Obtiene el monto de venta del vehículo (no debe superar el millón de pesos).
     */
    int getMonto() const;

    /**
     * @brief Indica si el vehículo tiene los papeles al día ("true" o "false").
     */
    bool getPapelesAlDia() const;

    /**
     * @brief Indica si el vehículo tiene alguna falla técnica ("true" o "false").
     */
    bool getFallaTecnica() const;

    /**
     * @brief Obtiene el mensaje o comentario de la oferta (máximo 450 caracteres).
     */
    std::string getMensaje() const;

    /**
     * @brief Obtiene la marca y modelo sin el año.
     */
    std::string getModeloMarca() const;

    /**
     * @brief Obtiene el año del vehículo.
     */
    int getAnio() const;
};

#endif //TALLER_1_VEHICULO_H