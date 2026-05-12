
    //const char* servidor = "localhost";
    //const char* usuario = "root";
    //const char* password = "59098233";
    //const char* base_datos = "db_escuela";
    //unsigned int puerto = 3306;
#include "ConexionBD.h"

ConexionBD::ConexionBD() {
    this->servidor = "tcp://127.0.0.1:3306";
    this->usuario = "root";
    this->password = "59098233";
    this->baseDatos = "db_escuela";
}

sql::Connection* ConexionBD::conectar() {
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* conexion;

        driver = sql::mysql::get_mysql_driver_instance();
        conexion = driver->connect(this->servidor, this->usuario, this->password);
        conexion->setSchema(this->baseDatos);

        return conexion;
    }
    catch (sql::SQLException& e) {
        std::cout << "Error al conectar con MySQL." << std::endl;
        std::cout << "Mensaje: " << e.what() << std::endl;
        std::cout << "Codigo de error: " << e.getErrorCode() << std::endl;
        return nullptr;
    }
}
