#ifndef FUNCIONES__H 
#define FUNCIONES__H 1

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "funciones.h"
#include "argumentos.h"
#include "procesamiento.h"

struct estado
{
	long acc;
	size_t contador;
	struct instruccion instruccion_actual;
};

status_t leer (struct instruccion *** instrucciones, size_t operando);
status_t seleccion_de_funcion (struct instruccion *** instrucciones, long cantidad_de_memoria, struct estado * estado);
status_t escribir (struct instruccion *** instrucciones, size_t operando);
status_t cargar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t guardar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t sumar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t restar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t dividir (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t multiplicar (struct instruccion *** instrucciones, size_t operando, long * acc);
status_t jmp (struct instruccion *** instrucciones, size_t operando,  long cantidad_de_memoria, size_t * i);

#endif
