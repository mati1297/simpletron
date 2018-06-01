#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "argumentos.h"
#include "types.h"
#include "dump.h"
#include "procesamiento.h"
#include "funciones.h"
#include "herramientas.h"
#include "error.h"
#include "simpletron.h"


/* Recibe los argumentos ingresados por el usuario y la cantidad de argumentos
 * ingresados, incluyendo la ejecución del programa. Llama a las funciones
 * de más alto nivel del programa. Devuelve EXIT_FAILURE en caso de haber
 * un error o EXIT_SUCCESS en caso de que no lo haya */
int main (int argc, const char * argv [])
{
	struct parametros params;
	struct instruccion ** instrucciones;
	struct estado estado_actual;
	status_t st;
	size_t cant;
	
	if ((st = procesar_argumentos (argv, &params, argc)) != ST_OK) {
		if (st == ST_HELP) {
			if (imprimir_ayuda (stderr) != ST_OK)
				return EXIT_FAILURE;
			return EXIT_SUCCESS;
		}
		imprimir_error(st);
		return EXIT_FAILURE;
	}
		
	if ((st = pedir_memoria_vector_punteros(&instrucciones, &params, &cant)) != ST_OK) {
		liberar_vector_de_punteros (&instrucciones, cant);
		imprimir_error(st);
		return EXIT_FAILURE;
	}
	
	if (params.bin_input == TRUE) {
		if ((st = procesamiento_bin (instrucciones, &params)) != ST_OK){
			liberar_vector_de_punteros (&instrucciones, cant);
			imprimir_error(st);
			return EXIT_FAILURE;
		}
	}
	else if (params.stdin_input == TRUE) {
		if ((st = procesamiento_stdin (instrucciones, &params)) != ST_OK){
			liberar_vector_de_punteros (&instrucciones, cant);
			imprimir_error(st);
			return EXIT_FAILURE;
		}
	}
	else {
		if ((st = procesamiento_txt (instrucciones, &params)) != ST_OK) {
			liberar_vector_de_punteros (&instrucciones, cant);
			imprimir_error(st);
			return EXIT_FAILURE;
		}
	}
	
	st = ejecutar_simpletron (instrucciones, params.cantidad_de_memoria, &estado_actual);
		
	if (st != ST_OK) {
		imprimir_error(st);
		if (st != ST_ERROR_SIMPLETRON) {
			liberar_vector_de_punteros (&instrucciones, cant);
			return EXIT_FAILURE;
		}
	}
		
	if ((st = imprimir_dump (&estado_actual, instrucciones, params.bin_output, params.stdout_output, params.cantidad_de_memoria, params.file_output)) != ST_OK) {
		imprimir_error(st);
		liberar_vector_de_punteros (&instrucciones, cant);
		return EXIT_FAILURE;
	}
		
	liberar_vector_de_punteros (&instrucciones, cant);
	
	return EXIT_SUCCESS;
}
