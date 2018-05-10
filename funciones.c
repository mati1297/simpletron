#include <stdio.h>
#include <stdlib.h>
#include <string.h>

status_t split_str (char * str_in, char * str_out, int izq, int der) {
	size_t i;
	
	
}


status_t split (const char * str, size_t * n, char *** fields, char delim) {
	
	size_t i, j = 0, k, n_fields = 0;
	
	if (n == NULL || str == NULL || fields == NULL)
		return ERROR_NULL_POINTER;

	if (((*fields) = (char **) malloc (sizeof (char *) * (*n))) == NULL)
		return ERROR_MEMORY;
	
	for (i = 0; i < (*n); i++) {
		
		if (((*fields) [i] = malloc (sizeof (char) * (MAX_GPS_FIELD+1))) == NULL) {
			free (fields);
			fields = NULL;
			return ERROR_MEMORY;
		}
		for (k = 0; str [j] != delim && str [j]; j++, k++)
			(*fields) [i][k] = str[j];
		(*fields) [i][k] = '\0';
		j++;
		n_fields++;
	}
	(*n) = n_fields;
	return OK;
}

