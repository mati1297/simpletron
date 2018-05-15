#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "herramientas.h"

status_t split_str (char * str_in, size_t largo_str_in, char * str_out, size_t largo_str_out, int izq, int der) {
	size_t i;
	if (str_in == NULL || str_out == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (der >= largo_str_in || (der - izq) > largo_str_out)
		return ST_ERROR_DIMENSION;
	for (i = izq; i < der; i++) {
		str_out[i] = str_in[i];
	}
	return ST_OK;	
}

status_t cortar_cadena (char ** cadena, char delim) {
	
	char * ptr;
	
	if (cadena == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	if (ptr = strchr (*cadena, delim))
		*ptr = '\0';
	
	return ST_OK;
}
	
