#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#ifndef _HAS_STD_BYTE
#define _HAS_STD_BYTE 0
#endif

#include <iostream>
#include <string>
#include <regex>
#include <memory>

#include "Persona.h"
#include "ConexionBD.h"

#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>

class Estudiante : public Persona {
private:
    int id_estudiante;
    std::string codigo;

public:
    Estudiante();

    Estudiante(
        int id_estudiante,
        std::string codigo,
        std::string nombres,
        std::string apellidos,
        std::string direccion,
        std::string telefono
    );

    int getIdEstudiante();
    std::string getCodigo();

    void setIdEstudiante(int id_estudiante);
    void setCodigo(std::string codigo);

    bool validarCodigo();
    bool validarNombres();
    bool validarApellidos();
    bool validarDireccion();
    bool validarTelefono();

    bool codigoExiste();
    bool codigoExisteEnOtroRegistro();

    void crear();
    void mostrarTodos();
    void buscarPorId();
    void actualizar();
    void eliminar();
};

#endif