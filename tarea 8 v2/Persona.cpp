#include "Persona.h"

Persona::Persona() {
    this->nombres = "";
    this->apellidos = "";
    this->direccion = "";
    this->telefono = "";
    this->fecha_nacimiento = "";
    this->id_tipo_sangre = 0;
}

Persona::Persona(
    std::string nombres,
    std::string apellidos,
    std::string direccion,
    std::string telefono,
    std::string fecha_nacimiento,
    int id_tipo_sangre
) {
    this->nombres = nombres;
    this->apellidos = apellidos;
    this->direccion = direccion;
    this->telefono = telefono;
    this->fecha_nacimiento = fecha_nacimiento;
    this->id_tipo_sangre = id_tipo_sangre;
}

std::string Persona::getNombres() {
    return this->nombres;
}

std::string Persona::getApellidos() {
    return this->apellidos;
}

std::string Persona::getDireccion() {
    return this->direccion;
}

std::string Persona::getTelefono() {
    return this->telefono;
}

std::string Persona::getFechaNacimiento() {
    return this->fecha_nacimiento;
}

int Persona::getIdTipoSangre() {
    return this->id_tipo_sangre;
}

void Persona::setNombres(std::string nombres) {
    this->nombres = nombres;
}

void Persona::setApellidos(std::string apellidos) {
    this->apellidos = apellidos;
}

void Persona::setDireccion(std::string direccion) {
    this->direccion = direccion;
}

void Persona::setTelefono(std::string telefono) {
    this->telefono = telefono;
}

void Persona::setFechaNacimiento(std::string fecha_nacimiento) {
    this->fecha_nacimiento = fecha_nacimiento;
}

void Persona::setIdTipoSangre(int id_tipo_sangre) {
    this->id_tipo_sangre = id_tipo_sangre;
}
