#ifndef PROCESAMIENTO__H
#define PROCESAMIENTO__H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "herramientas.h"

#define DELIM ';'
#define LARGO_INSTRUCCION 5
#define MAX_CANT_OPERANDOS 100

status_t procesamiento_txt (struct instruccion *** memoria, struct parametros * params);
status_t procesamiento_bin (struct instruccion *** memoria, struct parametros * params);
status_t procesamiento_stdin (struct instruccion *** memoria, struct parametros * params);
status_t cortar_cadena (char ** cadena, char delim);

#endif
