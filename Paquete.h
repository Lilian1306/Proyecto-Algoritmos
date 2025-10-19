// Paquete.h
#ifndef PAQUETE_H
#define PAQUETE_H

#include <iostream>
#include <string>

class Paquete {
public:
    int idSolicitud;
    std::string idCliente;
    std::string idMensajeroAsignado;
    std::string descripcion;
    float peso;
    std::string estado;
    double costo;

    void mostrarDetalles() const;
};

#endif