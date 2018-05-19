#ifndef FUNCIONES__H 
#define FUNCIONES__H 1

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "types.h"
#include "idioma.h"
#include "procesamiento.h"
#include "error.h"


#define MAX_MODULO 9999




status_t leer (struct instruccion *** instrucciones, size_t operando);
status_t seleccion_de_funcion (struct instruccion *** instrucciones, long cantidad_de_memoria, struct estado * estado);
status_t escribir (struct instruccion *** instrucciones, size_t operando);
status_t cargar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t guardar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t sumar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t restar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t dividir (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t multiplicar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t jmp (struct instruccion *** instrucciones, size_t operando, size_t * i);
status_t pcargar (struct instruccion *** instrucciones, long cantidad_de_memoria, size_t operando, long * acc);
status_t pguardar (struct instruccion *** instrucciones, long cantidad_de_memoria, size_t operando, long * acc);

#endif
