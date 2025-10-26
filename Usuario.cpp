
#include "Usuario.h"

Usuario::Usuario(std::string id, std::string nom, std::string mail, std::string pass, std::string tipo)
    : idUsuario(id), nombre(nom), email(mail), password(pass), tipoUsuario(tipo) {
}

Usuario::Usuario() = default;

// Leave a comment to not lose my daily goals in git hub