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
#include "main.h"

#define COLUMNAS 10

status_t imprimir_registros (struct estado * estado, FILE * f_output);
status_t imprimir_dump (struct estado * estado, struct instruccion *** instrucciones, struct parametros * parametros);
status_t imprimir_memoria (struct instruccion *** instrucciones, long cantidad_de_memoria, FILE * f_output);
status_t imprimir_bin (struct estado * estado, FILE * f_output, struct instruccion *** instrucciones, long cantidad_de_memoria);

#endif
