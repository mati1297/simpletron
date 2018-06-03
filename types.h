#ifndef TYPES__H
#define TYPES__H 1

#define MAX_STR 100
#define MAX_CADENA 100

typedef enum {
	FALSE,
	TRUE
} bool_t;

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
