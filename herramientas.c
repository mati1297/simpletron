#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "herramientas.h"
#include "idioma.h"
#include "error.h"
#include "simpletron.h"

/* Recibe por puntero una cadena y un delimitador. Recorta la cadena en
 * el delimitador indicado, dejando la parte del principio hasta el delimitador,
 * reemplazándolo por el \0. En caso de un error o que todo funcione en
 * orden lo informa a través del nombre */
status_t cortar_cadena (char * cadena, char delim) {
	
	char * ptr;
	
	if (cadena == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	if ((ptr = strchr (cadena, delim)))
		*ptr = '\0';
	
	return ST_OK;
}

/* Recibe por puntero una estructura con la información de las instrucciones,
 * otra estructura con la información de los parámetros y la cantidad de
 * estructuras cargadas en memoria. Pide la memoria para las estructuras
 * que contienen las instrucciones. En caso de un error o que todo funcione en
 * orden lo informa a través del nombre */
status_t pedir_memoria_vector_punteros (struct instruccion *** memoria, long cantidad_de_memoria, size_t * cant) {
	if (memoria == NULL) {
		return ST_ERROR_PUNTERO_NULO;
	}
	
	if (!(*memoria = (struct instruccion **) malloc (sizeof (struct instruccion *) * cantidad_de_memoria))) {
		*memoria = NULL;
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	
	for ((*cant) = 0; (*cant) < cantidad_de_memoria; (*cant)++)
		if (!((*memoria) [(*cant)] = (struct instruccion *) calloc (1, sizeof (struct instruccion)))) {
			return ST_ERROR_MEMORIA_INVALIDA;
		}
	return ST_OK;
}

/* Recibe por puntero una estructura con la información de las instrucciones
 * y la cantidad de estructuras cargadas en memoria. Libera el vector de
 * punteros a estructuras. No devuelve nada */
void liberar_vector_de_punteros (struct instruccion *** mem, size_t cant) {
	
	if (mem && *mem) {
		while (cant--) {
			free ((*mem) [cant]);
			(*mem) [cant] = NULL;
		}
		free (*mem);
		(*mem) = NULL;
	}
}

/* No recibe nada. Imprime un archivo con ayuda para la ejecución del
 * programa por stdout. En caso de un error o que todo funcione en orden
 * lo informa a través del nombre */
status_t imprimir_ayuda (FILE * f_out) {
	FILE * fhelp;
	char * buffer;
	if (!(fhelp = fopen (ARCHIVO_AYUDA, "rt"))) 
		return ST_ERROR_LECTURA_ARCHIVO;
	
	if (!(buffer = (char *) malloc (sizeof (char) * MAX_CADENA))) {
		fclose (fhelp);
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	while (fgets (buffer, MAX_CADENA + 2, fhelp))
		fprintf (f_out, "%s", buffer);
	free (buffer);
	if (ferror (fhelp)) {
		fclose (fhelp);
		return ST_ERROR_LECTURA_ARCHIVO;
	}
	fclose (fhelp);
	return ST_OK;
}

/* Recibe una cadena. Le saca los espacios de al comienzo y de al final.
 * Devuelve la cadena sin los espacios. */
char * recortar_espacios (char * s) {
	char * inicio, * fin;
	for (inicio = s; isspace (*inicio) && *inicio; inicio++)
		;
	if (!(*inicio)) {
		*s = '\0';
		return s;
	}
	for (fin = s + strlen (s) - 1; isspace (*fin) && fin != s; fin--)
		;
	*++fin = '\0';
	return memmove (s, inicio, fin - inicio + 1);
}
