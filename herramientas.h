#ifndef HERRAMIENTAS__H
#define HERRAMIENTAS__H 1

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "types.h"
#include "idioma.h"
#include "error.h"
#include "simpletron.h"

#define MAX_CADENA 100

status_t cortar_cadena (char *, char);
void liberar_vector_de_punteros (struct instruccion ***, size_t);
status_t imprimir_ayuda (FILE * f_out);
status_t pedir_memoria_vector_punteros (struct instruccion *** memoria, long cantidad_de_memoria, size_t * cant);
char * recortar_espacios (char * s);
int abs_t (int x);

#endif
