#pragma once
#include "company.h"

//  Registros

typedef struct Reparacion {
  int id;
  int dispositivo;// [1] PC - [2] Netbook - [3] Celular
  char fecha[11];
  float costoHardware;
  float costoSoftware;
  float precioFinal;
  Empleado empleado;
  Empresa empresa;
  struct Reparacion *siguiente;
} Reparacion;

extern Reparacion* Primero;
extern Reparacion* Ultimo;

//  Funciones y Procedimientos

void cargarID(Reparacion *reparacion);
char *DispositivoReparado(char dispositivoReparado[20], Reparacion *reparacion);
float CalcularPrecioFinal(Reparacion *reparacion);
void cargarFechaReparacion(Reparacion *reparacion);
void cargarEmpleadoAReparacion(Reparacion *reparacion, int *codigoEmpleado);
void cargarEmpresaAReparacion(Reparacion *reparacion);
void cargarReparacion(Reparacion *reparacion, int *codigoEmpleado);
void crearReparacion(int *codigoEmpleado);
void almacenarReparaciones();
void mostrarReparaciones();
void liberarMemoria();
void modificarReparacion(int id);
void eliminarReparacion(int id);