#ifndef DUMP__H
#define DUMP__H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "procesamiento.h"
#include "simpletron.h"
#include "error.h"

#define COLUMNAS 10

status_t imprimir_registros (const struct simpletron * simpletron, FILE * f_output);
status_t imprimir_dump (const struct simpletron * simpletron, bool_t bin_output, bool_t stdout_output, size_t cantidad_de_memoria, const  char * file_output);
status_t imprimir_memoria (const struct simpletron * simpletron, long cantidad_de_memoria, FILE * f_output);
status_t imprimir_bin (const struct simpletron * simpletron, FILE * f_output, long cantidad_de_memoria);

#endif
