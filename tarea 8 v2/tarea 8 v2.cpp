#include <iostream>
#include <string>

#include "Estudiante.h"

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int leerEntero(std::string mensaje) {
    int valor;

    while (true) {
        std::cout << mensaje;
        std::cin >> valor;

        if (std::cin.fail()) {
            std::cout << "Debe ingresar un numero valido." << std::endl;
            limpiarBuffer();
        }
        else {
            limpiarBuffer();
            return valor;
        }
    }
}

std::string leerTexto(std::string mensaje) {
    std::string texto;

    std::cout << mensaje;
    std::getline(std::cin, texto);

    return texto;
}

void registrarEstudiante() {
    std::string codigo;
    std::string nombres;
    std::string apellidos;
    std::string direccion;
    std::string telefono;
    std::string fecha_nacimiento;
    int id_tipo_sangre;

    std::cout << std::endl;
    std::cout << "=========== REGISTRAR ESTUDIANTE ===========" << std::endl;
    std::cout << "Instrucciones:" << std::endl;
    std::cout << "- El ID no se ingresa porque es automatico." << std::endl;
    std::cout << "- Codigo obligatorio. Ejemplo: E001." << std::endl;
    std::cout << "- Nombres y apellidos solo permiten letras y espacios." << std::endl;
    std::cout << "- Telefono solo permite numeros." << std::endl;
    std::cout << "- Fecha de nacimiento en formato AAAA-MM-DD." << std::endl;
    std::cout << "- El tipo de sangre debe existir en la tabla tipos_sangre." << std::endl;
    std::cout << std::endl;

    codigo = leerTexto("Ingrese codigo: ");
    nombres = leerTexto("Ingrese nombres: ");
    apellidos = leerTexto("Ingrese apellidos: ");
    direccion = leerTexto("Ingrese direccion: ");
    telefono = leerTexto("Ingrese telefono: ");
    fecha_nacimiento = leerTexto("Ingrese fecha de nacimiento AAAA-MM-DD: ");
    id_tipo_sangre = leerEntero("Ingrese ID tipo de sangre: ");

    Estudiante estudiante(
        0,
        codigo,
        nombres,
        apellidos,
        direccion,
        telefono,
        fecha_nacimiento,
        id_tipo_sangre
    );

    estudiante.crear();
}

void mostrarEstudiantes() {
    Estudiante estudiante;
    estudiante.mostrarTodos();
}

void mostrarTiposSangre() {
    ConexionBD db;
    sql::Connection* conexion = db.conectar();

    if (conexion == nullptr) {
        return;
    }

    try {
        std::unique_ptr<sql::Statement> consulta(conexion->createStatement());
        std::unique_ptr<sql::ResultSet> resultado(
            consulta->executeQuery("SELECT id_tipo_sangre, sangre FROM tipos_sangre ORDER BY id_tipo_sangre ASC")
        );

        std::cout << std::endl;
        std::cout << "=========== TIPOS DE SANGRE ===========" << std::endl;

        while (resultado->next()) {
            std::cout << "ID: " << resultado->getInt("id_tipo_sangre")
                << " | Tipo: " << resultado->getString("sangre") << std::endl;
        }

        delete conexion;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al mostrar tipos de sangre: " << e.what() << std::endl;
        delete conexion;
    }
}

void buscarEstudiante() {
    int id;

    std::cout << std::endl;
    std::cout << "=========== BUSCAR ESTUDIANTE ===========" << std::endl;

    id = leerEntero("Ingrese ID del estudiante: ");

    Estudiante estudiante;
    estudiante.setIdEstudiante(id);
    estudiante.buscarPorId();
}

void actualizarEstudiante() {
    int id;
    std::string codigo;
    std::string nombres;
    std::string apellidos;
    std::string direccion;
    std::string telefono;
    std::string fecha_nacimiento;
    int id_tipo_sangre;

    std::cout << std::endl;
    std::cout << "=========== ACTUALIZAR ESTUDIANTE ===========" << std::endl;
    std::cout << "Instrucciones:" << std::endl;
    std::cout << "- Debe ingresar el ID del estudiante que desea modificar." << std::endl;
    std::cout << "- Codigo obligatorio. Ejemplo: E001." << std::endl;
    std::cout << "- Nombres y apellidos solo permiten letras y espacios." << std::endl;
    std::cout << "- Telefono solo permite numeros." << std::endl;
    std::cout << "- Fecha de nacimiento en formato AAAA-MM-DD." << std::endl;
    std::cout << "- El tipo de sangre debe existir en la tabla tipos_sangre." << std::endl;
    std::cout << std::endl;

    id = leerEntero("Ingrese ID del estudiante: ");

    codigo = leerTexto("Ingrese nuevo codigo: ");
    nombres = leerTexto("Ingrese nuevos nombres: ");
    apellidos = leerTexto("Ingrese nuevos apellidos: ");
    direccion = leerTexto("Ingrese nueva direccion: ");
    telefono = leerTexto("Ingrese nuevo telefono: ");
    fecha_nacimiento = leerTexto("Ingrese nueva fecha de nacimiento AAAA-MM-DD: ");
    id_tipo_sangre = leerEntero("Ingrese nuevo ID tipo de sangre: ");

    Estudiante estudiante(
        id,
        codigo,
        nombres,
        apellidos,
        direccion,
        telefono,
        fecha_nacimiento,
        id_tipo_sangre
    );

    estudiante.actualizar();
}

void eliminarEstudiante() {
    int id;
    char confirmar;

    std::cout << std::endl;
    std::cout << "=========== ELIMINAR ESTUDIANTE ===========" << std::endl;

    id = leerEntero("Ingrese ID del estudiante a eliminar: ");

    std::cout << "Esta seguro de eliminar este registro? S/N: ";
    std::cin >> confirmar;
    limpiarBuffer();

    if (confirmar == 'S' || confirmar == 's') {
        Estudiante estudiante;
        estudiante.setIdEstudiante(id);
        estudiante.eliminar();
    }
    else {
        std::cout << "Eliminacion cancelada." << std::endl;
    }
}

int main() {
    int opcion;

    do {
        std::cout << std::endl;
        std::cout << "============================================" << std::endl;
        std::cout << "          CRUD ESTUDIANTES CON MYSQL        " << std::endl;
        std::cout << "============================================" << std::endl;
        std::cout << "1. Registrar estudiante" << std::endl;
        std::cout << "2. Mostrar estudiantes" << std::endl;
        std::cout << "3. Buscar estudiante por ID" << std::endl;
        std::cout << "4. Actualizar estudiante" << std::endl;
        std::cout << "5. Eliminar estudiante" << std::endl;
        std::cout << "6. Mostrar tipos de sangre" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "============================================" << std::endl;

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
        case 1:
            registrarEstudiante();
            break;

        case 2:
            mostrarEstudiantes();
            break;

        case 3:
            buscarEstudiante();
            break;

        case 4:
            actualizarEstudiante();
            break;

        case 5:
            eliminarEstudiante();
            break;

        case 6:
            mostrarTiposSangre();
            break;

        case 0:
            std::cout << "Saliendo del sistema..." << std::endl;
            break;

        default:
            std::cout << "Opcion no valida." << std::endl;
            break;
        }

    } while (opcion != 0);

    return 0;
}
