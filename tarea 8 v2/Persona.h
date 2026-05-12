#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona {
protected:
    std::string nombres;
    std::string apellidos;
    std::string direccion;
    std::string telefono;
    std::string fecha_nacimiento;
    int id_tipo_sangre;

public:
    Persona();

    Persona(
        std::string nombres,
        std::string apellidos,
        std::string direccion,
        std::string telefono,
        std::string fecha_nacimiento,
        int id_tipo_sangre
    );

    std::string getNombres();
    std::string getApellidos();
    std::string getDireccion();
    std::string getTelefono();
    std::string getFechaNacimiento();
    int getIdTipoSangre();

    void setNombres(std::string nombres);
    void setApellidos(std::string apellidos);
    void setDireccion(std::string direccion);
    void setTelefono(std::string telefono);
    void setFechaNacimiento(std::string fecha_nacimiento);
    void setIdTipoSangre(int id_tipo_sangre);
};

#endif
