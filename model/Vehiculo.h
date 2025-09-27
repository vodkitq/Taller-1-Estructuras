
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

    std::string getPatente() const;
    int getIdUsuario() const;
    std::string getModelo() const;
    int getMonto() const;
    bool getPapelesAlDia() const;
    bool getFallaTecnica() const;
    std::string getMensaje() const;
};

#endif //TALLER_1_VEHICULO_H