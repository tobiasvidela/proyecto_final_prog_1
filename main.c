#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "menu.h"

int main(void) {
  int opcion;
  do {
    //imprimir menu principal
    limpiarConsola();
    menu();
    //elegir opcion
    printf("\n\n\t Seleccione una opción: ");
    opcion = leerEntero();
    //imprimir opcion seleccionada
    limpiarConsola();
    menuSecundario(opcion);
  } while (opcion != 0);
  printf("\n Programa terminado correctamente.");
  return 0;
}