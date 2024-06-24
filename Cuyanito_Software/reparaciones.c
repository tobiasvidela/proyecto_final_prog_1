#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"
#include "funciones.h"
#include "company.h"
#include "busqueda.h"
#include "reparaciones.h"

// Variables Globales

Reparacion* Primero = NULL;
Reparacion* Ultimo = NULL;

//  Funciones y Procedimientos

void cargarID(Reparacion *reparacion) {
  //  abrir el archivo
  FILE *reparaciones = fopen("reparaciones.dat","rb");
  //  si el archivo no existe
  if (reparaciones == NULL) {
    reparacion->id = 1;
    //  si existen cargadas en memoria
    if (Ultimo != NULL && reparacion->id <= Ultimo->id) {
      //actualizar el id correctamente
      reparacion->id = Ultimo->id + 1;
    }
    return;
  }
  //  si el archivo ya existe
  //  posicionar el puntero de lectura al inicio de la última reparación cargada
  fseek(reparaciones, -sizeof(Reparacion), SEEK_END);
  //  leer la última reparacion cargada
  Reparacion ultima;
  fread(&ultima, sizeof(Reparacion), 1, reparaciones);
  fclose(reparaciones);
  reparacion->id = ultima.id + 1;
  if (Ultimo != NULL && reparacion->id == Ultimo->id) {
    reparacion->id = Ultimo->id + 1;
  }
  return;
}

char *DispositivoReparado(char dispositivoReparado[20], Reparacion *reparacion) {
  switch(reparacion->dispositivo){
    case 1:
      strcpy(dispositivoReparado,"PC");
      break;
    case 2:
      strcpy(dispositivoReparado,"Netbook");
      break;
    case 3:
      strcpy(dispositivoReparado,"Celular");
      break;
    default:
      strcpy(dispositivoReparado,"dispositivo");
      break;
  }
  return dispositivoReparado;
}

float CalcularPrecioFinal(Reparacion *reparacion) {
  //  dependiendo del tipo de dispositivo, sumamos una base al precio:
  float precioFinal = 0;
  switch(reparacion->dispositivo) {
    case 1:
      precioFinal += 500;
      break;
    case 2:
      precioFinal += 400;
      break;
    case 3:
      precioFinal += 300;
      break;
    default:
      break;
  }
  return precioFinal + reparacion->costoHardware + reparacion->costoSoftware;
}

void cargarFechaReparacion(Reparacion *reparacion) {
  char fecha[11];
  strcpy(reparacion->fecha,leerFecha(fecha));
}

void cargarEmpleadoAReparacion(Reparacion *reparacion, int *codigoEmpleado) {
  printf("\nCargando información del empleado...\n");

  //  cargar codigo del empleado ya validado
  reparacion->empleado.codigo = *codigoEmpleado;

  // buscar los datos del empleado y cargarlos en la reparación
  FILE *empleados = fopen("empleados.dat", "rb");
  verificarAbrirArchivo(empleados);
  Empleado empleado;

  while (fread(&empleado, sizeof(Empleado), 1, empleados) == 1) {
    if (reparacion->empleado.codigo == empleado.codigo) {
      strcpy(reparacion->empleado.dni, empleado.dni);
      strcpy(reparacion->empleado.cuil, empleado.cuil);
      strcpy(reparacion->empleado.nombres, empleado.nombres);
      strcpy(reparacion->empleado.apellidos, empleado.apellidos);
    }
  }

  fclose(empleados);
  printf("Finalizado.\n");
}

void cargarEmpresaAReparacion(Reparacion *reparacion) {
  printf("\nCargando información de la empresa...\n");

  int code, repeat, maximoEmpresa = obtenerMaximoEmpresa();
  Empresa empresa;
  FILE *empresas = fopen("empresas.dat", "rb");
  verificarAbrirArchivo(empresas);

  do{
    printf("Ingrese el código de la empresa: ");
    do {
      code = leerEntero();
    } while (code < 1 || code > maximoEmpresa);
    fseek(empresas, 0, SEEK_SET);
    while (fread(&empresa, sizeof(Empresa), 1, empresas) == 1) {
      if (code == empresa.codigo) {
        printf("\n Código %d;", code);
        printf(" Empresa %s;\n", empresa.nombre);
      }
    }
    printf("\n [1] Cambiar código\t\t[0] Es la correcta\n");
    repeat = leerEntero();
  } while (repeat);

  reparacion->empresa.codigo = code;

  fseek(empresas, 0, SEEK_SET);
  while (fread(&empresa, sizeof(Empresa), 1, empresas) == 1) {
    if (reparacion->empresa.codigo == empresa.codigo) {
      strcpy(reparacion->empresa.cuit, empresa.cuit);
      strcpy(reparacion->empresa.nombre, empresa.nombre);
    }
  }

  fclose(empresas);
  printf("Finalizado.\n");
}

void cargarReparacion(Reparacion *reparacion, int *codigoEmpleado) {

  limpiarConsola();
  printf("Nueva Reparación:\n");

  //cargar reparación
  cargarID(reparacion);
  
  printf("Declare dispositivo [1] PC - [2] Netbook - [3] Celular: \n");
  do {
    reparacion->dispositivo = leerEntero();
  } while (reparacion->dispositivo < 1 || reparacion->dispositivo > 3);

  cargarFechaReparacion(reparacion);

  printf("Ingrese costo del hardware de la reparación: \n");
  reparacion->costoHardware = leerFloat();

  printf("Ingrese costo del software de la reparación: \n");
  reparacion->costoSoftware = leerFloat();

  reparacion->precioFinal = CalcularPrecioFinal(reparacion);  

  cargarEmpleadoAReparacion(reparacion,codigoEmpleado);

  cargarEmpresaAReparacion(reparacion);

  reparacion->siguiente = NULL;
}

void crearReparacion(int *codigoEmpleado) {
  Reparacion *reparacionNueva = malloc(sizeof(Reparacion));

  if(reparacionNueva == NULL){
    printf("Error al asignar memoria para la reparación.\n");
    exit(1);
  }

  cargarReparacion(reparacionNueva, codigoEmpleado);

  // actualizar la lista
  if (Primero == NULL) { //  si no existe un primer nodo
    Primero = reparacionNueva;
    Ultimo = reparacionNueva;
    Ultimo->siguiente = NULL;
  } else {
    Ultimo->siguiente = reparacionNueva; //  que el actual último nodo apunte al nuevo agregado
    Ultimo = reparacionNueva; //  ahora el último nodo es el agregado
    Ultimo->siguiente = NULL; //  el nuevo nodo agregado apunta a nulo
  }

  printf("\n Reparación ingresada existosamente.\n\n");
}

void almacenarReparaciones() {
  Reparacion reparacion;

  if (Primero == NULL){
    printf("\n No se ingresaron nuevas reparaciones.\n");
    return;
  }
  printf("\n Actualizando el archivo \"reparaciones.dat\"...\n\n");

  //abrir archivo
  FILE *reparacionesDat = fopen("reparaciones.dat", "ab");
  verificarAbrirArchivo(reparacionesDat);

  //agregar datos
  Reparacion *reparacionActual = Primero;
  while (reparacionActual){
    fwrite(reparacionActual, sizeof(Reparacion), 1, reparacionesDat);
    reparacionActual = reparacionActual->siguiente;
  }
  
  liberarMemoria();
  fclose(reparacionesDat);

  //  muestra los datos reabriendo el archivo
  printf("\n Datos almacenados exitosamente.\n");
  mostrarReparaciones();
}

void mostrarReparaciones() {
  Reparacion reparacion;
  Reparacion *reparacionActual = Primero;
  char dispositivoReparado[20];
  FILE *reparacionesDAT = fopen("reparaciones.dat", "rb");
  verificarAbrirArchivo(reparacionesDAT);

  printf("\nReparaciones Almacenadas y Cargadas*: \n");

  printf("\n");
  printf("|%3s","ID");
  printf("|%-11s","Dispositivo");
  printf("|%2s%-6s%2s","","Fecha","");
  printf("|%4s%-6s%4s","","Precio","");
  printf("|%1s%-7s |","","Codigos");
  printf("\n");
  printf("|---|-----------|----------|--------------|---------|");
  while (reparacionActual) {
    printf("\n");
    printf("|%3s","");
    printf("|*%-8s%2s", DispositivoReparado(dispositivoReparado, reparacionActual),"");
    printf("|%10s", reparacionActual->fecha);
    printf("|$%12.2f%1s", reparacionActual->precioFinal,"");
    printf("| %2d%s%2d |", reparacionActual->empleado.codigo," | ", reparacionActual->empresa.codigo);
    reparacionActual = reparacionActual->siguiente;
  }
  reparacionActual = NULL;

  while (fread(&reparacion, sizeof(Reparacion), 1, reparacionesDAT) == 1) {
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

  fclose(reparacionesDAT);
}

void liberarMemoria() {
  Reparacion *reparacionActual = Primero;

  while (reparacionActual) {
    Reparacion *reparacionAEliminar = reparacionActual;//  vamos a borrar la reparacion actual
    reparacionActual = reparacionActual->siguiente;//  guardamos la dirección de la reparacion anterior a la actual
    free(reparacionAEliminar);//  borramos la reparacion actual
  }
  //  reseteamos los punteros referencia
  Primero = NULL;
  Ultimo = NULL;
}

void modificarReparacion(int id) {
  //Imprimir reparacion elegida
  Reparacion reparacion;
  char dispositivoReparado[20];
  FILE *reparacionesDAT = fopen("reparaciones.dat", "rb");
  printf("\n");
  printf("|%3s","ID");
  printf("|%-11s","Dispositivo");
  printf("|%2s%-6s%2s","","Fecha","");
  printf("|%4s%-6s%4s","","Precio","");
  printf("|%1s%-7s |","","Codigos");
  printf("\n");
  printf("|---|-----------|----------|--------------|---------|");
  //encontrar la reparacion elegida e imprimir sus datos y luego las opciones a modificar
  while (fread(&reparacion, sizeof(Reparacion), 1, reparacionesDAT) == 1) {
    if (reparacion.id == id) {
      printf("\n");
      printf("|%3d",reparacion.id);
      printf("| %-8s%2s", DispositivoReparado(dispositivoReparado, &reparacion),"");
      printf("|%10s", reparacion.fecha);
      printf("|$%12.2f%1s", reparacion.precioFinal,"");
      printf("| %2d%s%2d |", reparacion.empleado.codigo," | ", reparacion.empresa.codigo);
      printf("\n");
      printf("|---|-----------|----------|--------------|---------|");
      printf("\n");
      //Imprimir opciones para modificar de la reparación elegida
      printf("\n Modificar Reparación: \n");
      //tipo de dispositivo
      printf("\n\t [1] Dispositivo");
      //fecha
      printf("\n\t [2] Fecha");
      //costoSoftware
      printf("\n\t [3] Costo del Software (%.2f)",reparacion.costoSoftware);
      //costoHardware
      printf("\n\t [4] Costo del Hardware (%.2f)",reparacion.costoHardware);
      //empleado
      printf("\n\t [5] Empleado que la realizó (%s,%s)",reparacion.empleado.nombres,reparacion.empleado.apellidos);
      //empresa
      printf("\n\t [6] Empresa a la que se realizó (%s)",reparacion.empresa.nombre);
    }
  }
  fclose(reparacionesDAT);
  //instrucciones para editar datos
  printf("\n\n Elija una opción para editar: ");
  int opcion;
  do {
    opcion = leerEntero();
  } while (opcion < 1 || opcion > 6);
  limpiarConsola();
  switch (opcion) {
    case 1:{
      printf("\n Modificar Dispositivo:\n");
      printf(" [1] PC\t[2] Netbook\t[3] Celular");
      printf("\n Elija una opción: ");
      int dispositivoNuevo;
      do {
        dispositivoNuevo = leerEntero();
      } while (dispositivoNuevo < 1 || dispositivoNuevo > 3);
      //  actualizar reparacion
      FILE *reparaciones = fopen("reparaciones.dat","rb+");
      Reparacion reparacion;
      while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
        if (reparacion.id == id) {
          reparacion.dispositivo = dispositivoNuevo;
          fseek(reparaciones,-sizeof(Reparacion),SEEK_CUR);
          fwrite(&reparacion, sizeof(Reparacion), 1, reparaciones);
        }
      }
      fclose(reparaciones);
      break;
    }
    case 2:{
      printf("\n Modificar Fecha:\n");
      printf("\n Ingrese nueva fecha: ");
      char fechaNueva[11];
      FILE *reparaciones = fopen("reparaciones.dat","rb+");
      Reparacion reparacion;
      while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
        if (reparacion.id == id) {
          strcpy(reparacion.fecha,leerFecha(fechaNueva));
          fseek(reparaciones,-sizeof(Reparacion),SEEK_CUR);
          fwrite(&reparacion, sizeof(Reparacion), 1, reparaciones);
        }
      }
      fclose(reparaciones);
      break;
    }
    case 3:{
      printf("\n Modificar Costo del Software:\n");
      printf("\n Ingrese nuevo costo del Software: ");
      float nuevoCosto = leerFloat();
      //  actualizar reparacion
      FILE *reparaciones = fopen("reparaciones.dat","rb+");
      Reparacion reparacion;
      while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
        if (reparacion.id == id) {
          reparacion.costoSoftware = nuevoCosto;
          fseek(reparaciones,-sizeof(Reparacion),SEEK_CUR);
          fwrite(&reparacion, sizeof(Reparacion), 1, reparaciones);
        }
      }
      fclose(reparaciones);
      break;
    }
    case 4:{
      printf("\n Modificar Costo del Hardware:\n");
      printf("\n Ingrese nuevo costo del Hardware: ");
      float nuevoCosto = leerFloat();
      //  actualizar reparacion
      FILE *reparaciones = fopen("reparaciones.dat","rb+");
      Reparacion reparacion;
      while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
        if (reparacion.id == id) {
          reparacion.costoHardware = nuevoCosto;
          fseek(reparaciones,-sizeof(Reparacion),SEEK_CUR);
          fwrite(&reparacion, sizeof(Reparacion), 1, reparaciones);
        }
      }
      fclose(reparaciones);
      break;
    }
    case 5:{
      printf("\n Modificar Empleado:\n");
      menuElegirEmpleado();
      int empleadoElegido, maximoEmpleado = obtenerMaximoEmpleado();
      do{
        empleadoElegido = leerEntero();
      } while (empleadoElegido < 0 || empleadoElegido > maximoEmpleado);
      if (empleadoElegido != 0) {
        FILE *reparaciones = fopen("reparaciones.dat","rb+");
        Reparacion reparacion;
        while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
          if (reparacion.id == id) {
            cargarEmpleadoAReparacion(&reparacion, &empleadoElegido);
            fseek(reparaciones,-sizeof(Reparacion),SEEK_CUR);
            fwrite(&reparacion, sizeof(Reparacion), 1, reparaciones);
          }
        }
        fclose(reparaciones);
      }
      break;
    }
    case 6:{
      printf("\n Modificar Empresa:\n");
      menuElegirEmpresa();
      int empresaElegida, maximoEmpresa = obtenerMaximoEmpresa();
      do{
        empresaElegida = leerEntero();
      } while (empresaElegida < 0 || empresaElegida > maximoEmpresa);
      if (empresaElegida != 0) {
        FILE *reparaciones = fopen("reparaciones.dat","rb+");
        Reparacion reparacion;
        while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
          if (reparacion.id == id) {
            printf("\nCargando información de la empresa...\n");
            Empresa empresa;
            FILE *empresas = fopen("empresas.dat", "rb");
            verificarAbrirArchivo(empresas);
            
            reparacion.empresa.codigo = empresaElegida;

            fseek(empresas, 0, SEEK_SET);
            while (fread(&empresa, sizeof(Empresa), 1, empresas) == 1) {
              if (reparacion.empresa.codigo == empresa.codigo) {
                strcpy(reparacion.empresa.cuit, empresa.cuit);
                strcpy(reparacion.empresa.nombre, empresa.nombre);
              }
            }
            fclose(empresas);
            fseek(reparaciones,-sizeof(Reparacion),SEEK_CUR);
            fwrite(&reparacion, sizeof(Reparacion), 1, reparaciones);
            fseek(reparaciones,sizeof(Reparacion),SEEK_CUR);
            printf("Finalizado.\n");
          }
        }
        fclose(reparaciones);
      }
      break;
    }
  }
  //no dejar en blanco ningún atributo y actualizar los que dependen de otros
  FILE *reparaciones = fopen("reparaciones.dat","rb+");
  while (fread(&reparacion, sizeof(Reparacion), 1, reparaciones) == 1) {
    if (reparacion.id == id) {
      reparacion.precioFinal = CalcularPrecioFinal(&reparacion);
      fseek(reparaciones,-sizeof(Reparacion),SEEK_CUR);
      fwrite(&reparacion, sizeof(Reparacion), 1, reparaciones);
      fseek(reparaciones,sizeof(Reparacion),SEEK_CUR);
    }
  }
  fclose(reparaciones);
  //mostrar todas las reparaciones
  mostrarReparaciones();
  //volver al menu principal
  return;
}

void eliminarReparacion(int id) {
  //imprimir reparación elegida
  int confirmar = 0;
  Reparacion reparacion;
  char dispositivoReparado[20];
  FILE *reparacionesDAT = fopen("reparaciones.dat", "rb");
  verificarAbrirArchivo(reparacionesDAT);

  printf("\nReparaciones Almacenadas y Cargadas*: \n");

  printf("\n");
  printf("|%3s","ID");
  printf("|%-11s","Dispositivo");
  printf("|%2s%-6s%2s","","Fecha","");
  printf("|%4s%-6s%4s","","Precio","");
  printf("|%1s%-7s |","","Codigos");
  printf("\n");
  printf("|---|-----------|----------|--------------|---------|");
  while (fread(&reparacion, sizeof(Reparacion), 1, reparacionesDAT) == 1) {
    if (reparacion.id == id) {
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
  fclose(reparacionesDAT);
  printf("\n ¿Desea eliminar esta reparación?\n");
  printf("\t[1] Sí\t[0] No");
  printf("\nOpción: ");
  do{
    confirmar = leerEntero();
  } while (confirmar < 0 || confirmar > 1);
  if (confirmar != 0) {    
    //ELIMINAR REGISTRO
    //abrimos el archivo
    FILE *reparaciones = fopen("reparaciones.dat", "rb+");
    verificarAbrirArchivo(reparaciones);
    //sobreescribimos los registros
    //nos posicionamos al final del registro a eliminar
    fseek(reparaciones,sizeof(Reparacion)*(id),SEEK_SET);
    //avanzamos al siguiente registro y lo guardamos en una variable
    Reparacion siguiente;
    while (fread(&siguiente, sizeof(Reparacion), 1, reparaciones) == 1) {
      //nos posicionamos al inicio del anterior
      fseek(reparaciones,sizeof(Reparacion)*(-2),SEEK_CUR);
      //actualizamos su ID
      siguiente.id--;
      //escribimos el registro guardado en "siguiente" en el registro a eliminar
      fwrite(&siguiente, sizeof(Reparacion), 1, reparaciones);
      //avanzamos un registro
      fseek(reparaciones,sizeof(Reparacion),SEEK_CUR);
    }
    //eliminar el último registro
    int maximoReparaciones = obtenerMaximoReparacion();
    if (ftruncate(fileno(reparaciones), sizeof(Reparacion) * (maximoReparaciones-1)) != 0) {
      printf("\n Error al acortar el archivo.\n");
      return;
    }
    fclose(reparaciones);
  } else {
    //volver
    return;
  }
  mostrarReparaciones();
}