#ifndef FUNCIONES__H 
#define FUNCIONES__H 1

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "funciones.h"
#include "argumentos.h"
#include "procesamiento.h"
#include "idioma.h"

status_t leer (struct instruccion *** instrucciones, size_t operando, long cantidad_de_memoria);
status_t seleccion_de_funcion (struct instruccion *** instrucciones, long cantidad_de_memoria, struct estado * estado);
status_t escribir (struct instruccion *** instrucciones, size_t operando, long cantidad_de_memoria);
status_t cargar (struct instruccion *** instrucciones, size_t operando, long * acc, long cantidad_de_memoria);
status_t guardar (struct instruccion *** instrucciones, size_t operando, long * acc, long cantidad_de_memoria);
status_t sumar (struct instruccion *** instrucciones, size_t operando, long * acc, long cantidad_de_memoria);
status_t restar (struct instruccion *** instrucciones, size_t operando, long * acc, long cantidad_de_memoria);
status_t dividir (struct instruccion *** instrucciones, size_t operando, long * acc, long cantidad_de_memoria);
status_t multiplicar (struct instruccion *** instrucciones, size_t operando, long * acc, long cantidad_de_memoria);
status_t jmp (struct instruccion *** instrucciones, size_t operando,  long cantidad_de_memoria, size_t * i);
status_t pcargar (struct instruccion *** instrucciones, size_t operando, long cantidad_de_memoria, long * acc);

#endif
