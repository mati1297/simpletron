#include <stdio.h>
#include "error.h"
#include "types.h"
#include "idioma.h"

void imprimir_error (status_t st) {
	
	char error [][MAX_ERROR_STR] = {
	NO_HAY_ERROR,
	MSJ_ERROR_PUNTERO_NULO,
	MSJ_ERROR_CANTIDAD_DE_ARGS,
	MSJ_ERROR_MEMORIA_INSUFICIENTE,
	MSJ_ERROR_ENTRADA_INVALIDA,
	MSJ_ERROR_FILE_INPUT_DEMASIADO_LARGO,
	MSJ_ERROR_FILE_OUTPUT_DEMASIADO_LARGO,
	MSJ_ERROR_ARGUMENTO_INVALIDO,
	MSJ_ERROR_INSTRUCCION_INVALIDA,
	MSJ_ERROR_LECTURA_ARCHIVO,
	MSJ_ERROR_SIMPLETRON
};
	
	if(st != ST_OK)
		fprintf (stderr, "%s: %s\n", ERROR, error [st]);
} 
