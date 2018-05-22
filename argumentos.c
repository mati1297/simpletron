#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentos.h"
#include "types.h"
#include "error.h"
#include "herramientas.h"

/* Recibe la estructura de los parámetros por puntero y carga los
 * parámetros ingresados por el usuario. En caso no se haya ingresado
 * algún argumento quedará el valor predeterminado. Devuelve el estado
 * por la interfaz para informar de haber algún error */
status_t cargar_argumentos_por_omision (struct parametros * argv) {
	
	if (argv == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	argv -> cantidad_de_memoria = MEMORIA_POR_OMISION;
	argv -> stdin_input = TRUE;
	argv -> bin_input = FALSE;
	argv -> stdout_output = TRUE;
	argv -> bin_output = FALSE;
	
	return ST_OK;
}


/* Recibe los argumentos ingresados por el usuario en el vector de punteros
 * vec_argv, un puntero a la estructura de parámetros donde se van a guardar
 * los parámetros ingresados por el usuario, y la cantidad de parámetros
 * ingresados para las validaciones y ciclos. Devuelve el estado por la
 * interfaz, informando así si hay algún error */
status_t procesar_argumentos (const char * vec_argv [], struct parametros * argv, int argc) {
	
	size_t i, j;
	char * endp;
	static char * arg_validos[] = {TXT_ARG_MEMORIA, TXT_ARG_FILE_INPUT, TXT_ARG_BIN_INPUT, TXT_ARG_FILE_OUTPUT, TXT_ARG_BIN_OUTPUT, TXT_ARG_HELP};
	status_t st;
	
	/* Se valida que los punteros recibidos no sean nulos, que los argumentos
	 * ingresados por el usuario no sean más de los debidos y que la función
	 * cargar_argumentos_por_omision haya funcionado correctamente */
	if (argv == NULL || vec_argv == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	if (argc > MAX_ARGUMENTOS)
		return ST_ERROR_CANTIDAD_ARGUMENTOS;
		
	if ((st = cargar_argumentos_por_omision(argv)) != ST_OK)
		return st;
	
		
	/* Se empieza en 1 para no validar la ejecución del programa */
	for (i = 1; i < argc; i++) {
	
		for (j = 0; j < ARG_INVALIDO; j++)
		
			/* Si las cadenas son iguales se procede al switch, de otra forma se sigue iterando */
			if(!strcmp(vec_argv[i], arg_validos[j]))
				break;
		
		switch (j) {
			
			/* Se guarda la cantidad de instrucciones a interpretar */
			case ARG_MEMORIA:
				i++;
				argv -> cantidad_de_memoria = strtol (vec_argv[i], &endp, 10);
				if (*endp) 
					return ST_ERROR_ARGUMENTO_INVALIDO;

				if (argv -> cantidad_de_memoria <= 0)
					return ST_ERROR_ARGUMENTO_INVALIDO;

				break;
			
			/* Se guarda el nombre del archivo de entrada */
			case ARG_FILE_INPUT:
				i++;
				if (strlen(vec_argv[i]) > (MAX_STR - 1)) 
					return ST_ERROR_FILE_INPUT_DEMASIADO_LARGO;
				
				strcpy(argv -> file_input, vec_argv[i]);
				argv -> stdin_input = FALSE;
				break;
			
			/* Indica que el archivo de entrada es en formato binario */
			case ARG_BIN_INPUT:
				i++;
				if (!strcmp(vec_argv[i], TXT_INDICADOR_BINARIO))
					argv -> bin_input = TRUE;
				else if (strcmp (vec_argv[i], TXT_INDICADOR_TEXTO))
					return ST_ERROR_ARGUMENTO_INVALIDO;
				break;
				
			/* Se guarda el nombre del archivo de salida */
			case ARG_FILE_OUTPUT:
				i++;
				if (strlen(vec_argv[i]) > (MAX_STR - 1))
					return ST_ERROR_FILE_OUTPUT_DEMASIADO_LARGO;
					
				strcpy(argv -> file_output, vec_argv[i]);
				argv -> stdout_output = FALSE;
				break;
				
			/* Indica que el archivo de salida es en formato binario */
			case ARG_BIN_OUTPUT:
				i++;
				if (!strcmp(vec_argv[i], TXT_INDICADOR_BINARIO))
					argv -> bin_output = TRUE;
					
				else if (strcmp (vec_argv[i], TXT_INDICADOR_TEXTO)) 
					return ST_ERROR_ARGUMENTO_INVALIDO;
					
				break;
				
			/* Llama a la función de impresión de la ayuda */
			case ARG_HELP:
				if ((st = imprimir_ayuda ()) != ST_OK)
					return st;
				return ST_HELP;
				break;
			default:
				return ST_ERROR_ARGUMENTO_INVALIDO;
		}
	}
	
	if (argv -> stdin_input == TRUE && argv -> bin_input == TRUE)
		return ST_ERROR_ARGUMENTO_INVALIDO;

	if (argv -> stdout_output == TRUE && argv -> bin_output == TRUE)
		return ST_ERROR_ARGUMENTO_INVALIDO;
		
	return ST_OK;
}
