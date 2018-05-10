#ifndef PROCESAMIENTO__H
#define PROCESAMIENTO__H

#include <stdio.h>

#define DELIM ';'

struct wololo {
	int numero_dato;
	signo_t signo;
	opcode_t opcode;
	size_t pos;
};

status_t procesamiento_txt (FILE * fi, struct wololo * wololo);
status_t cortar_cadena (char ** cadena, char delim);

#endif
