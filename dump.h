#ifndef DUMP__H
#define DUMP__H

#include <stdio.h>
#include <stdlib.h>
#include "dump.h"
#include "types.h"
#include "argumentos.h"
#include "funciones.h"
#include "procesamiento.h"
#include "idioma.h"
#include "error.h"
#include "simpletron.h"

#define COLUMNAS 10

status_t imprimir_registros (struct simpletron * simpletron, FILE * f_output);
status_t imprimir_dump (struct simpletron * simpletron, bool_t bin_output, bool_t stdout_output, size_t cantidad_de_memoria, char * file_output);
status_t imprimir_memoria (struct simpletron * simpletron, long cantidad_de_memoria, FILE * f_output);
status_t imprimir_bin (struct simpletron * simpletron, FILE * f_output, long cantidad_de_memoria);

#endif
