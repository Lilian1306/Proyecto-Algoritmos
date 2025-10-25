#include <iostream>
#include <limits>
#include "SistemaEnvios.h"

void leerOpcion(int& opcion) {
    while (!(std::cin >> opcion)) {
        std::cout << "\033[31m>> Error: Por favor, introduce un numero valido.\033[0m\n";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Seleccione una Opcion: ";
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void mostrarMenuAdmin(SistemaEnvios& sistema) {
    int opcion;
    do {
        std::cout << "\n=== PANEL DE ADMINISTRADOR ===\n"
                  << "1. Crear nuevo cliente\n"
                  << "2. Ver todos los clientes\n"
                  << "3. Dar de baja a un cliente\n"
                  << "4. Generar reporte de envios\n"
                  << "5. Cerrar Sesion\n"
                  << "Seleccione una Opcion: ";
        leerOpcion(opcion); 

        switch (opcion) {
            case 1: sistema.altaUsuario(); break;
            case 2: sistema.verClientes(); break;
            case 3: sistema.bajaUsuario(); break;
            case 4: sistema.generarReporte(); break;
            case 5: sistema.logout(); std::cout << "\n>> Sesion cerrada.\n"; break;
            default: std::cout << "\033[31mOpcion no valida.\033[0m\n";
        }
    } while (opcion != 5); // 
}

void mostrarMenuControlador(SistemaEnvios& sistema) {
    int opcion;
    do {
        std::cout << "\n=== PANEL DE CONTROLADOR ===\n"
                  << "Bienvenido, " << sistema.getUsuarioActual()->nombre << "\n"
                  << "1. Ver solicitudes de envio pendientes\n"
                  << "2. Asignar envio a mensajero\n"
                  << "3. Cerrar Sesion\n"
                  << "Seleccione una Opcion: ";
        leerOpcion(opcion);

        switch (opcion) {
            case 1: sistema.verSolicitudesPendientes(); break;
            case 2: sistema.asignarEnvio(); break;
            case 3: sistema.logout(); std::cout << "\n>> Sesion cerrada.\n"; break;
            default: std::cout << "\033[31mOpcion no válida.\033[0m\n";
        }
    } while (opcion != 3);
}

void mostrarMenuCliente(SistemaEnvios& sistema) {
    int opcion;
    do {
        std::cout << "\n=== PANEL DE CLIENTE ===\n"
                  << "Bienvenido, " << sistema.getUsuarioActual()->nombre << "\n"
                  << "1. Solicitar un envio\n"
                  << "2. Ver estado de mis envios\n"
                  << "3. Realizar un pago en linea\n"
                  << "4. Cerrar Sesion\n" 
                  << "Seleccione una Opcion: ";
        leerOpcion(opcion); 

        switch (opcion) {
            case 1: sistema.solicitarEnvio(); break;
            case 2: sistema.verMisEnvios(); break;
            case 3: sistema.realizarPago(); break;
            case 4: sistema.logout(); std::cout << "\n>> Sesion cerrada.\n"; break;
            default: std::cout << "\033[31mOpcion no válida.\033[0m\n";
        }
    } while (opcion != 4);
}

void mostrarMenuMensajero(SistemaEnvios& sistema) {
    int opcion;
    do {
        std::cout << "\n=== PANEL DE MENSAJERO ===\n"
                  << "Bienvenido, " << sistema.getUsuarioActual()->nombre << "\n"
                  << "1. Ver mis entregas asignadas\n"
                  << "2. Marcar paquete como entregado\n"
                  << "3. Cerrar Sesion\n"
                  << "Seleccione una Opcion: ";
        leerOpcion(opcion); 

        switch (opcion) {
            case 1: sistema.verMisEntregasAsignadas(); break;
            case 2: sistema.marcarComoEntregado(); break;
            case 3: sistema.logout(); std::cout << "\n>> Sesion cerrada.\n"; break;
            default: std::cout << "\033[31mOpcion no válida.\033[0m\n";
        }
    } while (opcion != 3);
}

int main() {
    SistemaEnvios sistema;
    int opcion = 0;
    std::string email, password;

    do {
        std::cout << "\n===== BIENVENIDO A ENVIOS GARANTIZADOS, S.A. =====\n"
                  << "1. Ingresar como Cliente\n"
                  << "2. Ingresar como Administrador\n"
                  << "3. Ingresar como Controlador\n" 
                  << "4. Ingresar como Mensajero\n" 
                  << "5. Salir\n"                  
                  << "Seleccione una opcion: ";
        leerOpcion(opcion);

        switch (opcion) {
            
            case 1: { 
                int opcionCliente = 0;
                do {
                    std::cout << "\n--- Portal de Clientes ---\n"
                              << "1. Iniciar Sesion\n"
                              << "2. Crear una cuenta nueva\n"
                              << "3. Volver al menu principal\n"
                              << "Seleccione una opcion: ";
                    leerOpcion(opcionCliente);

                    switch (opcionCliente) {
                        case 1: { // Iniciar Sesionón
                            std::cout << "Email: ";
                            getline(std::cin, email);
                            std::cout << "Password: ";
                            getline(std::cin, password);

                            if (sistema.login(email, password) && sistema.getUsuarioActual()->tipoUsuario == "Cliente") {
                                mostrarMenuCliente(sistema);
                            } else {
                                std::cout << "\033[31m>> Error: Credenciales de CLIENTE incorrectas.\033[0m\n";
                                sistema.logout(); 
                            }
                            break;
                        }
                        case 2: { 
                            sistema.altaUsuario();
                            break;
                        }
                        case 3: {
                            break;
                        }
                        default: {
                            std::cout << "\033[31m>> Error:Opcion no valida.\033[0m\n";
                            break;
                        }
                    }
                } while (opcionCliente != 3);
                break;
            }
    

            case 2: 
            case 3:
            case 4: {
                std::cout << "Email: ";
                getline(std::cin, email);
                std::cout << "Password: ";
                getline(std::cin, password);

                if (sistema.login(email, password)) {
                    std::string tipo = sistema.getUsuarioActual()->tipoUsuario;
                    if (opcion == 2 && tipo == "Administrador") {
                        mostrarMenuAdmin(sistema);
                    } else if (opcion == 3 && tipo == "Controlador") {
                        mostrarMenuControlador(sistema);
                    } else if (opcion == 4 && tipo == "Mensajero") {
                        mostrarMenuMensajero(sistema);
                    } else {
                        std::cout << "\033[31mn>> Error: No tienes permiso para acceder a este panel.\033[0m\n";
                        sistema.logout();
                    }
                } else {
                    std::cout << "\033[31m>> Error: Credenciales de ADMINISTRADOR incorrectas.\033[0m\n";
                    sistema.logout(); 
                }
                break;
            }
            case 5: { 
                break; 
            }
            default: {
                std::cout << "\033[31m>> Error:Opcion no valida.\033[0m\n";
            }
        }
    } while (opcion != 5); 

    std::cout << "\nGracias por usar nuestro sistema.\n";
    return 0;
}