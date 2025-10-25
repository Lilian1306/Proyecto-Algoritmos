#include "SistemaEnvios.h"
#include <iostream>
#include <ctime>
#include <limits>
#include <vector> 
#include <algorithm> 

SistemaEnvios::SistemaEnvios() {
    usuarioActual = nullptr;
    tarifaNormal = 50.0;
    proximoIdPaquete = 101;
    usuarios.emplace_back("admin01", "Admin General", "admin@envios.com", "12345", "Administrador");
    usuarios.emplace_back("cli001", "Tony", "tony@email.com", "tony123", "Cliente");
    usuarios.emplace_back("men001", " Mensajero", "mensajero@email.com", "mensajero123", "Mensajero"); 
    usuarios.emplace_back("ctrl01", "Jefe de Ruta", "control@envios.com", "ctrl123", "Controlador");
}

bool SistemaEnvios::login(const std::string& email, const std::string& password) {
    for (auto& user : usuarios) {
        if (user.email == email && user.password == password) {
            usuarioActual = &user;
            return true;
        }
    }
    return false;
}

void SistemaEnvios::logout() {
    usuarioActual = nullptr;
}

Usuario* SistemaEnvios::getUsuarioActual() {
    return usuarioActual;
}

void SistemaEnvios::altaUsuario() {
    Usuario nuevoUsuario;
    
    std::cout << "\n--- Crear Nueva Cuenta ---\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Nombre completo: ";
    getline(std::cin, nuevoUsuario.nombre);
    if (nuevoUsuario.nombre.empty()) {
        std::cout << "\033[31mn>> Creacion cancelada. El nombre es obligatorio.\033[0m\n";
        return; 
    }

    std::cout << "Correo electronico: ";
    getline(std::cin, nuevoUsuario.email);
    if (nuevoUsuario.email.empty()) {
        std::cout << "\033[31mn>> Creacion cancelada. El correo es obligatorio.\033[0m\n";
        return; 
    }

    std::cout << "numero de telefono: ";
    getline(std::cin, nuevoUsuario.telefono);

    std::cout << "Contrasena: ";
    getline(std::cin, nuevoUsuario.password);
    if (nuevoUsuario.password.empty()) {
        std::cout << "\033[31mn>> Creacion cancelada. La contrasena es obligatoria.\033[0m\n";
        return; 
    }

    nuevoUsuario.tipoUsuario = "Cliente";
    nuevoUsuario.idUsuario = "cli" + std::to_string(usuarios.size());
                                    
    usuarios.push_back(nuevoUsuario);
    
    std::cout << "\n>> ¡Cuenta para '" << nuevoUsuario.nombre << "' creada exitosamente!\n";
}

void SistemaEnvios::solicitarEnvio() {
    if (!usuarioActual) return;
    Paquete nuevoPaquete;
    nuevoPaquete.idCliente = usuarioActual->idUsuario;
    nuevoPaquete.idSolicitud = proximoIdPaquete++;

    std::cout << "--- Solicitar Nuevo Envio ---\n";
    std::cout << "Descripcion del paquete: ";
    getline(std::cin, nuevoPaquete.descripcion);

    std::cout << "Peso del paquete (max 15 libras): ";
    std::cin >> nuevoPaquete.peso;

    while(std::cin.fail()) {
        std::cout << "\033[31mError: Por favor ingrese un numero.\033[0m\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Peso del paquete (max 15 libras): ";
        std::cin >> nuevoPaquete.peso;
    }

    if (nuevoPaquete.peso > 15.0) {
        std::cout << "\033[31mn>> Error: El peso excede las 15 libras.\033m\n";
        proximoIdPaquete--;
        return;
    }

    nuevoPaquete.costo = calcularCosto();
    nuevoPaquete.estado = "Solicitado";
    paquetes.push_back(nuevoPaquete);
    std::cout << "\n>> Solicitud de envio creada con exito. Costo: $" << nuevoPaquete.costo << "\n";
}

void SistemaEnvios::verMisEnvios() {
    if (!usuarioActual) return;
    std::cout << "\n--- Mis Envios Registrados ---\n";
    bool encontrados = false;

    for (const auto& paquete : paquetes) {
        if (paquete.idCliente == usuarioActual->idUsuario) {
            std::cout << "---------------------------------\n";
            paquete.mostrarDetalles(); 

            if (!paquete.idMensajeroAsignado.empty()) {
                std::string nombreMensajero = "No disponible";
                for (const auto& user : usuarios) {
                    if (user.idUsuario == paquete.idMensajeroAsignado) {
                        nombreMensajero = user.nombre;
                        break;
                    }
                }

                if (paquete.estado == "Entregado") {
                    std::cout << ">> ¡Entregado por " << nombreMensajero << "!\n";
                } else {
                    std::cout << ">> Asignado al mensajero: " << nombreMensajero << "\n";
                }
            }
            encontrados = true;
        }
    }
    if (!encontrados) {
        std::cout << ">> No tienes envios registrados.\n";
    }
}

double SistemaEnvios::calcularCosto() {
    time_t ahora = time(0);
    tm *ltm = localtime(&ahora);
    int hora = ltm->tm_hour;
    return (hora >= 8 && hora < 18) ? tarifaNormal : tarifaNormal * 2;
}

void SistemaEnvios::generarReporte() {
    std::cout << "\n--- REPORTE GENERAL DE ENVIOS ---\n";
    if (paquetes.empty()) {
        std::cout << "No hay paquetes registrados.\n";
        return;
    }
    int solicitudes = 0, enTransito = 0, entregados = 0;
    for (const auto& p : paquetes) {
        if (p.estado == "Solicitado") solicitudes++;
        else if (p.estado == "En Transito") enTransito++;
        else if (p.estado == "Entregado") entregados++;
    }
    std::cout << "Solicitudes Recibidas (pendientes de pago): " << solicitudes << "\n";
    std::cout << "Paquetes en Transito: " << enTransito << "\n";
    std::cout << "Paquetes Entregados: " << entregados << "\n";
    std::cout << "---------------------------------\n";
}

void SistemaEnvios::realizarPago() {
    if (!usuarioActual) {
        std::cout << "\033[31mError: Debes iniciar Sesion primero.\033[0m\n";
        return;
    }

    std::cout << "\n--- Realizar Pago en Linea ---\n";
    
    std::vector<int> paquetesAPagarIndices;
    for (int i = 0; i < paquetes.size(); ++i) {
        if (paquetes[i].idCliente == usuarioActual->idUsuario && paquetes[i].estado == "Solicitado") {
            paquetesAPagarIndices.push_back(i);
        }
    }

    if (paquetesAPagarIndices.empty()) {
        std::cout << ">> No tienes envios pendientes de pago.\n";
        return;
    }

    std::cout << "Tus envios pendientes de pago:\n";
    for (int index : paquetesAPagarIndices) {
        std::cout << "  ID de Solicitud: " << paquetes[index].idSolicitud
                  << ", Descripcion: " << paquetes[index].descripcion
                  << ", Costo: $" << paquetes[index].costo << "\n";
    }
    int idAPagar;
    std::cout << "\nIngresa el ID de la solicitud que deseas pagar: ";
    std::cin >> idAPagar;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool encontrado = false;
    for (int index : paquetesAPagarIndices) {
        if (paquetes[index].idSolicitud == idAPagar) {
            std::cout << "Procesando pago de $" << paquetes[index].costo << " para el envio " << idAPagar << "...\n";
            paquetes[index].estado = "En Transito";
            std::cout << "Pago realizado con exito! El estado de tu envio ahora es 'En Transito'.\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << ">> Error: ID de solicitud no valido o ya ha sido pagado.\n";
    }
}

void SistemaEnvios::bajaUsuario() {
    std::cout << "\n--- Baja de Usuario por Nombre ---\n";
    std::string nombreEliminar;
    verClientes(); 
    
    std::cout << "Ingrese el nombre completo del cliente a eliminar: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, nombreEliminar);

    auto it = std::remove_if(usuarios.begin(), usuarios.end(), [&](const Usuario& user) {
        return user.nombre == nombreEliminar && user.tipoUsuario == "Cliente";
    });

    if (it != usuarios.end()) {
        usuarios.erase(it, usuarios.end());
        std::cout << ">> Cliente '" << nombreEliminar << "' eliminado con exito.\n";
    } else {
        std::cout << ">> Error: Cliente no encontrado con ese nombre.\n";
    }
}

void SistemaEnvios::verSolicitudesPendientes() {
    std::cout << "\n--- Solicitudes de Envio Pendientes de Asignacion ---\n";
    bool encontradas = false;
    for (const auto& paquete : paquetes) {
        if (paquete.estado == "Solicitado") {
            std::cout << "---------------------------------\n";
            paquete.mostrarDetalles(); 
            encontradas = true;
        }
    }
    if (!encontradas) {
        std::cout << ">> No hay solicitudes pendientes.\n";
    }
}

void SistemaEnvios::asignarEnvio() {
    std::cout << "\n--- Asignar Envio a Mensajero ---\n";
    verSolicitudesPendientes(); 
    bool hayPendientes = false;
    for (const auto& paquete : paquetes) {
        if (paquete.estado == "Solicitado") {
            hayPendientes = true;
            break;
        }
    }
    if (!hayPendientes) {
        return; 
    }

    int idSolicitud;
    std::string nombreMensajero;

    std::cout << "\nIngrese el ID de la solicitud a asignar: ";
    while (!(std::cin >> idSolicitud)) {
        std::cout << "\033[31m>> Error: Por favor, ingrese un numero de ID valido:\033[0m\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    
    std::cout << "Ingrese el nombre del MENSAJERO para la recoleccion: ";
    getline(std::cin, nombreMensajero);

    std::string idMensajeroEncontrado = "";
    for (const auto& user : usuarios) {
        if (user.nombre == nombreMensajero) {
            idMensajeroEncontrado = user.idUsuario;
            break; 
        }
    }

    if (idMensajeroEncontrado.empty()) {
        std::cout << ">> Error: No se encontro un mensajero con el nombre '" << nombreMensajero << "'.\n";
        return;
    }

    bool paqueteAsignado = false;
    for (auto& paquete : paquetes) {
        if (paquete.idSolicitud == idSolicitud && paquete.estado == "Solicitado") {
            paquete.estado = "En recoleccion";
            paquete.idMensajeroAsignado = idMensajeroEncontrado;
            
            std::cout << "\n>> ¡Mensaje enviado al mensajero " << nombreMensajero << "!\n";
            std::cout << "   Asignado para recolectar el paquete #" << idSolicitud << ".\n";
            
            paqueteAsignado = true;
            break;
        }
    }

    if (!paqueteAsignado) {
        std::cout << ">> Error: ID de solicitud no valido o ya fue asignado.\n";
    }
}

void SistemaEnvios::verClientes() {
    std::cout << "\n--- Listado de Todos los Clientes ---\n";
    bool clientesEncontrados = false;

    for (const auto& user : usuarios) {
        if (user.tipoUsuario == "Cliente") {
            std::cout << "---------------------------------\n"
                      << "ID:         " << user.idUsuario << "\n"
                      << "Nombre:     " << user.nombre << "\n"
                      << "Email:      " << user.email << "\n"
                      << "Teléfono:   " << user.telefono << "\n";
            clientesEncontrados = true;
        }
    }

    if (!clientesEncontrados) {
        std::cout << ">> No hay clientes registrados en el sistema.\n";
    }
    std::cout << "---------------------------------\n";
}

void SistemaEnvios::verMisEntregasAsignadas() {
    std::cout << "\n--- Mis Entregas Asignadas ---\n";
    bool encontradas = false;
    for (const auto& paquete : paquetes) {
        if (paquete.idMensajeroAsignado == usuarioActual->idUsuario) {
            std::string nombreCliente = "N/A";
            for (const auto& user : usuarios) {
                if (user.idUsuario == paquete.idCliente) {
                    nombreCliente = user.nombre;
                    break;
                }
            }
            std::cout << "---------------------------------\n"
                      << "ID Solicitud: " << paquete.idSolicitud << "\n"
                      << "Cliente:      " << nombreCliente << "\n"
                      << "Estado Actual:  " << paquete.estado << "\n";
            encontradas = true;
        }
    }
    if (!encontradas) {
        std::cout << ">> No tienes entregas asignadas.\n";
    }
}

void SistemaEnvios::marcarComoEntregado() {
    verMisEntregasAsignadas(); 
    
    int idSolicitud;
    std::cout << "\nIngrese el ID de la solicitud que ha sido entregada: ";
    std::cin >> idSolicitud;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool actualizado = false;
    for (auto& paquete : paquetes) {
        if (paquete.idSolicitud == idSolicitud && paquete.idMensajeroAsignado == usuarioActual->idUsuario) {
            if (paquete.estado == "En recoleccion") {
                 paquete.estado = "Entregado";
                 std::cout << ">> ¡Paquete #" << idSolicitud << " marcado como ENTREGADO!\n";
                 actualizado = true;
                 break;
            } else {
                 std::cout << ">> Error: Solo puedes marcar como entregado un paquete que esta 'En recoleccion'.\n";
                 actualizado = true; 
                 break;
            }
        }
    }

    if (!actualizado) {
        std::cout << ">> Error: ID de solicitud no valido o no asignado a ti.\n";
    }
}