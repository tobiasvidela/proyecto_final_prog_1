#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "company.h"
#include "reparaciones.h"
#include "busqueda.h"

//EMPLEADOS
void mostrarReparacionesDeEmpleado(int opcion) {
  int codigoABuscar = opcion;
  int existe = ExisteReparacionesPorCodigoEmpleado(codigoABuscar);

  if (existe == 1) {
    limpiarConsola();
    imprimirReparacionesPorCodigoEmpleado(codigoABuscar);
    continuar();
  } else {
    limpiarConsola();
    printf("\n No se ha registrado ninguna reparación realizada por ese/a empleado/a.");
    printf("\n Pruebe a almacenar todas las reparaciones antes de realizar la búsqueda.\n\n");
    continuar();
  }
}
void imprimirReparacionesPorCodigoEmpleado(int codigoABuscar) {
  char dispositivoReparado[20];

  limpiarConsola();
  printf("\n\tReparación/es encontrada/s:\n");
  //  imprimir reparaciones
  printf("\n");
  printf("|%3s","ID");
  printf("|%-11s","Dispositivo");
  printf("|%2s%-6s%2s","","Fecha","");
  printf("|%4s%-6s%4s","","Precio","");
  printf("|%1s%-7s |","","Codigos");
  printf("\n");
  printf("|---|-----------|----------|--------------|---------|");
  //  reparaciones almacenadas
  Reparacion reparacion;
  FILE *reparaciones = fopen("reparaciones.dat", "rb");
  verificarAbrirArchivo(reparaciones);
  while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
    if (reparacion.empleado.codigo == codigoABuscar) {
      printf("\n");
      printf("|%3d",reparacion.id);
      printf("| %-8s%2s", DispositivoReparado(dispositivoReparado, &reparacion),"");
      printf("|%10s", reparacion.fecha);
      printf("|$%12.2f%1s", reparacion.precioFinal,"");
      printf("| %2d%s%2d |", reparacion.empleado.codigo," | ", reparacion.empresa.codigo);
    }
  }
  fclose(reparaciones);
  printf("\n");
  printf("|---|-----------|----------|--------------|---------|");
  printf("\n");
}
int ExisteReparacionesPorCodigoEmpleado(int codigoABuscar) {
  int existe = 0;
  Reparacion reparacion;
  FILE *reparaciones = fopen("reparaciones.dat", "rb");
  verificarAbrirArchivo(reparaciones);
  //BUSCAMOS SI EXISTE UNA REPARACION HECHA POR TAL EMPLEADO
  while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
    if (reparacion.empleado.codigo == codigoABuscar) {
      existe = 1;
    }
  }
  fclose(reparaciones);
  return existe;
}
//EMPRESAS
void mostrarReparacionesAEmpresa(int opcion) {
  int codigoABuscar = opcion;
  int existe = ExisteReparacionesPorCodigoDeEmpresa(codigoABuscar);

  if (existe == 1) {
    limpiarConsola();
    imprimirReparacionesPorCodigoDeEmpresa(codigoABuscar);
    continuar();
  } else {
    limpiarConsola();
    printf("\n No existe ninguna reparación realizada a esa empresa.");
    printf("\n Pruebe a almacenar todas las reparaciones antes de realizar la búsqueda.\n\n");
    continuar();
  }
}
void imprimirReparacionesPorCodigoDeEmpresa(int codigoABuscar) {
  char dispositivoReparado[20];

  limpiarConsola();
  printf("\n\tReparación/es encontrada/s:\n");
  //  imprimir reparaciones
  printf("\n");
  printf("|%3s","ID");
  printf("|%-11s","Dispositivo");
  printf("|%2s%-6s%2s","","Fecha","");
  printf("|%4s%-6s%4s","","Precio","");
  printf("|%1s%-7s |","","Codigos");
  printf("\n");
  printf("|---|-----------|----------|--------------|---------|");
  //  reparaciones almacenadas
  Reparacion reparacion;
  FILE *reparaciones = fopen("reparaciones.dat", "rb");
  verificarAbrirArchivo(reparaciones);
  while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
    if (reparacion.empresa.codigo == codigoABuscar) {
      printf("\n");
      printf("|%3d",reparacion.id);
      printf("| %-8s%2s", DispositivoReparado(dispositivoReparado, &reparacion),"");
      printf("|%10s", reparacion.fecha);
      printf("|$%12.2f%1s", reparacion.precioFinal,"");
      printf("| %2d%s%2d |", reparacion.empleado.codigo," | ", reparacion.empresa.codigo);
    }
  }
  fclose(reparaciones);
  printf("\n");
  printf("|---|-----------|----------|--------------|---------|");
  printf("\n");
}
int ExisteReparacionesPorCodigoDeEmpresa(int codigoABuscar) {
  int existe = 0;
  Reparacion reparacion;
  FILE *reparaciones = fopen("reparaciones.dat", "rb");
  verificarAbrirArchivo(reparaciones);
  while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
    if (reparacion.empresa.codigo == codigoABuscar) {
      existe = 1;
    }
  }
  fclose(reparaciones);
  return existe;
}
//DISPOSITIVO
void buscarDispositivo(){
  Reparacion reparacion;
  char dispositivoReparado[20];
  int existe = 0;
  int opcBuscada = 0;

  printf("\n Ingrese la opción que desea buscar:");
  printf("\n\t[1] PC");
  printf("\n\t[2] Netbook");
  printf("\n\t[3] Celular");
  printf("\n\n");
  do {
    opcBuscada = leerEntero();
  } while (opcBuscada < 1 || opcBuscada > 3);

  FILE* archivo = fopen("reparaciones.dat","rb");
  verificarAbrirArchivo(archivo);
  while(fread(&reparacion, sizeof(Reparacion), 1, archivo) == 1) {
    if (reparacion.dispositivo == opcBuscada) {
      existe = 1;
    }
  }
  fseek(archivo, 0, SEEK_SET);
  if (existe == 1) {
    printf("\n");
    printf("|%3s","ID");
    printf("|%-11s","Dispositivo");
    printf("|%2s%-6s%2s","","Fecha","");
    printf("|%4s%-6s%4s","","Precio","");
    printf("|%1s%-7s |","","Codigos");
    printf("\n");
    printf("|---|-----------|----------|--------------|---------|");
    while(fread(&reparacion, sizeof(Reparacion), 1, archivo) == 1) {
      if (reparacion.dispositivo == opcBuscada) {
        printf("\n");
        printf("|%3d",reparacion.id);
        printf("| %-8s%2s", DispositivoReparado(dispositivoReparado, &reparacion),"");
        printf("|%10s", reparacion.fecha);
        printf("|$%12.2f%1s", reparacion.precioFinal,"");
        printf("| %2d%s%2d |", reparacion.empleado.codigo," | ", reparacion.empresa.codigo);
      }
    }
    printf("\n");
    printf("|---|-----------|----------|--------------|---------|");
    printf("\n");
  } else {
    printf("\n No existen reparaciones almacenadas realizadas a ese dispositivo.\n");
  }
  fclose(archivo);
}
//PRECIO MAXIMO
void buscarPresupuestoMaximo(){
  FILE* archivo = fopen("reparaciones.dat","rb");
  verificarAbrirArchivo(archivo);

  float precioMaximo = - 99999999999.99;
  char dispositivoReparado[20];

  Reparacion reparacion;

  while (fread(&reparacion,sizeof(Reparacion),1,archivo)==1){
    if(reparacion.precioFinal > precioMaximo){
      precioMaximo = reparacion.precioFinal;
    }
  }
  fseek(archivo,0,SEEK_SET);

  if (precioMaximo != - 99999999999.99) {
    printf("El mayor precio final de una reparacion encontrada es: %.2f\n", precioMaximo);
    printf("\n");
    printf("|%3s","ID");
    printf("|%-11s","Dispositivo");
    printf("|%2s%-6s%2s","","Fecha","");
    printf("|%4s%-6s%4s","","Precio","");
    printf("|%1s%-7s |","","Codigos");
    printf("\n");
    printf("|---|-----------|----------|--------------|---------|");
    while(fread(&reparacion, sizeof(Reparacion), 1, archivo) == 1) {
      if (reparacion.precioFinal == precioMaximo) {
        printf("\n");
        printf("|%3d",reparacion.id);
        printf("| %-8s%2s", DispositivoReparado(dispositivoReparado, &reparacion),"");
        printf("|%10s", reparacion.fecha);
        printf("|$%12.2f%1s", reparacion.precioFinal,"");
        printf("| %2d%s%2d |", reparacion.empleado.codigo," | ", reparacion.empresa.codigo);
      }
    }
    printf("\n");
    printf("|---|-----------|----------|--------------|---------|");
    printf("\n");
  } else {
    printf("No se encontró ningún precio máximo en el archivo.\n");
  }
  fclose(archivo);
}
//FECHA
void buscarReparacionesFecha() {
  char fecha[11];
  char fechaBuscada[11];
  char dispositivoReparado[20];
  int found = 0;
  Reparacion reparacion;
  printf("\n Ingrese la fecha a buscar: ");
  strcpy(fechaBuscada,leerFecha(fecha));
  //abrir archivo
  FILE *reparaciones = fopen("reparaciones.dat", "rb");
  verificarAbrirArchivo(reparaciones);
  verificarArchivoVacio(reparaciones);
  //buscar en el archivo
  while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
    if (strstr(reparacion.fecha,fechaBuscada) != NULL) {
      found = 1;
    }
  }
  //imprimir los resultados
  fseek(reparaciones,0,SEEK_SET);
  if (found == 1) {
    printf("\n");
    printf("|%3s","ID");
    printf("|%-11s","Dispositivo");
    printf("|%2s%-6s%2s","","Fecha","");
    printf("|%4s%-6s%4s","","Precio","");
    printf("|%1s%-7s |","","Codigos");
    printf("\n");
    printf("|---|-----------|----------|--------------|---------|");
    while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
      if (strstr(reparacion.fecha,fechaBuscada) != NULL) {
        printf("\n");
        printf("|%3d",reparacion.id);
        printf("| %-8s%2s", DispositivoReparado(dispositivoReparado, &reparacion),"");
        printf("|%10s", reparacion.fecha);
        printf("|$%12.2f%1s", reparacion.precioFinal,"");
        printf("| %2d%s%2d |", reparacion.empleado.codigo," | ", reparacion.empresa.codigo);
      }
    }
    printf("\n");
    printf("|---|-----------|----------|--------------|---------|");
    printf("\n");
  } else {
    printf("\n No existen reparaciones almacenadas realizadas en esa fecha.");
  }
  fclose(reparaciones);
}
//ID-CODIGOS
int obtenerMaximoEmpleado() {
  //  abrir archivo para leer
  FILE *empleados = fopen("empleados.dat", "rb");
  verificarAbrirArchivo(empleados);
  //  posicionamos el cursor al inicio del último registro
  fseek(empleados, -sizeof(Empleado), SEEK_END);
  //  leer el codigo-id del registro
  Empleado empleado;
  if (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
    //  devolver el valor
    return empleado.codigo;
  } else {
    return 0;
  }
}
int obtenerMaximoEmpresa() {
  //  abrir archivo para leer
  FILE *empresas = fopen("empresas.dat", "rb");
  verificarAbrirArchivo(empresas);
  //  posicionamos el cursor al inicio del último registro
  fseek(empresas, -sizeof(Empresa), SEEK_END);
  //  leer el codigo-id del registro
  Empresa empresa;
  if (fread(&empresa, sizeof(Empresa), 1, empresas) == 1) {
    //  devolver el valor
    return empresa.codigo;
  } else {
    return 0;
  }
}
int obtenerMaximoReparacion() {
  //  abrir archivo para leer
  FILE *reparaciones = fopen("reparaciones.dat", "rb");
  verificarAbrirArchivo(reparaciones);
  //  posicionamos el cursor al inicio del último registro
  fseek(reparaciones, -sizeof(Reparacion), SEEK_END);
  //  leer el codigo-id del registro
  Reparacion reparacion;
  if (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
    //  devolver el valor
    return reparacion.id;
  } else {
    return 0;
  }
}