#ifndef FUNCIONES__H 
#define FUNCIONES__H 1

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "types.h"
#include "idioma.h"
#include "procesamiento.h"
#include "error.h"
#include "simpletron.h"



#define MAX_PALABRA 9999
#define MIN_PALABRA -9999




status_t leer (struct instruccion ** instrucciones, struct estado * estado);
status_t ejecutar_simpletron (struct instruccion ** instrucciones, long cantidad_de_memoria, struct estado * estado);
status_t escribir (struct instruccion ** instrucciones, struct estado * estado);
status_t cargar (struct instruccion ** instrucciones, struct estado * estado);
status_t guardar (struct instruccion ** instrucciones, struct estado * estado);
status_t sumar (struct instruccion ** instrucciones, struct estado * estado);
status_t restar (struct instruccion ** instrucciones, struct estado * estado);
status_t dividir (struct instruccion ** instrucciones, struct estado * estado);
status_t multiplicar (struct instruccion ** instrucciones, struct estado * estado);
status_t jmp (struct instruccion ** instrucciones, struct estado * estado, size_t *i);
status_t pcargar (struct instruccion ** instrucciones, struct estado * estado, long cantidad_de_memoria);
status_t pguardar (struct instruccion ** instrucciones, struct estado * estado, long cantidad_de_memoria);

#endif
