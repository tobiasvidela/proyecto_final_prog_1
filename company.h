#pragma once

//  Registros de la Empresa "El Cuyanito"

typedef struct Empleado {
  int codigo;
  char dni[9];
  char cuil[15];
  char nombres[40];
  char apellidos[40];
} Empleado;
typedef struct Empresa {
  int codigo;
  char cuit[15];
  char nombre[40];
} Empresa;

// Funciones y Procedimientos

int ValidarEmpleado();
void mostrarEmpleados();
void mostrarEmpresas();
void modificarEmpleado(int codigo);
void eliminarEmpleado(int codigo);
void modificarEmpresa(int codigo);
void eliminarEmpresa(int codigo);