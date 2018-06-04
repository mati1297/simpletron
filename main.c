#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "dump.h"
#include "procesamiento.h"
#include "funciones.h"
#include "herramientas.h"
#include "error.h"
#include "simpletron.h"
#include "argumentos.h"
#include "types.h"

/* Recibe los argumentos ingresados por el usuario y la cantidad de argumentos
 * ingresados, incluyendo la ejecución del programa. Llama a las funciones
 * de más alto nivel del programa. Devuelve EXIT_FAILURE en caso de haber
 * un error o EXIT_SUCCESS en caso de que no lo haya */
int main (int argc, const char * argv [])
{
	struct parametros params;
	struct simpletron simpletron;
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
		
	if ((st = pedir_memoria_vector_punteros((&simpletron.memoria), params.cantidad_de_memoria, &cant)) != ST_OK) {
		liberar_vector_de_punteros (&(simpletron.memoria), cant);
		imprimir_error(st);
		return EXIT_FAILURE;
	}
	
	if (params.bin_input == TRUE) {
		if ((st = procesamiento_bin (simpletron.memoria, params.file_input, params.cantidad_de_memoria)) != ST_OK){
			liberar_vector_de_punteros (&(simpletron.memoria), cant);
			imprimir_error(st);
			return EXIT_FAILURE;
		}
	}
	else if (params.stdin_input == TRUE) {
		if ((st = procesamiento_stdin (simpletron.memoria, params.cantidad_de_memoria)) != ST_OK){
			liberar_vector_de_punteros (&(simpletron.memoria), cant);
			imprimir_error(st);
			return EXIT_FAILURE;
		}
	}
	else {
		if ((st = procesamiento_txt (simpletron.memoria, params.file_input, params.cantidad_de_memoria)) != ST_OK) {
			liberar_vector_de_punteros (&(simpletron.memoria), cant);
			imprimir_error(st);
			return EXIT_FAILURE;
		}
	}
	
	st = ejecutar_simpletron (&simpletron, params.cantidad_de_memoria);
		
	if (st != ST_OK) {
		imprimir_error(st);
		if (st != ST_ERROR_SIMPLETRON) {
			liberar_vector_de_punteros (&(simpletron.memoria), cant);
			return EXIT_FAILURE;
		}
	}
		
	if ((st = imprimir_dump (&simpletron, params.bin_output, params.stdout_output, params.cantidad_de_memoria, params.file_output)) != ST_OK) {
		imprimir_error(st);
		liberar_vector_de_punteros (&(simpletron.memoria), cant);
		return EXIT_FAILURE;
	}
		
	liberar_vector_de_punteros (&(simpletron.memoria), cant);
	
	return EXIT_SUCCESS;
}
