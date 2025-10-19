
#include "Paquete.h" 

// Implementación del método
void Paquete::mostrarDetalles() const {
    std::cout << "  ID Solicitud: " << idSolicitud << "\n";
    std::cout << "  Estado: " << estado << "\n";
    std::cout << "  Descripcion: " << descripcion << "\n";
    std::cout << "  Costo: Q" << costo << "\n";
    std::cout << "  -------------------------\n";
}