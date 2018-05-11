#ifndef ARGUMENTOS__H
#define ARGUMENTOS__H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_ARGUMENTOS 11
#define MEMORIA_POR_OMISION 50
#define MAX_STR 30
#define EXTENSION_TXT ".lms"
#define EXTENSION_BIN ".bin"
#define LARGO_EXTENSION 4
#define TXT_ARG_MEMORIA "-m"
#define TXT_ARG_FILE_INPUT "-i"
#define TXT_ARG_BIN_INPUT "-if"
#define TXT_ARG_FILE_OUTPUT "-o"
#define TXT_ARG_BIN_OUTPUT "-o"
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

struct parametros {
	long cantidad_de_memoria;
	char file_input [MAX_STR];
	bool_t stdin_input;
	bool_t bin_input;
	char file_output [MAX_STR];
	bool_t stdout_output;
	bool_t bin_output;
};

status_t cargar_argumentos_por_omision (struct parametros * argv);
status_t procesar_argumentos (const char ** vec_argv, struct parametros * argv, int argc);

#endif
