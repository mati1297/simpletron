#ifndef ARGUMENTOS__H
#define ARGUMENTOS__H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGUMENTOS 11
#define MEMORIA_POR_OMISION 50
#define MAX_STR 30
#define EXTENSION "lms"
#define TXT_ARG_MEMORIA "-m"
#define TXT_ARG_FILE_INPUT "-i"
#define TXT_ARG_BIN_INPUT "-if"
#define TXT_ARG_FILE_OUTPUT "-o"
#define TXT_ARG_BIN_OUTPUT "-o"
#define TXT_ARG_HELP "-h"
#define TXT_INDICADOR_TEXTO "txt"
#define TXT_INDICADOR_BINARIO "bin"

typedef enum
{
	TRUE,
	FALSE
} bool_t;

typedef enum
{
	ARG_MEMORIA,
	ARG_FILE_INPUT,
	ARG_BIN_INPUT,
	ARG_FILE_OUTPUT,
	ARG_BIN_OUTPUT,
	ARG_HELP,
	ARG_INVALIDO
} arg_t;

/*STATUS_T QUE HAY QUE PASAR A OTRO ARCHIVO*/
typedef enum
{
	ST_OK,
	ST_ERROR_PUNTERO_NULO,
	ST_ERROR_CANTIDAD_ARGUMENTOS,
	ST_ERROR_MEMORIA_INVALIDA,
	ST_ERROR_CARACTER_INCORRECTO_MEMORIA,
	ST_ERROR_FILE_INPUT_DEMASIADO_LARGO,
	ST_ERROR_INPUT_EXTENSION_MAL,
	ST_ERROR_BIN_INPUT_MAL,
	ST_ERROR_FILE_OUTPUT_DEMASIADO_LARGO,
	ST_ERROR_OUTPUT_EXTENSION_MAL,
	ST_ERROR_BIN_OUTPUT_MAL,
	ST_HELP,
	ST_ERROR_ARGUMENTOS_INVALIDOS
} status_t;

struct parametros
{
	long memoria;
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
