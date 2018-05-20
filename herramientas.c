#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "herramientas.h"

status_t cortar_cadena (char ** cadena, char delim) {
	
	char * ptr;
	
	if (cadena == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	if ((ptr = strchr (*cadena, delim)))
		*ptr = '\0';
	
	return ST_OK;
}

void liberar_vector_de_punteros (struct instruccion *** mem, size_t cant) {
	
	if (mem) {
		while (cant--) {
			free ((*mem) [cant]);
			(*mem) [cant] = NULL;
		}
		free (*mem);
		(*mem) = NULL;
	}
}

status_t imprimir_ayuda (void) {
	FILE * fhelp;
	char * buffer;
	if (!(fhelp = fopen (ARCHIVO_AYUDA, "rt"))) 
		return ST_ERROR_LECTURA_ARCHIVO;
	
	if (!(buffer = (char *) malloc (sizeof (char) * MAX_CADENA))) {
		fclose (fhelp);
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	while (fgets (buffer, MAX_CADENA + 2, fhelp))
		printf ("%s", buffer);
	free (buffer);
	if (ferror (fhelp)) {
		fclose (fhelp);
		return ST_ERROR_LECTURA_ARCHIVO;
	}
	fclose (fhelp);
	return ST_OK;
}
	
