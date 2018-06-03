#ifndef MAIN__H
#define MAIN__H 1

#include "types.h"

struct parametros {
	long cantidad_de_memoria;
	const char * file_input;
	bool_t stdin_input;
	bool_t bin_input;
	const char * file_output;
	bool_t stdout_output;
	bool_t bin_output;
};

#endif
