#ifndef HERRAMIENTAS__H
#define HERRAMIENTAS__H 1

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "idioma.h"

#define MAX_CADENA 100

status_t cortar_cadena (char **, char);
void liberar_vector_de_punteros (struct instruccion ***, size_t);
status_t imprimir_ayuda (void);

#endif
