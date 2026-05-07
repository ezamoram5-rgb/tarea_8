#ifndef CONEXIONBD_H
#define CONEXIONBD_H

#ifndef _HAS_STD_BYTE
#define _HAS_STD_BYTE 0
#endif

#include <iostream>
#include <string>

#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>

class ConexionBD {
private:
    std::string servidor;
    std::string usuario;
    std::string password;
    std::string baseDatos;

public:
    ConexionBD();

    sql::Connection* conectar();
};

#endif