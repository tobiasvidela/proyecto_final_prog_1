#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

/*  FUNCIONES PARA EL PROGRAMA */
//  AUXILIARES
void limpiarConsola() {
  #ifdef __unix__  // Unix/Linux/MacOS
    system("clear");
  #else _WIN32  // Windows
    system("cls");
  #endif
}

void limpiarBuffers() {
  fflush(stdout);//  Vaciar el búfer de salida
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    //  Descartar caracteres restantes en el búfer de entrada
  }
}

void continuar() {
  printf("\nPresiona Enter para continuar...");
  limpiarBuffers();
  getchar();//  Esperar a que el usuario presione Enter
}

int leerEntero() {
  int entero, control;
  do {
    printf("Ingresar un entero: ");
    if (scanf("%d", &entero) != 1){
      printf("\nDebes ingresar un entero.\n\n");
      limpiarBuffers();
      control = 1;
    } else {
      control = 0;
    }
  } while (control);
  return entero;
}

float leerFloat() {
  float numero;
  int control;
  do {
    printf("Ingresar un número decimal: ");
    if (scanf("%f", &numero) != 1) {
      printf("\nDebes ingresar un número decimal.\n\n");
      limpiarBuffers();
      control = 1;
    } else {
      control = 0;
    }
  } while (control);
  return numero;
}

char* leerFecha(char fecha[11]) {
  limpiarBuffers();
  int valido = 0;
  size_t longitud;

  while (!valido) {
    printf("Ingrese la fecha 'dd/mm/yyyy' : ");
    fgets(fecha, 11, stdin);//stdin (teclado)

    longitud = strlen(fecha);//longitud de un string(strlen)

    // Eliminar el carácter de nueva línea
    if (fecha[longitud - 1] == '\n') {
      fecha[longitud - 1] = '\0';
      longitud--;
    } else {
      limpiarBuffers();
    }

    // Validar el formato de la fecha
    if (longitud == 10 &&
      fecha[2] == '/' && fecha[5] == '/' &&
      esDigito(fecha[0]) && esDigito(fecha[1]) &&
      esDigito(fecha[3]) && esDigito(fecha[4]) &&
      esDigito(fecha[6]) && esDigito(fecha[7]) &&
      esDigito(fecha[8]) && esDigito(fecha[9])) {
      valido = 1;
    } else {
      printf("Formato de fecha incorrecto. Vuelva a intentarlo.\n");
    }
  }
  return fecha;
}

void imprimirCadenaCentrada(char *cadena, int ancho) {
  int longitudCadena = strlen(cadena);
  int espacios = (ancho - longitudCadena) / 2;
  int margenIzq = espacios;
  int margenDer = espacios;

  if ((ancho - longitudCadena) % 2 != 0) {margenDer++;}

  printf("%*s%s%*s",margenIzq,"",cadena,margenDer,"");
}

int esDigito(char c) {
  return (c >= '0' && c <= '9');
}

void verificarAbrirArchivo(FILE *archivo) {
  if (archivo == NULL) {
    printf("\nError al abrir/crear el archivo.\n");
    continuar();
    return;
  }
}

void verificarArchivoVacio(FILE *archivo) {
  fseek(archivo, 0, SEEK_END);
  if (ftell(archivo) == 0) {
    printf("\nEl archivo está vacío.\n");
    continuar();
    return;
  } else {
    fseek(archivo, 0, SEEK_SET);
  }
}