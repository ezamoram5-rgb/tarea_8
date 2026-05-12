#include "Estudiante.h"
#include <ctime>

static bool esBisiesto(int anio) {
    if (anio % 400 == 0) return true;
    if (anio % 100 == 0) return false;
    return anio % 4 == 0;
}

static bool fechaReal(int anio, int mes, int dia) {
    if (anio < 1900 || mes < 1 || mes > 12) return false;

    int diasMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (esBisiesto(anio)) diasMes[1] = 29;

    return dia >= 1 && dia <= diasMes[mes - 1];
}

static bool fechaFutura(int anio, int mes, int dia) {
    time_t tiempoActual = time(0);
    tm fechaActual;
    localtime_s(&fechaActual, &tiempoActual);

    int anioActual = fechaActual.tm_year + 1900;
    int mesActual = fechaActual.tm_mon + 1;
    int diaActual = fechaActual.tm_mday;

    if (anio > anioActual) return true;
    if (anio == anioActual && mes > mesActual) return true;
    return anio == anioActual && mes == mesActual && dia > diaActual;
}

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
    std::string telefono,
    std::string fecha_nacimiento,
    int id_tipo_sangre
) : Persona(nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) {
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
    std::regex patron("^[A-Za-z ]+$");

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
    std::regex patron("^[A-Za-z ]+$");

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
    std::string peligrosos[] = {
        "'", "\"", ";", "--", "/*", "*/", "\\",
        "DROP", "drop", "DELETE", "delete",
        "INSERT", "insert", "UPDATE", "update",
        "SELECT", "select"
    };

    if (this->direccion.empty()) {
        std::cout << "La direccion es obligatoria." << std::endl;
        return false;
    }

    if (this->direccion.length() > 100) {
        std::cout << "La direccion debe tener maximo 100 caracteres." << std::endl;
        return false;
    }

    for (std::string texto : peligrosos) {
        if (this->direccion.find(texto) != std::string::npos) {
            std::cout << "La direccion contiene caracteres o palabras no permitidas." << std::endl;
            return false;
        }
    }

    return true;
}

bool Estudiante::validarTelefono() {
    std::regex patron("^[0-9]+$");

    if (this->telefono.empty()) {
        std::cout << "El telefono es obligatorio." << std::endl;
        return false;
    }

    if (this->telefono.length() != 8) {
        std::cout << "El telefono debe tener exactamente 8 digitos." << std::endl;
        return false;
    }

    if (!std::regex_match(this->telefono, patron)) {
        std::cout << "El telefono solo debe contener numeros." << std::endl;
        return false;
    }

    return true;
}

bool Estudiante::validarFechaNacimiento() {
    std::regex patron("^\\d{4}-\\d{2}-\\d{2}$");

    if (this->fecha_nacimiento.empty()) {
        std::cout << "La fecha de nacimiento es obligatoria." << std::endl;
        return false;
    }

    if (!std::regex_match(this->fecha_nacimiento, patron)) {
        std::cout << "La fecha debe tener formato AAAA-MM-DD." << std::endl;
        return false;
    }

    int anio = std::stoi(this->fecha_nacimiento.substr(0, 4));
    int mes = std::stoi(this->fecha_nacimiento.substr(5, 2));
    int dia = std::stoi(this->fecha_nacimiento.substr(8, 2));

    if (!fechaReal(anio, mes, dia)) {
        std::cout << "La fecha ingresada no es real." << std::endl;
        return false;
    }

    if (fechaFutura(anio, mes, dia)) {
        std::cout << "No se permiten fechas futuras." << std::endl;
        return false;
    }

    return true;
}

bool Estudiante::validarTipoSangre() {
    if (this->id_tipo_sangre <= 0) {
        std::cout << "El tipo de sangre es obligatorio y debe ser numerico." << std::endl;
        return false;
    }

    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return false;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> consulta(
            conexion->prepareStatement("SELECT COUNT(*) AS total FROM tipos_sangre WHERE id_tipo_sangre = ?")
        );

        consulta->setInt(1, this->id_tipo_sangre);

        std::unique_ptr<sql::ResultSet> resultado(consulta->executeQuery());

        bool existe = false;
        if (resultado->next()) {
            existe = resultado->getInt("total") > 0;
        }

        delete conexion;

        if (!existe) {
            std::cout << "El tipo de sangre ingresado no existe." << std::endl;
        }

        return existe;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al validar tipo de sangre: " << e.what() << std::endl;
        delete conexion;
        return false;
    }
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

        std::unique_ptr<sql::ResultSet> resultado(consulta->executeQuery());

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

        std::unique_ptr<sql::ResultSet> resultado(consulta->executeQuery());

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

bool Estudiante::estudianteExiste() {
    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return false;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> consulta(
            conexion->prepareStatement("SELECT COUNT(*) AS total FROM estudiantes WHERE id_estudiante = ?")
        );

        consulta->setInt(1, this->id_estudiante);

        std::unique_ptr<sql::ResultSet> resultado(consulta->executeQuery());

        bool existe = false;
        if (resultado->next()) {
            existe = resultado->getInt("total") > 0;
        }

        delete conexion;
        return existe;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al validar estudiante: " << e.what() << std::endl;
        delete conexion;
        return false;
    }
}

void Estudiante::crear() {
    if (!validarCodigo()) return;
    if (!validarNombres()) return;
    if (!validarApellidos()) return;
    if (!validarDireccion()) return;
    if (!validarTelefono()) return;
    if (!validarFechaNacimiento()) return;
    if (!validarTipoSangre()) return;

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
                "(codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) "
                "VALUES (?, ?, ?, ?, ?, ?, ?)"
            )
        );

        consulta->setString(1, this->codigo);
        consulta->setString(2, this->nombres);
        consulta->setString(3, this->apellidos);
        consulta->setString(4, this->direccion);
        consulta->setString(5, this->telefono);
        consulta->setString(6, this->fecha_nacimiento);
        consulta->setInt(7, this->id_tipo_sangre);

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
        std::unique_ptr<sql::Statement> consulta(conexion->createStatement());

        std::unique_ptr<sql::ResultSet> resultado(
            consulta->executeQuery(
                "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, e.direccion, "
                "e.telefono, e.fecha_nacimiento, ts.sangre "
                "FROM estudiantes e "
                "LEFT JOIN tipos_sangre ts ON e.id_tipo_sangre = ts.id_tipo_sangre "
                "ORDER BY e.id_estudiante ASC"
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
            std::cout << "Fecha nacimiento: " << resultado->getString("fecha_nacimiento") << std::endl;
            std::cout << "Tipo sangre: " << resultado->getString("sangre") << std::endl;
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
                "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, e.direccion, "
                "e.telefono, e.fecha_nacimiento, ts.sangre "
                "FROM estudiantes e "
                "LEFT JOIN tipos_sangre ts ON e.id_tipo_sangre = ts.id_tipo_sangre "
                "WHERE e.id_estudiante = ?"
            )
        );

        consulta->setInt(1, this->id_estudiante);

        std::unique_ptr<sql::ResultSet> resultado(consulta->executeQuery());

        if (resultado->next()) {
            std::cout << std::endl;
            std::cout << "=========== ESTUDIANTE ENCONTRADO ===========" << std::endl;
            std::cout << "ID: " << resultado->getInt("id_estudiante") << std::endl;
            std::cout << "Codigo: " << resultado->getString("codigo") << std::endl;
            std::cout << "Nombres: " << resultado->getString("nombres") << std::endl;
            std::cout << "Apellidos: " << resultado->getString("apellidos") << std::endl;
            std::cout << "Direccion: " << resultado->getString("direccion") << std::endl;
            std::cout << "Telefono: " << resultado->getString("telefono") << std::endl;
            std::cout << "Fecha nacimiento: " << resultado->getString("fecha_nacimiento") << std::endl;
            std::cout << "Tipo sangre: " << resultado->getString("sangre") << std::endl;
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

    if (!estudianteExiste()) {
        std::cout << "No existe un estudiante con ese ID." << std::endl;
        return;
    }

    if (!validarCodigo()) return;
    if (!validarNombres()) return;
    if (!validarApellidos()) return;
    if (!validarDireccion()) return;
    if (!validarTelefono()) return;
    if (!validarFechaNacimiento()) return;
    if (!validarTipoSangre()) return;

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
                "codigo = ?, nombres = ?, apellidos = ?, direccion = ?, telefono = ?, "
                "fecha_nacimiento = ?, id_tipo_sangre = ? "
                "WHERE id_estudiante = ?"
            )
        );

        consulta->setString(1, this->codigo);
        consulta->setString(2, this->nombres);
        consulta->setString(3, this->apellidos);
        consulta->setString(4, this->direccion);
        consulta->setString(5, this->telefono);
        consulta->setString(6, this->fecha_nacimiento);
        consulta->setInt(7, this->id_tipo_sangre);
        consulta->setInt(8, this->id_estudiante);

        consulta->executeUpdate();

        std::cout << "Estudiante actualizado correctamente." << std::endl;

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

    if (!estudianteExiste()) {
        std::cout << "No existe un estudiante con ese ID." << std::endl;
        return;
    }

    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> consulta(
            conexion->prepareStatement("DELETE FROM estudiantes WHERE id_estudiante = ?")
        );

        consulta->setInt(1, this->id_estudiante);
        consulta->executeUpdate();

        std::cout << "Estudiante eliminado correctamente." << std::endl;

        delete conexion;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al eliminar estudiante: " << e.what() << std::endl;
        delete conexion;
    }
}
