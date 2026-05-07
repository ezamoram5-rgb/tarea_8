#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona {
protected:
    std::string nombres;
    std::string apellidos;
    std::string direccion;
    std::string telefono;

public:
    Persona();

    Persona(
        std::string nombres,
        std::string apellidos,
        std::string direccion,
        std::string telefono
    );

    std::string getNombres();
    std::string getApellidos();
    std::string getDireccion();
    std::string getTelefono();

    void setNombres(std::string nombres);
    void setApellidos(std::string apellidos);
    void setDireccion(std::string direccion);
    void setTelefono(std::string telefono);
};

#endif