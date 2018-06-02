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
status_t procesamiento_txt (struct instruccion ** memoria, char * file_input, long cantidad_de_memoria) {
	
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


/*Recibe un vector de punteros a la estructura de las instrucciones,
 * y la informacion del archivo de entrada y la cantidad de memoria
 * pedida por el usuario. Lee los datos de forma binaria y los guarda
 * en las distintas estructuras. Devuelve el estado por el nombre.*/
status_t procesamiento_bin (struct instruccion ** memoria, char * file_input, long cantidad_de_memoria) {
	FILE * fi;
	int aux;
	size_t i;
	if (memoria == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if ((fi = fopen(file_input, "rb")) == NULL)
		return ST_ERROR_LECTURA_ARCHIVO;
	for(i = 0; i < cantidad_de_memoria; i++) {
		fread(&aux, sizeof(int), 1, fi);

		if (aux < MIN_INSTRUCCION || aux > MAX_INSTRUCCION)
			return ST_ERROR_INSTRUCCION_INVALIDA;
		memoria[i] -> instruccion = aux;
		memoria[i] -> opcode = aux / MAX_CANT_OPERANDOS;
		memoria[i] -> operando = abs_t(aux) % MAX_CANT_OPERANDOS;
	}
	
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
 * través del nombre en caso de que ocurra un error o no */



/*status_t procesamiento_bin (struct instruccion ** memoria, struct parametros * params) {
	
	FILE * fi;
	long * aux;
	char * buffer, * endp;
	size_t i = 0, j = 0;
	
	if (memoria == NULL || params == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	if ((fi = fopen (params -> file_input, "rb")) == NULL) 
		return ST_ERROR_LECTURA_ARCHIVO;
	
	if (!(aux = (int *) malloc (sizeof (int) * 5))) {
		fclose (fi);
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	
	while (fread (aux, sizeof (int), 5, fi) == 5) {
		memoria [j] -> instruccion = 0;
		while (memoria [j] -> instruccion < MAX_INSTRUCCION) {
			memoria [j] -> instruccion *= 10;
			memoria [j] -> instruccion += aux [++i];
			
	
	
	
	if ((buffer = (char *) malloc (sizeof (char) * (LARGO_INSTRUCCION + 1))) == NULL) {
		fclose (fi);
		return ST_ERROR_MEMORIA_INVALIDA;
	}
	
	while (fread (&buffer[i], sizeof (char), LARGO_INSTRUCCION, fi) == LARGO_INSTRUCCION) {
		(*memoria)[j] -> instruccion = strtol (buffer, &endp, 10);
		
		if (*endp) {
			fclose (fi);
			free (buffer);
			buffer = NULL;
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		
		if (((*memoria)[i] -> instruccion) < 0)
			(*memoria)[i] -> operando = (((*memoria)[i] -> instruccion) * (-1)) % MAX_CANT_OPERANDOS;
		else
			(*memoria)[i] -> operando = ((*memoria)[i] -> instruccion) % MAX_CANT_OPERANDOS;
		(*memoria)[i] -> opcode = ((*memoria)[i] -> instruccion) / MAX_CANT_OPERANDOS;
		
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
}*/

/* Esta función recibe un puntero a la estructura con la informacion sobre
 * los argumentos recibidos por la línea de comandos y también un vector
 * de punteros a estructuras en donde se gurdarán las instrucciones leídas
 * por pantalla a medida de que el usuario las ingrese. Devuelve un estado
 * a través de la interfaz en caso de que ocurra un error o no */
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
		
		if (fgets (buffer, LARGO_INSTRUCCION + 2, stdin) == NULL) {
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
		if (aux < MIN_INSTRUCCION || aux > MAX_INSTRUCCION) {
			free (buffer);
			buffer = NULL;
			return ST_ERROR_INSTRUCCION_INVALIDA;
		}
		
		if(aux > MAX_INSTRUCCION || aux < MIN_INSTRUCCION)
			return ST_ERROR_INSTRUCCION_INVALIDA;
			
		memoria[i] -> instruccion = aux;
		memoria[i] -> operando = abs_t (aux) % MAX_CANT_OPERANDOS;
		memoria[i] -> opcode = aux / MAX_CANT_OPERANDOS;
	}
	
	free (buffer);
	buffer = NULL;
	
	return ST_OK;
}
