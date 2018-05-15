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
status_t procesamiento_txt (struct wololo ** memoria, struct parametros * params) { /*ver tema doble puntero o triple*/
	
	FILE * fi;
	char * buffer, * endp;
	char delim = DELIM;
	status_t st;
	
	if (memoria == NULL || params == NULL) {
		
		return ST_ERROR_PUNTERO_NULO;
	}
	
	if ((fi = fopen (params -> file_input, "rt")) == NULL) {
		
		return ST_ERROR_INPUT_FILE;
	}
		
	if ((buffer = (char *) malloc (sizeof (char) * MEMORIA_PEDIDA)) == NULL) {
		
		fclose (fi);
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	
	for (i = 0; fgets (buffer, MAX_STR + 2, fi); i++) {
		
		if ((st = cortar_cadena (&buffer, delim)) != ST_OK) {
			
			fclose (fi);
			free (buffer);
			buffer = NULL;
			return st;
		
		for (i = LARGO_INSTRUCCION; buffer [i]; i++) 
			if (!isspace (buffer[i])) {
				
				fclose (fi);
				free (buffer);
				buffer = NULL;
				return ST_ERROR_INSTRUCCION_INVALIDA;
			}
		
		(*memoria)[i] -> numero_dato = strtol (buffer, &endp, 10); /*LA RE FLASHASTE AMEO JAJAJ, FIJATE QUE EN OTRO LADO NO ESTE
		ASI TAMBIEN*/
		
		if (*endp && *endp != ' ') {
			
			fclose (fi);
			free (buffer);
			buffer = NULL;
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		
		(*memoria)[i] -> pos = ((*memoria)[i] -> numero_dato) % 100;
		(*memoria)[i] -> opcode = ((*memoria)[i] -> numero_dato) / 100;
		
		free (buffer);
		buffer = NULL;
		fclose (fi);

	}
	return ST_OK;
}

/* Esta función recibe un puntero a la estructura con la informacion sobre
 * los argumentos recibidos por la línea de comandos y también un vector
 * de punteros a estructuras en donde se gurdarán las instrucciones leídas
 * en el archivo binario ingresado como argumento. Devuelve un estado a
 * través de la interfaz en caso de que ocurra un error o no */
status_t procesamiento_bin (struct wololo ** memoria, struct parametros * params) {
	
	FILE * fi;
	char * buffer;
	
	if (memoria == NULL || params == NULL) {
		
		return ST_ERROR_PUNTERO_NULO;
	}
	
	if ((fi = fopen (params -> input_file, "rb")) == NULL) {
		
		return ST_ERROR_INPUT_FILE;
	}
	
	if ((buffer = (char *) malloc (sizeof (char) * MEMORIA_PEDIDA)) == NULL) {
		
		fclose (fi);
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	
	for (i = 0; i < params -> cantidad_de_memoria; i++) {
		
		fread (buffer, sizeof (char), MEMORIA_PEDIDA, fi);
		
		if (*buffer == EOF)
			break;
			
								/* sin terminar */
	
	}
		
	
	return ST_OK;
}

/* Esta función recibe un puntero a la estructura con la informacion sobre
 * los argumentos recibidos por la línea de comandos y también un vector
 * de punteros a estructuras en donde se gurdarán las instrucciones leídas
 * por pantalla a medida de que el usuario las ingrese. Devuelve un estado
 * a través de la interfaz en caso de que ocurra un error o no */
status_t procesamiento_stdin (struct wololo ** memoria, struct parametros * params) {
	
	char * buffer;
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
		
		aux = strtol (buffer, &endp, 10 /*donde esta declarada aux??*/
		
		if (*endp) {
			
			free (buffer);
			buffer = NULL;
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		if (aux == INSTRUCCION_FINAL)
			break;
			
		(*memoria)[i] -> numero_dato = aux;
		(*memoria)[i] -> pos = ((*memoria)[i] -> numero_dato) % 100;
		(*memoria)[i] -> opcode = ((*memoria)[i] -> numero_dato) / 100;		
	}
	
	free (buffer);
	buffer = NULL;
	
	return ST_OK;
}
