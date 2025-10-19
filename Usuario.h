// Usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
public:
    std::string idUsuario;
    std::string telefono;
    std::string nombre;
    std::string email;
    std::string password;
    std::string tipoUsuario;

    Usuario(std::string id, std::string nom, std::string mail, std::string pass, std::string tipo);
    Usuario();
};

#endif