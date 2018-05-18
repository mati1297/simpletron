#include <stdio.h>

int main (int argc, char * argv [])
{
	struct parametros params;
	struct intruccion ** memoria;
	
	if (procesar_argumentos (argv, &params, argc) != ST_OK)
		return EXIT_FAILURE;
	
	if (params.bin_input == TRUE)
		if (procesamiento_bin (&memoria, &params) != ST_OK)
			return EXIT_FAILURE;
	else if (params.stdin_input == TRUE)
		if (procesamiento_stdin (&memoria, &params) != ST_OK)
			return EXIT_FAILURE;
	else /* deberia poner llaves? para que no lo interprete como un else if */
		if (procesamiento_txt (&memoria, &params) != ST_OK)
			return EXIT_FAILURE;
	
	
	
	return EXIT_SUCCESS;
}
