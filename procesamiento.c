#include "procesamiento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "herramientas.h"
#include "argumentos.h"
#include "types.h"


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
	/*ARREGLE PARA QUE LEA SOLAMENTE HASTA QUE LE DA LA MEMORIA*/
	for (i = 0; i < params -> cantidad_de_memoria ; i++) {
		
		
		/*Rellena si se pidio mas memoria de la necesaria*/
		if(!(fgets (buffer, MAX_CADENA + 2, fi)))
			strcpy(buffer, INSTRUCCION_POR_OMISION);
		
		if ((st = cortar_cadena (&buffer, delim)) != ST_OK) {
			fclose (fi);
			free (buffer);
			buffer = NULL;
			
			
			return st;
		}
		
		if (buffer[0] != '-' && buffer[0] != '+') {
			fclose (fi);
			free (buffer);
			buffer = NULL;
			
			
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		
		for (j = LARGO_INSTRUCCION; buffer [j]; j++) 
			if (!isspace (buffer[j])) {
				fclose (fi);
				free (buffer);
				buffer = NULL;
				
				
				return ST_ERROR_INSTRUCCION_INVALIDA;
			}
		
		(*memoria)[i] -> numero_dato = strtol (buffer, &endp, 10); 
		
		if (*endp && *endp != ' ' && *endp != '\n') {
			
			fclose (fi);
			free (buffer);
			buffer = NULL;
			
			
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		
		/*Lo vuelve siempre positivo porque sino cuando se convierte a size_t no lo convierte correctamente*/
		if (((*memoria)[i] -> numero_dato) < 0)
			(*memoria)[i] -> operando = (((*memoria)[i] -> numero_dato) * (-1)) % MAX_CANT_OPERANDOS;
		else
			(*memoria)[i] -> operando = ((*memoria)[i] -> numero_dato) % MAX_CANT_OPERANDOS;
		(*memoria)[i] -> opcode = ((*memoria)[i] -> numero_dato) / MAX_CANT_OPERANDOS;
		
	}
	
	/*Si se pidio la memoria justa, lee de nuevo para poder llegar a EOF*/
	fgets(buffer, MAX_CADENA +2, fi);
	
	free (buffer);
	buffer = NULL;
	
	 /*VE SI PUDO LEER TODO EL ARHCIVO O LE QUEDARON COSAS AFUERA*/
	if (!feof (fi)) {
		fclose (fi);
		return ST_ERROR_LECTURA_ARCHIVO;
	}
	
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
			
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		
		if (((*memoria)[i] -> numero_dato) < 0)
			(*memoria)[i] -> operando = (((*memoria)[i] -> numero_dato) * (-1)) % MAX_CANT_OPERANDOS;
		else
			(*memoria)[i] -> operando = ((*memoria)[i] -> numero_dato) % MAX_CANT_OPERANDOS;
		(*memoria)[i] -> opcode = ((*memoria)[i] -> numero_dato) / MAX_CANT_OPERANDOS;
		
		j++;
	}
	
	free (buffer);
	buffer = NULL;
	
	if (!feof (fi)) {
		fclose (fi);
		return ST_ERROR_LECTURA_ARCHIVO;
	}
	
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
		
		/* Lleva la cuenta del N° de instrucción ingresado */
		printf ("%lu) ", i);
		
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
		
		/*Validacion para que haya que poner signo y no mas de 5 digitos (contando signo)*/
		if (strlen (buffer) != 5 || (buffer [0] != '+' && buffer [0] != '-')) {
			free (buffer);
			buffer = NULL;
			return ST_ERROR_ENTRADA_INVALIDA;
		}
		
		aux = strtol (buffer, &endp, 10);
		
		if (*endp) {
			
			free (buffer);
			buffer = NULL;
			
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
			
		(*memoria)[i] -> numero_dato = aux;
		if (((*memoria)[i] -> numero_dato) < 0)
			(*memoria)[i] -> operando = (((*memoria)[i] -> numero_dato) * (-1)) % MAX_CANT_OPERANDOS;
		else
			(*memoria)[i] -> operando = ((*memoria)[i] -> numero_dato) % MAX_CANT_OPERANDOS;
		(*memoria)[i] -> opcode = ((*memoria)[i] -> numero_dato) / MAX_CANT_OPERANDOS;
	}
	
	free (buffer);
	buffer = NULL;
	
	return ST_OK;
}
