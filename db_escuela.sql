CREATE DATABASE IF NOT EXISTS db_escuela
  CHARACTER SET utf8mb4
  COLLATE utf8mb4_unicode_ci;

USE db_escuela;

CREATE TABLE IF NOT EXISTS tipos_sangre (
  id_tipo_sangre INT AUTO_INCREMENT PRIMARY KEY,
  sangre VARCHAR(5) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS estudiantes (
  id_estudiante INT AUTO_INCREMENT PRIMARY KEY,
  codigo VARCHAR(4) NOT NULL UNIQUE,
  nombres VARCHAR(60) NOT NULL,
  apellidos VARCHAR(60) NOT NULL,
  direccion VARCHAR(100) NOT NULL,
  telefono VARCHAR(8) NOT NULL,
  fecha_nacimiento DATE NOT NULL,
  id_tipo_sangre INT NOT NULL,
  CONSTRAINT fk_estudiantes_tipos_sangre
    FOREIGN KEY (id_tipo_sangre)
    REFERENCES tipos_sangre(id_tipo_sangre)
);

INSERT IGNORE INTO tipos_sangre (sangre) VALUES
('O+'),
('O-'),
('A+'),
('A-'),
('B+'),
('B-'),
('AB+'),
('AB-');
