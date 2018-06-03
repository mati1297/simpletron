#include <stdio.h>
#include <stdlib.h>

#define MAX_LARGO 100
#define MSJ_PRE_ERROR "Error"
#define MSJ_ERROR_ARCHIVO_NO_TERMINADO "el archivo no se terminó de leer"
#define MSJ_ERROR_ERROR_ARCHIVO "ocurrió un error al leer el archivo"
#define MSJ_ERROR_ARCHIVO_NO_LEIDO "no se pudo leer el archivo"
#define SEPARADOR ")"

int main(int argc, char * argv[])
{
	FILE * input;
	size_t i, j;
	int aux[MAX_LARGO];
	if (!(input = fopen(argv[1], "rb")))
	{
		fprintf(stderr, "%s: %s", MSJ_PRE_ERROR, MSJ_ERROR_ARCHIVO_NO_LEIDO);
		return EXIT_FAILURE;
	}
	for (i = 0; fread(&(aux[i]), sizeof(int), 1, input) && i < MAX_LARGO; i++)
		;
	
	if(!feof(input))
	{
		fprintf(stderr, "%s: %s", MSJ_PRE_ERROR, MSJ_ERROR_ARCHIVO_NO_TERMINADO);
		return EXIT_FAILURE;
	}
	
	if(ferror(input))
	{
		fprintf(stderr, "%s: %s", MSJ_PRE_ERROR, MSJ_ERROR_ERROR_ARCHIVO);
		return EXIT_FAILURE;
	}
	for(j = 0; j < i; j++)
		printf("%02lu%s  %+05d\n",j+1, SEPARADOR, aux [j]);
	return EXIT_SUCCESS;
}
