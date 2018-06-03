
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "argumentos.h"
#include "types.h"
#include "error.h"
#include "herramientas.h"


/* Recibe la estructura de los parámetros por puntero y carga los
 * parámetros ingresados por el usuario. En caso no se haya ingresado
 * algún argumento quedará el valor predeterminado. Devuelve el estado
 * por el nombre para informar de haber algún error */
status_t cargar_argumentos_por_omision (struct parametros * params) {
	
	if (params == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	params -> cantidad_de_memoria = MEMORIA_POR_OMISION;
	params -> stdin_input = TRUE;
	params -> bin_input = FALSE;
	params -> stdout_output = TRUE;
	params -> bin_output = FALSE;
	
	return ST_OK;
}


/* Recibe los argumentos ingresados por el usuario en el vector de punteros
 * argv, un puntero a la estructura de parámetros donde se van a guardar
 * los parámetros ingresados por el usuario, y la cantidad de parámetros
 * ingresados para las validaciones y ciclos. Devuelve el estado por el
 * nombre, informando así si hay algún error */
status_t procesar_argumentos (const char * argv [], struct parametros * params, int argc) {
	
	size_t i, j;
	char * endp;
	const char * arg_validos[] = {TXT_ARG_MEMORIA, TXT_ARG_FILE_INPUT, TXT_ARG_BIN_INPUT, TXT_ARG_FILE_OUTPUT, TXT_ARG_BIN_OUTPUT, TXT_ARG_HELP};
	status_t st;
	
	/* Se valida que los punteros recibidos no sean nulos, que los argumentos
	 * ingresados por el usuario no sean más de los debidos y que la función
	 * cargar_argumentos_por_omision haya funcionado correctamente */
	if (params == NULL || argv == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	if (argc > MAX_ARGUMENTOS)
		return ST_ERROR_CANTIDAD_ARGUMENTOS;
		
	if ((st = cargar_argumentos_por_omision(params)) != ST_OK)
		return st;
	
		
	/* Se empieza en 1 para omitir el argumento que contiene la linea de ejecucion */
	for (i = 1; i < argc; i++) {
		for (j = 0; j < ARG_INVALIDO; j++) {
			/* Si las cadenas son iguales se procede al switch, de otra forma se sigue iterando */
			if(!strcmp(argv[i], arg_validos[j]))
				break;
		}
		switch (j) {
			
			/* Se guarda la cantidad de instrucciones a interpretar */
			case ARG_MEMORIA:
				i++;
				params -> cantidad_de_memoria = strtol (argv[i], &endp, 10);
				if (*endp) 
					return ST_ERROR_ARGUMENTO_INVALIDO;

				if (params -> cantidad_de_memoria <= 0)
					return ST_ERROR_CANTIDAD_DE_MEMORIA_INVALIDA;

				break;
			
			/* Se guarda el nombre del archivo de entrada igualando punteros */
			case ARG_FILE_INPUT:
				i++;
				params -> file_input = argv[i];
				params -> stdin_input = FALSE;
				break;
			
			/* Indica que el archivo de entrada es en formato binario */
			case ARG_BIN_INPUT:
				i++;
				if (!strcmp(argv[i], TXT_INDICADOR_BINARIO))
					params -> bin_input = TRUE;
				else if (!strcmp (argv[i], TXT_INDICADOR_TEXTO))
					params -> bin_input = FALSE;
				else
					return ST_ERROR_ARGUMENTO_INVALIDO;
				break;
				
			/* Se guarda el nombre del archivo de salida igualando punteros */
			case ARG_FILE_OUTPUT:
				i++;
				params -> file_output = argv[i];
				params -> stdout_output = FALSE;
				break;
				
			/* Indica que el archivo de salida es en formato binario */
			case ARG_BIN_OUTPUT:
				i++;
				if (!strcmp(argv[i], TXT_INDICADOR_BINARIO))
					params -> bin_output = TRUE;
					
				else if (strcmp (argv[i], TXT_INDICADOR_TEXTO)) 
					return ST_ERROR_ARGUMENTO_INVALIDO;
					
				break;
				
			/* Llama a la función de impresión de la ayuda */
			case ARG_HELP:
				return ST_HELP;
				break;
			default:
				return ST_ERROR_ARGUMENTO_INVALIDO;
		}
	}
	
	if (params -> stdin_input == TRUE && params -> bin_input == TRUE)
		return ST_ERROR_ARGUMENTO_INVALIDO;

	if (params -> stdout_output == TRUE && params -> bin_output == TRUE)
		return ST_ERROR_ARGUMENTO_INVALIDO;
		
	return ST_OK;
}
