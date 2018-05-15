#include <stdio.h>

int main (int argc, char * argv [])
{
	struct parametros params;
	status_t st;
	
	if ((st = procesar_argumentos (argv, &params, argc)) != ST_OK)
		return st;
	
	return EXIT_SUCCESS;
}
