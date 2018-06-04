#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "procesamiento.h"
#include "herramientas.h"
#include "types.h"
#include "error.h"
#include "simpletron.h"



/* Esta función recibe un puntero a la estructura con la informacion sobre
 * los argumentos recibidos por la línea de comandos y también un vector
 * de punteros a estructuras en donde se gurdarán las instrucciones leídas
 * en el archivo de texto ingresado como argumento. Devuelve un estado a
 * través den en caso del nombre que ocurra un error o no */
status_t procesamiento_txt (struct instruccion ** memoria, const char * file_input, long cantidad_de_memoria) {
	
	FILE * fi;
	char * buffer, * endp;
	char delim = DELIM;
	size_t i;
	status_t st;
	int aux;
	
	if (memoria == NULL) {
		return ST_ERROR_PUNTERO_NULO;
	}

	
	if ((fi = fopen (file_input, "rt")) == NULL) {
		return ST_ERROR_LECTURA_ARCHIVO;
	}
		
	if ((buffer = (char *) malloc (sizeof (char) * MAX_CADENA)) == NULL) {
		fclose (fi);
		
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	/*ARREGLE PARA QUE LEA SOLAMENTE HASTA QUE LE DA LA MEMORIA*/
	for (i = 0; i < cantidad_de_memoria ; i++) {
		
		
		/*Rellena si se pidio mas memoria de la necesaria*/
		if(!(fgets (buffer, MAX_CADENA, fi)))
			strcpy(buffer, INSTRUCCION_POR_OMISION);
		
		if ((st = cortar_cadena (buffer, delim)) != ST_OK) {
			fclose (fi);
			free (buffer);
			buffer = NULL;
			return st;
		}
		
		if (*recortar_espacios (buffer) == '\0')
			continue;
		
		aux = strtol (buffer, &endp, 10);
		
		if (*endp) {
			free (buffer);
			buffer = NULL;
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		if (aux < MIN_INSTRUCCION || aux > MAX_INSTRUCCION) {
			free (buffer);
			buffer = NULL;
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		memoria[i] -> instruccion = aux;
		memoria[i] -> operando = abs_t (aux) % MAX_CANT_OPERANDOS;
		memoria[i] -> opcode = aux / MAX_CANT_OPERANDOS;
		
	}
	
	/*Si se pidio la memoria justa, lee de nuevo para poder llegar a EOF*/
	fgets(buffer, MAX_CADENA, fi);
	
	free (buffer);
	buffer = NULL;
	
	 /*VE SI PUDO LEER TODO EL ARHCIVO O LE QUEDARON COSAS AFUERA*/
	if (!feof (fi)) {
		fclose (fi);
		return ST_ERROR_MEMORIA_INSUFICIENTE_ARCHIVO;
	}
	
	if (ferror (fi)) {
		fclose (fi);
		return ST_ERROR_LECTURA_ARCHIVO;
	}
	
	fclose (fi);
	
	return ST_OK;
}


/*Recibe un vector de punteros a la estructura de las instrucciones,
 * y la informacion del archivo de entrada y la cantidad de memoria
 * pedida por el usuario. Lee los datos de forma binaria y los guarda
 * en las distintas estructuras. Devuelve el estado por el nombre.*/
status_t procesamiento_bin (struct instruccion ** memoria, const char * file_input, long cantidad_de_memoria) {
	FILE * fi;
	int aux;
	size_t i;
	if (memoria == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if ((fi = fopen(file_input, "rb")) == NULL)
		return ST_ERROR_LECTURA_ARCHIVO;
	for(i = 0; i < cantidad_de_memoria && fread(&aux, sizeof(int), 1, fi); i++) {
		

		if (aux < MIN_INSTRUCCION || aux > MAX_INSTRUCCION)
			return ST_ERROR_INSTRUCCION_INVALIDA;
		memoria[i] -> instruccion = aux;
		memoria[i] -> opcode = aux / MAX_CANT_OPERANDOS;
		memoria[i] -> operando = abs_t(aux) % MAX_CANT_OPERANDOS;
	}
	
	
	fread(&aux, sizeof(int), 1, fi);
	
	if (!feof (fi)) {
		fclose (fi);
		return ST_ERROR_MEMORIA_INSUFICIENTE_ARCHIVO;
	}
	
	if (ferror (fi)) {
		fclose (fi);
		return ST_ERROR_LECTURA_ARCHIVO;
	}
	
	fclose (fi);
	
	return ST_OK;
}



/* Esta función recibe un puntero a el vector de punteros que representa la memoria
 * y la cantidad de memoria pedida por el usuario. Lee por stdin las palabras que
 * ingresa el usuario hasta que se termine la memoria solicitada o hasta
 * que el usuario ingrese un comando de finalización (-99999), todo lo que el usuario
 * no ingrese queda en +0000.*/
status_t procesamiento_stdin (struct instruccion ** memoria, long cantidad_de_memoria) {
	
	char * buffer, * endp;
	long aux;
	status_t st;
	size_t i;
	
	if (memoria == NULL) {
		return ST_ERROR_PUNTERO_NULO;
	}
	
	
	
	if ((buffer = (char *) malloc (sizeof (char) * (LARGO_INSTRUCCION + 2))) == NULL) {
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	
	for (i = 0; i < cantidad_de_memoria; i++) {
		
		/* Lleva la cuenta del N° de instrucción ingresado */
		printf ("%lu%s ", i, SEPARADOR_INGRESO);
		
		if (fgets (buffer, LARGO_INSTRUCCION + 3, stdin) == NULL) {
			free (buffer);
			buffer = NULL;
			return ST_ERROR_ENTRADA_INVALIDA;
		}
		
		if ((st = cortar_cadena (buffer, '\n')) != ST_OK) {
			
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
		
		if (aux == FIN_INGRESO)
			break;
		
		if (aux < MIN_INSTRUCCION || aux > MAX_INSTRUCCION) {
			free (buffer);
			buffer = NULL;
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		
		
			
		memoria[i] -> instruccion = aux;
		memoria[i] -> operando = abs_t (aux) % MAX_CANT_OPERANDOS;
		memoria[i] -> opcode = aux / MAX_CANT_OPERANDOS;
	}
	
	free (buffer);
	buffer = NULL;
	
	return ST_OK;
}
