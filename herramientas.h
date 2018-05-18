#ifndef HERRAMIENTAS__H
#define HERRAMIENTAS__H 1

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define ARCHIVO_AYUDA "ayuda.txt"
#define MAX_CADENA 100

status_t split_str (char * str_in, size_t largo_str_in, char * str_out, size_t largo_str_out, int izq, int der);
status_t cortar_cadena (char **, char);
void liberar_vector_de_punteros (struct instruccion ***, size_t);
status_t imprimir_ayuda (void);

#endif
