#include "procesamiento.h"
#include <stdio.h>

status_t procesamiento_txt (FILE * fi, struct wololo * wololo) {
	
	char * aux, * endp;
	char delim = DELIM;
	
	fopen (fi, "rt"); /* validar? */
	
	for (i = 0; fgets (aux, MAX_STR - 2, fi); i++) {
		
		if ((cortar_cadena (&aux, delim)) != ST_OK)
			return queseyo;
		
		wololo->vec[i] = strtol (aux, &endp, 10);
		
		
}

status_t cortar_cadena (char ** cadena, char delim) {
	
	char * ptr;
	
	if (!cadena)
		return ST_ERROR_PUNTERO_NULO;
	
	if (ptr = strchr (*cadena, delim))
		*ptr = '\0';
	
	return ST_OK;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
