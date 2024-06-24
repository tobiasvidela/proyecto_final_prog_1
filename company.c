#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"
#include "funciones.h"
#include "busqueda.h"
#include "company.h"

int ValidarEmpleado() {
  int code, repeat;
  int maximoEmpleado = obtenerMaximoEmpleado();
  Empleado empleado;
  FILE *empleados = fopen("empleados.dat", "rb");
  verificarAbrirArchivo(empleados);

  limpiarConsola();
  do{
    printf("Ingrese su código de empleado: ");
    do {
      code = leerEntero();
    } while (code < 1 || code > maximoEmpleado);
    fseek(empleados, 0, SEEK_SET);
    while (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
      if (code == empleado.codigo) {
        printf("\n Código %d;", code);
        printf(" Empleado/a %s;\n", empleado.apellidos);
      }
    }
    printf("\n [1] No soy yo\t\t[0] Soy yo\t\t[2] Volver atrás\n");
    repeat = leerEntero();
    if (repeat == 2) {
      return 0;
    }
  } while (repeat == 1 || repeat == 2);
  fclose(empleados);
  return code;
}

void mostrarEmpleados() {
  Empleado empleado;
  FILE *empleadosDAT = fopen("empleados.dat", "rb");
  verificarAbrirArchivo(empleadosDAT);

  printf("\n\n");
  printf("|%-3s|","");
  imprimirCadenaCentrada("CUIL",15);
  printf("|");
  imprimirCadenaCentrada("NOMBRES Y APELLIDOS",32);
  printf("|");
  printf("\n");
  printf("|---|---------------|--------------------------------|");
  printf("\n");

  while (fread(&empleado, sizeof(Empleado), 1, empleadosDAT) == 1) {
    printf("%s%-3d", "|", empleado.codigo);
    printf("|");
    imprimirCadenaCentrada(empleado.cuil,15);
    printf("|%15s, ", empleado.nombres);
    printf("%-15s%s", empleado.apellidos,"|");
    printf("\n");
  }
  printf("|---|---------------|--------------------------------|");
  printf("\n");

  fclose(empleadosDAT);
}

void mostrarEmpresas() {
  Empresa empresa;
  FILE *empresasDAT = fopen("empresas.dat", "rb");
  verificarAbrirArchivo(empresasDAT);

  printf("\n\n");
  printf("|%-3s|","");
  imprimirCadenaCentrada("CUIT",15);
  printf("|");
  imprimirCadenaCentrada("NOMBRES",20);
  printf("|");
  printf("\n");
  printf("|---|---------------|--------------------|");
  printf("\n");

  while (fread(&empresa, sizeof(Empresa), 1, empresasDAT) == 1){
    printf("|%-3d", empresa.codigo);
    printf("|");
    imprimirCadenaCentrada(empresa.cuit,15);
    printf("|");
    imprimirCadenaCentrada(empresa.nombre,20);
    printf("|");
    printf("\n");
  }
  printf("|---|---------------|--------------------|");
  printf("\n");

  fclose(empresasDAT);
}

void modificarEmpleado(int codigo) {
  //Imprimir empleado elegido
  Empleado empleado;
  FILE *empleados = fopen("empleados.dat", "rb");
  printf("\n\n");
  printf("|%-3s|","");
  imprimirCadenaCentrada("CUIL",15);
  printf("|");
  imprimirCadenaCentrada("NOMBRES Y APELLIDOS",32);
  printf("|");
  printf("\n");
  printf("|---|---------------|--------------------------------|");
  printf("\n");
  //encontrar el empleado elegido e imprimir sus datos y luego las opciones a modificar
  while (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
    if (empleado.codigo == codigo) {
      printf("%s%-3d", "|", empleado.codigo);
      printf("|");
      imprimirCadenaCentrada(empleado.cuil,15);
      printf("|%15s, ", empleado.nombres);
      printf("%-15s%s", empleado.apellidos,"|");
      printf("\n");
    }
  }
  printf("|---|---------------|--------------------------------|");
  printf("\n");
  fclose(empleados);
  //datos para editar
  printf("\n\n MODIFICAR EMPLEADO:");
  printf("\n\t [1] DNI");
  printf("\n\t [2] CUIL");
  printf("\n\t [3] Nombres");
  printf("\n\t [4] Apellidos");
  //instrucciones para editar datos
  printf("\n\n Elija una opción para editar: ");
  int opcion;
  do {
    opcion = leerEntero();
  } while (opcion < 1 || opcion > 4);
  limpiarConsola();
  switch (opcion) {
    case 1:{
      FILE *empleados = fopen("empleados.dat","rb+");
      Empleado empleado;
      while (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
        if (empleado.codigo == codigo) {
          printf("\n Modificar DNI (%s):\n",empleado.dni);
          limpiarBuffers();
          fgets(empleado.dni, sizeof(empleado.dni), stdin);
          fseek(empleados,-sizeof(Empleado),SEEK_CUR);
          fwrite(&empleado, sizeof(Empleado), 1, empleados);
        }
      }
      fclose(empleados);
      break;
    }
    case 2:{
      FILE *empleados = fopen("empleados.dat","rb+");
      Empleado empleado;
      while (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
        if (empleado.codigo == codigo) {
          printf("\n Modificar CUIL (%s):\n",empleado.cuil);
          limpiarBuffers();
          fgets(empleado.cuil, sizeof(empleado.cuil), stdin);
          fseek(empleados,-sizeof(Empleado),SEEK_CUR);
          fwrite(&empleado, sizeof(Empleado), 1, empleados);
        }
      }
      fclose(empleados);
      break;
    }
    case 3:{
      FILE *empleados = fopen("empleados.dat","rb+");
      Empleado empleado;
      while (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
        if (empleado.codigo == codigo) {
          printf("\n Modificar nombres (%s):\n",empleado.nombres);
          limpiarBuffers();
          fgets(empleado.nombres, sizeof(empleado.nombres), stdin);
          fseek(empleados,-sizeof(Empleado),SEEK_CUR);
          fwrite(&empleado, sizeof(Empleado), 1, empleados);
        }
      }
      fclose(empleados);
      break;
    }
    case 4:{
      FILE *empleados = fopen("empleados.dat","rb+");
      Empleado empleado;
      while (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
        if (empleado.codigo == codigo) {
          printf("\n Modificar apellidos (%s):\n",empleado.apellidos);
          limpiarBuffers();
          fgets(empleado.apellidos, sizeof(empleado.apellidos), stdin);
          fseek(empleados,-sizeof(Empleado),SEEK_CUR);
          fwrite(&empleado, sizeof(Empleado), 1, empleados);
        }
      }
      fclose(empleados);
      break;
    }
  }
  //mostrar todos los empleados
  mostrarEmpleados();
  //volver al menu principal
  return;
}

void eliminarEmpleado(int codigo) {
  //imprimir empleado elegido
  int confirmar = 0;
  Empleado empleado;
  FILE *empleados = fopen("empleados.dat", "rb");
  printf("\n\n");
  printf("|%-3s|","");
  imprimirCadenaCentrada("CUIL",15);
  printf("|");
  imprimirCadenaCentrada("NOMBRES Y APELLIDOS",32);
  printf("|");
  printf("\n");
  printf("|---|---------------|--------------------------------|");
  printf("\n");
  while (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
    if (empleado.codigo == codigo) {
      printf("%s%-3d", "|", empleado.codigo);
      printf("|");
      imprimirCadenaCentrada(empleado.cuil,15);
      printf("|%15s, ", empleado.nombres);
      printf("%-15s%s", empleado.apellidos,"|");
      printf("\n");
    }
  }
  printf("|---|---------------|--------------------------------|");
  printf("\n");
  fclose(empleados);
  printf("\n ¿Desea eliminar este empleado?\n");
  printf("\t[1] Sí\t[0] No");
  printf("\nOpción: ");
  do{
    confirmar = leerEntero();
  } while (confirmar < 0 || confirmar > 1);
  if (confirmar != 0) {    
    //ELIMINAR REGISTRO
    //abrimos el archivo
    FILE *empleados = fopen("empleados.dat", "rb+");
    verificarAbrirArchivo(empleados);
    //sobreescribimos los registros
    //nos posicionamos al final del registro a eliminar
    fseek(empleados,sizeof(Empleado)*(codigo),SEEK_SET);
    //avanzamos al siguiente registro y lo guardamos en una variable
    
    Empleado siguiente;
    while (fread(&siguiente, sizeof(Empleado), 1, empleados) == 1) {
      //nos posicionamos al inicio del anterior
      fseek(empleados,sizeof(Empleado)*(-2),SEEK_CUR);
      //actualizamos su codigo
      siguiente.codigo--;
      //escribimos el registro guardado en "siguiente" en el registro a eliminar
      fwrite(&siguiente, sizeof(Empleado), 1, empleados);
      //avanzamos un registro
      fseek(empleados,sizeof(Empleado),SEEK_CUR);
    }
    //eliminar el último registro
    int maximoEmpleados = obtenerMaximoEmpleado();
    if (ftruncate(fileno(empleados), sizeof(Empleado) * (maximoEmpleados-1)) != 0) {
      printf("\n Error al acortar el archivo.\n");
      return;
    }
    fclose(empleados);
  } else {
    //volver
    return;
  }
  mostrarEmpleados();
}

void modificarEmpresa(int codigo) {
  //imprimir empresa elegida
  Empresa empresa;
  FILE *empresas = fopen("empresas.dat", "rb");
  printf("\n\n");
  printf("|%-3s|","");
  imprimirCadenaCentrada("CUIT",15);
  printf("|");
  imprimirCadenaCentrada("NOMBRES",20);
  printf("|");
  printf("\n");
  printf("|---|---------------|--------------------|");
  printf("\n");
  while (fread(&empresa, sizeof(Empresa), 1, empresas) == 1) {
    if (empresa.codigo == codigo) {
      printf("|%-3d", empresa.codigo);
      printf("|");
      imprimirCadenaCentrada(empresa.cuit,15);
      printf("|");
      imprimirCadenaCentrada(empresa.nombre,20);
      printf("|");
      printf("\n");
    }
  }
  printf("|---|---------------|--------------------|");
  printf("\n");
  fclose(empresas);
  //datos para editar
  printf("\n\n MODIFICAR EMPRESA:");
  printf("\n\t [1] CUIT");
  printf("\n\t [2] Nombre");
  //instrucciones para editar datos
  printf("\n\n Elija una opción para editar: ");
  int opcion;
  do {
    opcion = leerEntero();
  } while (opcion < 1 || opcion > 2);
  limpiarConsola();
  switch (opcion) {
    case 1:{
      FILE *empresas = fopen("empresas.dat","rb+");
      Empresa empresa;
      while (fread(&empresa, sizeof(Empresa), 1, empresas) == 1) {
        if (empresa.codigo == codigo) {
          printf("\n Modificar CUIT (%s):\n",empresa.cuit);
          limpiarBuffers();
          fgets(empresa.cuit, sizeof(empresa.cuit), stdin);
          fseek(empresas,-sizeof(Empresa),SEEK_CUR);
          fwrite(&empresa, sizeof(Empresa), 1, empresas);
        }
      }
      fclose(empresas);
      break;
    }
    case 2:{
      FILE *empresas = fopen("empresas.dat","rb+");
      Empresa empresa;
      while (fread(&empresa, sizeof(Empresa), 1, empresas) == 1) {
        if (empresa.codigo == codigo) {
          printf("\n Modificar nombre (%s):\n",empresa.nombre);
          limpiarBuffers();
          fgets(empresa.nombre, sizeof(empresa.nombre), stdin);
          fseek(empresas,-sizeof(Empresa),SEEK_CUR);
          fwrite(&empresa, sizeof(Empresa), 1, empresas);
        }
      }
      fclose(empresas);
      break;
    }
  }
  //mostrar todas las empresas
  mostrarEmpresas();
  //volver al menu principal
  return;
}

void eliminarEmpresa(int codigo) {
  //imprimir empresa elegida
  int confirmar = 0;
  Empresa empresa;
  FILE *empresas = fopen("empresas.dat", "rb");
  printf("\n\n");
  printf("|%-3s|","");
  imprimirCadenaCentrada("CUIT",15);
  printf("|");
  imprimirCadenaCentrada("NOMBRES",20);
  printf("|");
  printf("\n");
  printf("|---|---------------|--------------------|");
  printf("\n");
  while (fread(&empresa, sizeof(Empresa), 1, empresas) == 1) {
    if (empresa.codigo == codigo) {
      printf("|%-3d", empresa.codigo);
      printf("|");
      imprimirCadenaCentrada(empresa.cuit,15);
      printf("|");
      imprimirCadenaCentrada(empresa.nombre,20);
      printf("|");
      printf("\n");
    }
  }
  printf("|---|---------------|--------------------|");
  printf("\n");
  fclose(empresas);
  printf("\n ¿Desea eliminar esta empresa?\n");
  printf("\t[1] Sí\t[0] No");
  printf("\nOpción: ");
  do{
    confirmar = leerEntero();
  } while (confirmar < 0 || confirmar > 1);
  if (confirmar != 0) {    
    //ELIMINAR REGISTRO
    //abrimos el archivo
    FILE *empresas = fopen("empresas.dat", "rb+");
    verificarAbrirArchivo(empresas);
    //sobreescribimos los registros
    //nos posicionamos al final del registro a eliminar
    fseek(empresas,sizeof(Empresa)*(codigo),SEEK_SET);
    //avanzamos al siguiente registro y lo guardamos en una variable
    Empresa siguiente;
    while (fread(&siguiente, sizeof(Empresa), 1, empresas) == 1) {
      //nos posicionamos al inicio del anterior
      fseek(empresas,sizeof(Empresa)*(-2),SEEK_CUR);
      //actualizamos su codigo
      siguiente.codigo--;
      //escribimos el registro guardado en "siguiente" en el registro a eliminar
      fwrite(&siguiente, sizeof(Empresa), 1, empresas);
      //avanzamos un registro
      fseek(empresas,sizeof(Empresa),SEEK_CUR);
    }
    //eliminar el último registro
    int maximoEmpresas = obtenerMaximoEmpresa();
    if (ftruncate(fileno(empresas), sizeof(Empresa) * (maximoEmpresas-1)) != 0) {
      printf("\n Error al acortar el archivo.\n");
      return;
    }
    fclose(empresas);
  } else {
    //volver
    return;
  }
  mostrarEmpresas();
}
