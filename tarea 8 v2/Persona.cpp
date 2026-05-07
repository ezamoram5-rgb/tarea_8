#include "Persona.h"

Persona::Persona() {
    this->nombres = "";
    this->apellidos = "";
    this->direccion = "";
    this->telefono = "";
}

Persona::Persona(
    std::string nombres,
    std::string apellidos,
    std::string direccion,
    std::string telefono
) {
    this->nombres = nombres;
    this->apellidos = apellidos;
    this->direccion = direccion;
    this->telefono = telefono;
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