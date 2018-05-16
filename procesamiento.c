#include "procesamiento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "argumentos.h"
#include "types.h"
#include "procesamiento.h"


/* Esta función recibe un puntero a la estructura con la informacion sobre
 * los argumentos recibidos por la línea de comandos y también un vector
 * de punteros a estructuras en donde se gurdarán las instrucciones leídas
 * en el archivo de texto ingresado como argumento. Devuelve un estado a
 * través de la interfaz en caso de que ocurra un error o no */
status_t procesamiento_txt (struct instruccion *** memoria, struct parametros * params) {
	
	FILE * fi;
	char * buffer, * endp;
	char delim = DELIM;
	size_t i, j;
	status_t st;
	
	if (memoria == NULL || params == NULL) {
		
		return ST_ERROR_PUNTERO_NULO;
	}
	
	if ((fi = fopen (params -> file_input, "rt")) == NULL) {
		
		return ST_ERROR_LECTURA_ARCHIVO;
	}
		
	if ((buffer = (char *) malloc (sizeof (char) * MAX_CADENA)) == NULL) {
		
		fclose (fi);
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	
	for (i = 0; fgets (buffer, MAX_CADENA + 2, fi); i++) {
		
		if ((st = cortar_cadena (&buffer, delim)) != ST_OK) {
			
			fclose (fi);
			free (buffer);
			buffer = NULL;
			return st;
		}
		
		for (j = LARGO_INSTRUCCION; buffer [j]; i++) 
			if (!isspace (buffer[j])) {
				
				fclose (fi);
				free (buffer);
				buffer = NULL;
				return ST_ERROR_INSTRUCCION_INVALIDA;
			}
		
		(*memoria)[i] -> numero_dato = strtol (buffer, &endp, 10); 
		
		if (*endp && *endp != ' ') {
			
			fclose (fi);
			free (buffer);
			buffer = NULL;
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		
		(*memoria)[i] -> operando = ((*memoria)[i] -> numero_dato) % 100;
		(*memoria)[i] -> opcode = ((*memoria)[i] -> numero_dato) / 100;
		
	}
	free (buffer);
	buffer = NULL;
	
	if (ferror (fi)) {
		
		fclose (fi);
		return ST_ERROR_LECTURA_ARCHIVO;
	}
	
	fclose (fi);
	
	return ST_OK;
}

/* Esta función recibe un puntero a la estructura con la informacion sobre
 * los argumentos recibidos por la línea de comandos y también un vector
 * de punteros a estructuras en donde se gurdarán las instrucciones leídas
 * en el archivo binario ingresado como argumento. Devuelve un estado a
 * través de la interfaz en caso de que ocurra un error o no */
status_t procesamiento_bin (struct instruccion *** memoria, struct parametros * params) {
	
	FILE * fi;
	char * buffer, * endp;
	size_t i = 0, j = 0;
	
	if (memoria == NULL || params == NULL) {
		
		return ST_ERROR_PUNTERO_NULO;
	}
	
	if ((fi = fopen (params -> file_input, "rb")) == NULL) {
		
		return ST_ERROR_LECTURA_ARCHIVO;
	}
	
	if ((buffer = (char *) malloc (sizeof (char) * (LARGO_INSTRUCCION + 1))) == NULL) {
		
		fclose (fi);
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	
	while (fread (&buffer[i], sizeof (char), LARGO_INSTRUCCION, fi) == LARGO_INSTRUCCION) {
		
		(*memoria)[j] -> numero_dato = strtol (buffer, &endp, 10);
		
		if (*endp) {
			
			fclose (fi);
			free (buffer);
			buffer = NULL;
		}
		
		(*memoria)[j] -> operando = (*memoria)[j] -> numero_dato % 100;
		(*memoria)[j] -> opcode = (*memoria)[j] -> numero_dato / 100;
		
		if (fseek (fi, 1, SEEK_CUR) == -1) {
			
			fclose (fi);
			free (buffer);
			buffer = NULL;
			return ST_ERROR_LECTURA_ARCHIVO;
		}
		j++;
	}
	
	free (buffer);
	buffer = NULL;
	
	if (ferror (fi)) {
		
		fclose (fi);
		return ST_ERROR_LECTURA_ARCHIVO;
	}
	
	fclose (fi);
	
	return ST_OK;
}

/* Esta función recibe un puntero a la estructura con la informacion sobre
 * los argumentos recibidos por la línea de comandos y también un vector
 * de punteros a estructuras en donde se gurdarán las instrucciones leídas
 * por pantalla a medida de que el usuario las ingrese. Devuelve un estado
 * a través de la interfaz en caso de que ocurra un error o no */
status_t procesamiento_stdin (struct instruccion *** memoria, struct parametros * params) {
	
	char * buffer, * endp;
	long aux;
	status_t st;
	size_t i;
	
	if (memoria == NULL || params == NULL) {
		
		return ST_ERROR_PUNTERO_NULO;
	}
	
	if ((buffer = (char *) malloc (sizeof (char) * (LARGO_INSTRUCCION + 2))) == NULL) {
		
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	
	for (i = 0; i < params -> cantidad_de_memoria; i++) {
	
		if (fgets (buffer, LARGO_INSTRUCCION + 2, stdin) == NULL) {
			
			free (buffer);
			buffer = NULL;
			return ST_ERROR_ENTRADA_INVALIDA;
		}
		
		if ((st = cortar_cadena (&buffer, '\n')) != ST_OK) {
			
			free (buffer);
			buffer = NULL;
			return st;
		}
		
		aux = strtol (buffer, &endp, 10);
		
		if (*endp) {
			
			free (buffer);
			buffer = NULL;
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		if (aux == INSTRUCCION_FINAL)
			break;
			
		(*memoria)[i] -> numero_dato = aux;
		(*memoria)[i] -> operando = ((*memoria)[i] -> numero_dato) % 100;
		(*memoria)[i] -> opcode = ((*memoria)[i] -> numero_dato) / 100;		
	}
	
	free (buffer);
	buffer = NULL;
	
	return ST_OK;
}
