#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "menu.h"
#include "reparaciones.h"
#include "company.h"
#include "busqueda.h"

// procedimientos de menu y titulo de proyecto

void menu() {
  titulo();
  printf("\n [1] Ingresar reparaciones.");
  printf("\n [2] Buscar una reparación según tipo de dispositivo.");
  printf("\n [3] Buscar la reparación con el mayor precio final.");
  printf("\n [4] Mostrar las reparaciones realizadas por un empleado específico.");
  printf("\n [5] Mostrar las reparaciones correspondientes a una sola empresa.");
  printf("\n [6] Mostrar las reparaciones realizadas en una fecha.");
  printf("\n [7] Mostrar Datos de Empleados y Empresas.");
  printf("\n [8] Mostrar todas las reparaciones.");
  printf("\n [9] Almacenar todas las reparaciones.");
  printf("\n [10] Modificar archivos de empleados, empresas y reparaciones.");
  printf("\n [0] Salir del programa.");
}

void menuSecundario(int opcionSeleccionada) {
  switch (opcionSeleccionada) {
    case 0:{
      printf("\n Saliendo del programa...\n\n");
      break;
    }
    case 1:{
      menuTerciario(1);
      continuar();
      break;
    }
    case 2:{
      menuTerciario(2);
      continuar();
      break;
    }
    case 3:{
      menuTerciario(3);
      continuar();
      break;
    }
    case 4:{
      menuTerciario(4);
      continuar();
      break;
    }
    case 5:{
      menuTerciario(5);
      continuar();
      break;
    }
    case 6:{
      menuTerciario(6);
      continuar();
      break;
    }
    case 7:{
      menuTerciario(7);
      continuar();
      break;
    }
    case 8:{
      menuTerciario(8);
      continuar();
      break;
    }
    case 9:{
      menuTerciario(9);
      continuar();
      break;
    }
    case 10:{
      menuTerciario(10);
      continuar();
      break;
    }
    default:{
      printf(" Opción incorrecta. \n Por favor, elija una de las opciones indicadas en el menú.\n");
      continuar();
      break;
    }
  }
}

void menuTerciario(int opcionSeleccionada) {
  int subOpcion;// bandera para saber si es valida la opcion seleccionada (menu 4 y 5)
  int ok;//  bandera de confirmación (menu 1 y menu 7)
  int dato;// almacena la opcion seleccionada (menu 1)
  int codigoEmpleado;// almacena el codigo del empleado a validar (menu 1)
  
  switch (opcionSeleccionada) {
    case 1:{
      do {
        limpiarConsola();
        titulo();
        printf("\tIngresar reparaciones\n");
        printf("\n Seleccione una opción:\n");
        printf("[1] Ingresar reparación.\n");
        printf("[0] Volver al menú anterior.\n");
        printf("\n\n");
        dato = leerEntero();
      } while (dato < 0 || dato > 1);
      if (dato == 1) {
        codigoEmpleado = ValidarEmpleado();
        if (codigoEmpleado == 0) {
          return;
        } else {
          crearReparacion(&codigoEmpleado);
        }
      }
      break;
    }
    case 2:{
      limpiarConsola();
      titulo();
      printf("\tBuscar reparación por tipo de dispositivo\n");
      buscarDispositivo();
      break;
    }
    case 3:{
      limpiarConsola();
      titulo();
      printf("\tReparación con el mayor precio final:\n");
      buscarPresupuestoMaximo();
      break;
    }
    case 4:{
      do {
        limpiarConsola();
        titulo();
        printf("\tReparaciones realizadas por un empleado específico\n");
        menuElegirEmpleado();
        int maximoEmpleado = obtenerMaximoEmpleado();
        do {
          subOpcion = leerEntero();
        } while (subOpcion < 0 || subOpcion > maximoEmpleado);
        if (subOpcion != 0) {
          mostrarReparacionesDeEmpleado(subOpcion);
        }
      } while (subOpcion != 0);
      break;}
    case 5:{
      do {
        limpiarConsola();
        titulo();
        printf("\tReparaciones realizadas a una empresa\n");
        menuElegirEmpresa();
        int maximoEmpresa = obtenerMaximoEmpresa();
        do {
          subOpcion = leerEntero();
        } while (subOpcion < 0 || subOpcion > maximoEmpresa);
        if (subOpcion != 0) {
          mostrarReparacionesAEmpresa(subOpcion);
        }
      } while (subOpcion != 0);
      break;}
    case 6:{
      limpiarConsola();
      titulo();
      printf("\tReparaciones realizadas en una fecha\n");
      buscarReparacionesFecha();
      break;
    }
    case 7:{
      limpiarConsola();
      titulo();
      printf("\tDatos de Empleados y Empresas:\n");
      mostrarEmpleados();
      mostrarEmpresas();
      break;
    }
    case 8:{
      limpiarConsola();
      titulo();
      mostrarReparaciones();
      break;
    }
    case 9:{
      limpiarConsola();
      titulo();
      do{
        printf("\tAlmacenar todas las reparaciones:\n");
        printf("[1] Guardar en 'reparaciones.dat'.\n");
        printf("[0] Volver al menú anterior.\n");
        printf("\n\n");
        dato = leerEntero();
      } while (dato < 0 || dato > 1);
      if (dato == 1) {
        almacenarReparaciones();
      }
      break;
    }
    case 10:{
      int archivoElegido;
      do {
        limpiarConsola();
        titulo();
        printf("\tModificar archivos:\n");
        menuModificarArchivos();
        printf("\n Opción = ");
        archivoElegido = leerEntero();
      } while (archivoElegido < 0 || archivoElegido > 3);
      if (archivoElegido != 0) {
        limpiarConsola();
        titulo();
        submenuModificar(archivoElegido);
      }
      break;
    }
    case 0:
    default:
      break;
  }
}

void submenuModificar(int seleccion) {
  int reparacionElegida;//  control para elegir reparación a modificar/eliminar
  int empleadoElegido;//  control para elegir empleado a modificar/eliminar
  int empresaElegida;//  control para elegir empresa a modificar/eliminar
  int opcion;//  control para elegir entre modificar y eliminar
  
  switch (seleccion) {
    case 1:{
      do {
        limpiarConsola();
        titulo();
        printf("\nModificar/Eliminar reparaciones:\n\n");
        menuElegirReparacion();
        printf("\n\n Opción: ");
        int maximoReparacion = obtenerMaximoReparacion();
        do {
          reparacionElegida = leerEntero();
        } while (reparacionElegida < 0 || reparacionElegida > maximoReparacion);
        if (reparacionElegida != 0) {
          do {
            limpiarConsola();
            printf("\n[1] Modificar\t [0] Eliminar\t [2] Volver\n\n");
            opcion = leerEntero();
          } while (opcion < 0 || opcion > 2);
          if (opcion == 1) {
            modificarReparacion(reparacionElegida);
          } else if (opcion == 0) {
            eliminarReparacion(reparacionElegida);
          }
        }
      } while (reparacionElegida != 0); 
      break;
    }
    case 2:{
      do {
        limpiarConsola();
        titulo();
        printf("\nModificar/Eliminar empleados:\n\n");
        menuElegirEmpleado();
        printf("\n\n Opción: ");
        int maximoEmpleado = obtenerMaximoEmpleado();
        do {
          empleadoElegido = leerEntero();
        } while (empleadoElegido < 0 || empleadoElegido > maximoEmpleado);
        if (empleadoElegido != 0) {
          do {
            limpiarConsola();
            printf("\n[1] Modificar\t [0] Eliminar\t [2] Volver\n\n");
            opcion = leerEntero();
          } while (opcion < 0 || opcion > 2);
          if (opcion == 1) {
            modificarEmpleado(empleadoElegido);
          } else if (opcion == 0) {
            eliminarEmpleado(empleadoElegido);
          }
        }
      } while (empleadoElegido != 0);
      break;
    }
    case 3:{
      do {
        limpiarConsola();
        titulo();
        printf("\nModificar/Eliminar empresas:\n\n");
        menuElegirEmpresa();
        printf("\n\n Opción: ");
        int maximoEmpresa = obtenerMaximoEmpresa();
        do {
          empresaElegida = leerEntero();
        } while (empresaElegida < 0 || empresaElegida > maximoEmpresa);
        if (empresaElegida != 0) {
          do {
            limpiarConsola();
            printf("\n[1] Modificar\t [0] Eliminar\t [2] Volver\n\n");
            opcion = leerEntero();
          } while (opcion < 0 || opcion > 2);
          if (opcion == 1) {
            modificarEmpresa(empresaElegida);
          } else if (opcion == 0) {
            eliminarEmpresa(empresaElegida);
          }
        }
      } while (empleadoElegido != 0);
      break;
    }
    default:
      break;
  }
}

void menuModificarArchivos() {
  printf("\n Seleccione un archivo a modificar:\n");
  printf("\t\t [1] 'reparaciones.dat'\n");
  printf("\t\t [2] 'empleados.dat'\n");
  printf("\t\t [3] 'empresas.dat'\n");
  printf("\t\t [0] Volver al menú anterior.\n");
  printf("\n");
}

void menuElegirEmpleado() {
  Empleado empleado;
  FILE *empleados = fopen("empleados.dat", "rb");
  verificarAbrirArchivo(empleados);
  while (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
    printf("\n [%2d] %s %s", empleado.codigo, empleado.nombres, empleado.apellidos);
  }
  fclose(empleados);
  printf("\n [0] Volver");
  printf("\n\n\tEmpleado: ");
}

void menuElegirEmpresa() {
  Empresa empresa;
  FILE *empresas = fopen("empresas.dat", "rb");
  verificarAbrirArchivo(empresas);
  while (fread(&empresa, sizeof(Empresa), 1, empresas) == 1) {
    printf("\n [%d] %s", empresa.codigo, empresa.nombre);
  }
  fclose(empresas);
  printf("\n [0] Volver");
  printf("\n\n\tEmpresa: ");
}

void menuElegirReparacion() {
  Reparacion reparacion;
  char dispositivoReparado[20];
  FILE *reparaciones = fopen("reparaciones.dat", "rb");
  verificarAbrirArchivo(reparaciones);
  verificarArchivoVacio(reparaciones);
  printf("\n");
  printf("|%3s","ID");
  printf("|%-11s","Dispositivo");
  printf("|%2s%-6s%2s","","Fecha","");
  printf("|%4s%-6s%4s","","Precio","");
  printf("|%1s%-7s |","","Codigos");
  printf("\n");
  printf("|---|-----------|----------|--------------|---------|");
  while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
    printf("\n");
    printf("|%3d",reparacion.id);
    printf("| %-8s%2s", DispositivoReparado(dispositivoReparado, &reparacion),"");
    printf("|%10s", reparacion.fecha);
    printf("|$%12.2f%1s", reparacion.precioFinal,"");
    printf("| %2d%s%2d |", reparacion.empleado.codigo," | ", reparacion.empresa.codigo);
  }
  printf("\n");
  printf("|---|-----------|----------|--------------|---------|");
  printf("\n");
  fclose(reparaciones);
  printf("\n\t[ID] Ingrese el ID de la reparación que desea modificar o borrar");
  printf("\n\t[0] Ingrese cero para volver");
}

void titulo() {
  imprimirCadenaCentrada("< - - - - - - - - - - - - - >", 68);
  printf("\n");
  imprimirCadenaCentrada("< - - - - | 'El Cuyanito' | - - - - >", 68);
  printf("\n");
  imprimirCadenaCentrada("< - - - - - - |    v2 - by    | - - - - - - >", 68);
  //imprimirCadenaCentrada("< - - - - - - |               | - - - - - - >", 68);
  printf("\n");
  imprimirCadenaCentrada("< - - - - |NiBits Software| - - - - >", 68);
  printf("\n");
  imprimirCadenaCentrada("< - - - - - - - - - - - - - >", 68);
  printf("\n\n");
}
