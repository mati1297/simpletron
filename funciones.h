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
	struct wololo instruccion_actual;
};

status_t leer (struct wololo *** instrucciones, size_t pos);
status_t seleccion_de_funcion (struct wololo *** instrucciones, long cantidad_de_memoria, struct estado * estado);
status_t escribir (struct wololo *** instrucciones, size_t pos);
status_t cargar (struct wololo *** instrucciones, size_t pos, long * acc);
status_t guardar (struct wololo *** instrucciones, size_t pos, long * acc);
status_t sumar (struct wololo *** instrucciones, size_t pos, long * acc);
status_t restar (struct wololo *** instrucciones, size_t pos, long * acc);
status_t dividir (struct wololo *** instrucciones, size_t pos, long * acc);
status_t multiplicar (struct wololo *** instrucciones, size_t pos, long * acc);
status_t jmp (struct wololo *** instrucciones, size_t pos,  long cantidad_de_memoria, size_t * i);

#endif
