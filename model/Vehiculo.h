
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
    Vehiculo(std::string patente, int idUsuario, std::string modelo, int monto,
             bool papelesAlDia, bool fallaTecnica, std::string mensaje);

    std::string getPatente();
    int getIdUsuario();
    std::string getModelo();
    int getMonto();
    bool getPapelesAlDia();
    bool getFallaTecnica();
    std::string getMensaje();
};

#endif //TALLER_1_VEHICULO_H