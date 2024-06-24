#pragma once 
//funciones para el programa
//AUXILIARES
void limpiarConsola();
void limpiarBuffers();
void continuar();
int leerEntero();
float leerFloat();
char* leerFecha(char fecha[11]);
void imprimirCadenaCentrada(char *cadena, int ancho);
int esDigito(char c);
void verificarAbrirArchivo(FILE *archivo);
void verificarArchivoVacio(FILE *archivo);