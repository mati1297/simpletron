#include <stdio.h>
#include "error.h"
#include "types.h"
#include "idioma.h"

void imprimir_error (status_t st) {
	if(st != ST_OK)
	fprintf (stderr, "%s: %s\n", ERROR, error [st]);
} 
