#ifndef PROCESAMIENTO__H
#define PROCESAMIENTO__H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "argumentos.h"
#include "types.h"
#include "herramientas.h"

#define DELIM ';'
#define LARGO_INSTRUCCION 5
#define MEMORIA_PEDIDA 100


struct wololo {
	int numero_dato;
	opcode_t opcode;
	size_t pos;
};

status_t procesamiento_txt (struct wololo ** memoria, struct parametros * params);
status_t procesamiento_bin (struct wololo ** memoria, struct parametros * params);
status_t procesamiento_stdin (struct wololo ** memoria, struct parametros * params);
status_t cortar_cadena (char ** cadena, char delim);

#endif
