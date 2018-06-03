#ifndef PROCESAMIENTO__H
#define PROCESAMIENTO__H 1

#include "error.h"
#include "simpletron.h"

#define DELIM ';'
#define MAX_CANT_OPERANDOS 100
#define INSTRUCCION_POR_OMISION "+0000"
#define SEPARADOR_INGRESO ")"
#define FIN_INGRESO -99999

status_t procesamiento_txt (struct instruccion ** memoria, const char * file_input, long cantidad_de_memoria);
status_t procesamiento_bin (struct instruccion ** memoria, const char * file_input, long cantidad_de_memoria);
status_t procesamiento_stdin (struct instruccion ** memoria, long cantidad_de_memoria);

#endif
