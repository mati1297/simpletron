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
	size_t cant;
	
	if ((st = procesar_argumentos (argv, &params, argc)) != ST_OK && st != ST_HELP) {
		imprimir_error(st);
		return EXIT_FAILURE;
	}
		
	if (st == ST_HELP)
		return EXIT_SUCCESS;
		
	if ((st = pedir_memoria_vector_punteros(&instrucciones, &params, &cant)) != ST_OK) {
		liberar_vector_de_punteros (&instrucciones, cant);
		imprimir_error(st);
		return EXIT_FAILURE;
	}
	
	if (params.bin_input == TRUE) {
		if ((st = procesamiento_bin (&instrucciones, &params)) != ST_OK){
			liberar_vector_de_punteros (&instrucciones, cant);
			imprimir_error(st);
			return EXIT_FAILURE;
		}
	}
	else if (params.stdin_input == TRUE) {
		if ((st = procesamiento_stdin (&instrucciones, &params)) != ST_OK){
			liberar_vector_de_punteros (&instrucciones, cant);
			imprimir_error(st);
			return EXIT_FAILURE;
		}
	}
	else {
		if ((st = procesamiento_txt (&instrucciones, &params)) != ST_OK) {
			liberar_vector_de_punteros (&instrucciones, cant);
			imprimir_error(st);
			return EXIT_FAILURE;
		}
	}
	
	st = seleccion_de_funcion (&instrucciones, params.cantidad_de_memoria, &estado_actual);
		
	if (st != ST_OK) {
		imprimir_error(st);
		if (st != ST_ERROR_SIMPLETRON) {
			liberar_vector_de_punteros (&instrucciones, cant);
			return EXIT_FAILURE;
		}
	}
		
	if ((st = imprimir_dump (&estado_actual, &instrucciones, &params)) != ST_OK) {
		imprimir_error(st);
		liberar_vector_de_punteros (&instrucciones, cant);
		return EXIT_FAILURE;
	}
		
	liberar_vector_de_punteros (&instrucciones, cant);
	
	return EXIT_SUCCESS;
}
