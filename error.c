#include "error.h"
#include "types.h"
#include "idioma.h"

void imprimir_error (status_t st) {
	fprintf (stderr, "%s: %s\n", ERROR, error [st]);
} 
