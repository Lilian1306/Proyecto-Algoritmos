#ifndef SISTEMAENVIOS_H
#define SISTEMAENVIOS_H

#include <vector>
#include <string> 
#include "Usuario.h"
#include "Paquete.h"

class SistemaEnvios {
public:
    SistemaEnvios();

    // --- Métodos de Sesionón ---
    bool login(const std::string& email, const std::string& password);
    void logout();
    Usuario* getUsuarioActual();

    // --- Métodos de Cliente ---
    void solicitarEnvio();
    void verMisEnvios();
    void realizarPago();

    // --- Métodos de Administrador ---
    void altaUsuario();
    void bajaUsuario(); 
    void verClientes();
    void generarReporte();

    // --- Métodos de Controlador ---
    void verSolicitudesPendientes(); 
    void asignarEnvio();   
    
    // Metodos de mensajero
    void verMisEntregasAsignadas();
    void marcarComoEntregado();

private: // <-- Datos y funciones internas de la clase
    std::vector<Usuario> usuarios;
    std::vector<Paquete> paquetes;
    Usuario* usuarioActual;
    double tarifaNormal;
    int proximoIdPaquete;

    double calcularCosto();
};

#endif 