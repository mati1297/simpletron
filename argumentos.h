#ifndef ARGUMENTOS__H
#define ARGUMENTOS__H 1

#include "main.h"
#include "error.h"

#define MAX_ARGUMENTOS 11
#define MEMORIA_POR_OMISION 50
#define TXT_ARG_MEMORIA "-m"
#define TXT_ARG_FILE_INPUT "-i"
#define TXT_ARG_BIN_INPUT "-if"
#define TXT_ARG_FILE_OUTPUT "-o"
#define TXT_ARG_BIN_OUTPUT "-of"
#define TXT_ARG_HELP "-h"
#define TXT_INDICADOR_TEXTO "txt"
#define TXT_INDICADOR_BINARIO "bin"

typedef enum {
	ARG_MEMORIA = 0,
	ARG_FILE_INPUT = 1,
	ARG_BIN_INPUT = 2,
	ARG_FILE_OUTPUT = 3,
	ARG_BIN_OUTPUT = 4,
	ARG_HELP = 5,
	ARG_INVALIDO = 6
} arg_t;

status_t cargar_argumentos_por_omision (struct parametros * params);
status_t procesar_argumentos (const char * argv [], struct parametros * params, int argc);

#endif
