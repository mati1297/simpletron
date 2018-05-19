#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "dump.h"
#include "procesamiento.h"
#include "funciones.h"

int main (int argc, const char * argv [])
{
	struct parametros params;
	struct instruccion ** instrucciones;
	struct estado estado_actual;
	status_t st;
	
	if (procesar_argumentos (argv, &params, argc) != ST_OK)
		return EXIT_FAILURE;
	
	if (params.bin_input == TRUE)
		if (procesamiento_bin (&instrucciones, &params) != ST_OK)
			return EXIT_FAILURE;
	else if (params.stdin_input == TRUE)
		if (procesamiento_stdin (&instrucciones, &params) != ST_OK)
			return EXIT_FAILURE;
	else /* deberia poner llaves? para que no lo interprete como un else if */
		if (procesamiento_txt (&instrucciones, &params) != ST_OK)
			return EXIT_FAILURE;
			
	if((st = seleccion_de_funcion (&instrucciones, params.cantidad_de_memoria, &estado_actual)) != ST_OK && st != ST_ERROR_SIMPLETRON)
		return EXIT_FAILURE;
		
	if(imprimir_dump(&estado_actual, &instrucciones, &params) != ST_OK)
		return EXIT_FAILURE;
		
	/*LIBERAR MEMORIA*/
	return EXIT_SUCCESS;
}
