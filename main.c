#include <stdio.h>
#include <stdlib.h>
#include "argumentos.h"
#include "types.h"
#include "dump.h"
#include "procesamiento.h"
#include "funciones.h"
#include "herramientas.h"

int main (int argc, const char * argv [])
{
	struct parametros params;
	struct instruccion ** instrucciones;
	struct estado estado_actual;
	status_t st;
	
	if (procesar_argumentos (argv, &params, argc) != ST_OK)
		return EXIT_FAILURE;
	
	if (params.bin_input == TRUE) {
		if (procesamiento_bin (&instrucciones, &params) != ST_OK)
			return EXIT_FAILURE;
	}
	else if (params.stdin_input == TRUE) {
		if (procesamiento_stdin (&instrucciones, &params) != ST_OK)
			return EXIT_FAILURE;
	}
	else {
		if (procesamiento_txt (&instrucciones, &params) != ST_OK)
			return EXIT_FAILURE;
	}
	
	st = seleccion_de_funcion (&instrucciones, params.cantidad_de_memoria, &estado_actual);
		
	if (st != ST_OK && st != ST_ERROR_SIMPLETRON) {
		liberar_vector_de_punteros (&instrucciones, params.cantidad_de_memoria);
		return EXIT_FAILURE;
	}
		
	if (imprimir_dump (&estado_actual, &instrucciones, &params) != ST_OK) {
		liberar_vector_de_punteros (&instrucciones, params.cantidad_de_memoria);
		return EXIT_FAILURE;
	}
		
	liberar_vector_de_punteros (&instrucciones, params.cantidad_de_memoria);
	
	return EXIT_SUCCESS;
}
