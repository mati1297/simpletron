#ifndef MAIN__H 
#define MAIN__H 1

#include "argumentos.h"
#include "types.h"
#include "dump.h"
#include "procesamiento.h"
#include "funciones.h"
#include "herramientas.h"
#include "error.h"
#include "simpletron.h"

struct parametros {
	long cantidad_de_memoria;
	char * file_input;
	bool_t stdin_input;
	bool_t bin_input;
	char * file_output;
	bool_t stdout_output;
	bool_t bin_output;
};

#endif
