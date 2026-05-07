#include "Estudiante.h"

Estudiante::Estudiante() : Persona() {
    this->id_estudiante = 0;
    this->codigo = "";
}

Estudiante::Estudiante(
    int id_estudiante,
    std::string codigo,
    std::string nombres,
    std::string apellidos,
    std::string direccion,
    std::string telefono
) : Persona(nombres, apellidos, direccion, telefono) {
    this->id_estudiante = id_estudiante;
    this->codigo = codigo;
}

int Estudiante::getIdEstudiante() {
    return this->id_estudiante;
}

std::string Estudiante::getCodigo() {
    return this->codigo;
}

void Estudiante::setIdEstudiante(int id_estudiante) {
    this->id_estudiante = id_estudiante;
}

void Estudiante::setCodigo(std::string codigo) {
    this->codigo = codigo;
}

bool Estudiante::validarCodigo() {
    std::regex patron("^E[0-9]{3}$");

    if (this->codigo.empty()) {
        std::cout << "El codigo es obligatorio." << std::endl;
        return false;
    }

    if (this->codigo.length() > 4) {
        std::cout << "El codigo debe tener maximo 4 caracteres." << std::endl;
        return false;
    }

    if (!std::regex_match(this->codigo, patron)) {
        std::cout << "Formato incorrecto. Ejemplo valido: E001, E002, E003." << std::endl;
        return false;
    }

    return true;
}

bool Estudiante::validarNombres() {
    std::regex patron("^[A-Za-zÁÉÍÓÚáéíóúÑñ ]+$");

    if (this->nombres.empty()) {
        std::cout << "Los nombres son obligatorios." << std::endl;
        return false;
    }

    if (this->nombres.length() > 60) {
        std::cout << "Los nombres deben tener maximo 60 caracteres." << std::endl;
        return false;
    }

    if (!std::regex_match(this->nombres, patron)) {
        std::cout << "Los nombres solo deben contener letras y espacios." << std::endl;
        return false;
    }

    return true;
}

bool Estudiante::validarApellidos() {
    std::regex patron("^[A-Za-zÁÉÍÓÚáéíóúÑñ ]+$");

    if (this->apellidos.empty()) {
        std::cout << "Los apellidos son obligatorios." << std::endl;
        return false;
    }

    if (this->apellidos.length() > 60) {
        std::cout << "Los apellidos deben tener maximo 60 caracteres." << std::endl;
        return false;
    }

    if (!std::regex_match(this->apellidos, patron)) {
        std::cout << "Los apellidos solo deben contener letras y espacios." << std::endl;
        return false;
    }

    return true;
}

bool Estudiante::validarDireccion() {
    if (this->direccion.empty()) {
        std::cout << "La direccion es obligatoria." << std::endl;
        return false;
    }

    if (this->direccion.length() > 100) {
        std::cout << "La direccion debe tener maximo 100 caracteres." << std::endl;
        return false;
    }

    return true;
}

bool Estudiante::validarTelefono() {
    std::regex patron("^[0-9]+$");

    if (this->telefono.empty()) {
        std::cout << "El telefono es obligatorio." << std::endl;
        return false;
    }

    if (this->telefono.length() < 8 || this->telefono.length() > 15) {
        std::cout << "El telefono debe tener entre 8 y 15 digitos." << std::endl;
        return false;
    }

    if (!std::regex_match(this->telefono, patron)) {
        std::cout << "El telefono solo debe contener numeros." << std::endl;
        return false;
    }

    return true;
}

bool Estudiante::codigoExiste() {
    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return true;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> consulta(
            conexion->prepareStatement("SELECT COUNT(*) AS total FROM estudiantes WHERE codigo = ?")
        );

        consulta->setString(1, this->codigo);

        std::unique_ptr<sql::ResultSet> resultado(
            consulta->executeQuery()
        );

        bool existe = false;

        if (resultado->next()) {
            existe = resultado->getInt("total") > 0;
        }

        delete conexion;
        return existe;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al validar codigo duplicado: " << e.what() << std::endl;
        delete conexion;
        return true;
    }
}

bool Estudiante::codigoExisteEnOtroRegistro() {
    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return true;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> consulta(
            conexion->prepareStatement(
                "SELECT COUNT(*) AS total FROM estudiantes WHERE codigo = ? AND id_estudiante <> ?"
            )
        );

        consulta->setString(1, this->codigo);
        consulta->setInt(2, this->id_estudiante);

        std::unique_ptr<sql::ResultSet> resultado(
            consulta->executeQuery()
        );

        bool existe = false;

        if (resultado->next()) {
            existe = resultado->getInt("total") > 0;
        }

        delete conexion;
        return existe;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al validar codigo duplicado: " << e.what() << std::endl;
        delete conexion;
        return true;
    }
}

void Estudiante::crear() {
    if (!validarCodigo()) return;
    if (!validarNombres()) return;
    if (!validarApellidos()) return;
    if (!validarDireccion()) return;
    if (!validarTelefono()) return;

    if (codigoExiste()) {
        std::cout << "No se puede registrar. El codigo ya existe." << std::endl;
        return;
    }

    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> consulta(
            conexion->prepareStatement(
                "INSERT INTO estudiantes "
                "(codigo, nombres, apellidos, direccion, telefono) "
                "VALUES (?, ?, ?, ?, ?)"
            )
        );

        consulta->setString(1, this->codigo);
        consulta->setString(2, this->nombres);
        consulta->setString(3, this->apellidos);
        consulta->setString(4, this->direccion);
        consulta->setString(5, this->telefono);

        consulta->executeUpdate();

        std::cout << "Estudiante registrado correctamente." << std::endl;

        delete conexion;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al registrar estudiante: " << e.what() << std::endl;
        delete conexion;
    }
}

void Estudiante::mostrarTodos() {
    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return;
    }

    try {
        std::unique_ptr<sql::Statement> consulta(
            conexion->createStatement()
        );

        std::unique_ptr<sql::ResultSet> resultado(
            consulta->executeQuery(
                "SELECT id_estudiante, codigo, nombres, apellidos, direccion, telefono "
                "FROM estudiantes ORDER BY id_estudiante ASC"
            )
        );

        std::cout << std::endl;
        std::cout << "=========== LISTADO DE ESTUDIANTES ===========" << std::endl;

        while (resultado->next()) {
            std::cout << "ID: " << resultado->getInt("id_estudiante") << std::endl;
            std::cout << "Codigo: " << resultado->getString("codigo") << std::endl;
            std::cout << "Nombres: " << resultado->getString("nombres") << std::endl;
            std::cout << "Apellidos: " << resultado->getString("apellidos") << std::endl;
            std::cout << "Direccion: " << resultado->getString("direccion") << std::endl;
            std::cout << "Telefono: " << resultado->getString("telefono") << std::endl;
            std::cout << "---------------------------------------------" << std::endl;
        }

        delete conexion;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al mostrar estudiantes: " << e.what() << std::endl;
        delete conexion;
    }
}

void Estudiante::buscarPorId() {
    if (this->id_estudiante <= 0) {
        std::cout << "El ID debe ser mayor a cero." << std::endl;
        return;
    }

    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> consulta(
            conexion->prepareStatement(
                "SELECT id_estudiante, codigo, nombres, apellidos, direccion, telefono "
                "FROM estudiantes WHERE id_estudiante = ?"
            )
        );

        consulta->setInt(1, this->id_estudiante);

        std::unique_ptr<sql::ResultSet> resultado(
            consulta->executeQuery()
        );

        if (resultado->next()) {
            std::cout << std::endl;
            std::cout << "=========== ESTUDIANTE ENCONTRADO ===========" << std::endl;
            std::cout << "ID: " << resultado->getInt("id_estudiante") << std::endl;
            std::cout << "Codigo: " << resultado->getString("codigo") << std::endl;
            std::cout << "Nombres: " << resultado->getString("nombres") << std::endl;
            std::cout << "Apellidos: " << resultado->getString("apellidos") << std::endl;
            std::cout << "Direccion: " << resultado->getString("direccion") << std::endl;
            std::cout << "Telefono: " << resultado->getString("telefono") << std::endl;
        }
        else {
            std::cout << "No existe un estudiante con ese ID." << std::endl;
        }

        delete conexion;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al buscar estudiante: " << e.what() << std::endl;
        delete conexion;
    }
}

void Estudiante::actualizar() {
    if (this->id_estudiante <= 0) {
        std::cout << "El ID debe ser mayor a cero." << std::endl;
        return;
    }

    if (!validarCodigo()) return;
    if (!validarNombres()) return;
    if (!validarApellidos()) return;
    if (!validarDireccion()) return;
    if (!validarTelefono()) return;

    if (codigoExisteEnOtroRegistro()) {
        std::cout << "No se puede actualizar. El codigo ya pertenece a otro estudiante." << std::endl;
        return;
    }

    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> consulta(
            conexion->prepareStatement(
                "UPDATE estudiantes SET "
                "codigo = ?, nombres = ?, apellidos = ?, direccion = ?, telefono = ? "
                "WHERE id_estudiante = ?"
            )
        );

        consulta->setString(1, this->codigo);
        consulta->setString(2, this->nombres);
        consulta->setString(3, this->apellidos);
        consulta->setString(4, this->direccion);
        consulta->setString(5, this->telefono);
        consulta->setInt(6, this->id_estudiante);

        int filas = consulta->executeUpdate();

        if (filas > 0) {
            std::cout << "Estudiante actualizado correctamente." << std::endl;
        }
        else {
            std::cout << "No se encontro el estudiante para actualizar." << std::endl;
        }

        delete conexion;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al actualizar estudiante: " << e.what() << std::endl;
        delete conexion;
    }
}

void Estudiante::eliminar() {
    if (this->id_estudiante <= 0) {
        std::cout << "El ID debe ser mayor a cero." << std::endl;
        return;
    }

    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> consulta(
            conexion->prepareStatement(
                "DELETE FROM estudiantes WHERE id_estudiante = ?"
            )
        );

        consulta->setInt(1, this->id_estudiante);

        int filas = consulta->executeUpdate();

        if (filas > 0) {
            std::cout << "Estudiante eliminado correctamente." << std::endl;
        }
        else {
            std::cout << "No se encontro el estudiante para eliminar." << std::endl;
        }

        delete conexion;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al eliminar estudiante: " << e.what() << std::endl;
        delete conexion;
    }
}