#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentos.h"

/* Recibe la estructura de los parámetros por puntero para no tener que
 * copiarla en memoria y carga los parámetros ingresados por el usuario
 * y en caso no se haya ingresado algun argumento quedará el valor
 * predeterminado. Devuelve el estado por la interfaz para informar de
 * haber algún error */
status_t cargar_argumentos_por_omision (struct parametros * argv)
{
	if (argv == NULL)
		return ST_ERROR_PUNTERO_NULO;
	argv -> memoria = MEMORIA_POR_OMISION;
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
status_t procesar_argumentos (const char * vec_argv [], struct parametros * argv, int argc)
{
	size_t i, j;
	long aux;
	char *endp;
	static char * arg_validos[] = {TXT_ARG_MEMORIA, TXT_ARG_FILE_INPUT, TXT_ARG_BIN_INPUT, TXT_ARG_FILE_OUTPUT, TXT_ARG_BIN_OUTPUT, TXT_ARG_HELP};
	status_t st;
	
	/* Se valida que los punteros recibidos no sean nulos, que los argumentos
	 * ingresados por el usuario no sean más de los debidos y que la función
	 * cargar_argumentos_por_omision haya funcionado correctamente */
	if (argv == NULL || vec_argv == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (argc > MAX_ARGUMENTOS)
		return ST_ERROR_CANTIDAD_ARGUMENTOS;
	if (cargar_argumentos_por_omision(argv) != ST_OK)
		return st;
		
	/* Se empieza en 1 para no validar la ejecución del programa */
	for (i = 1; i < argc; i++)
	{
		for (j = 0; j < CANT_PARAMETROS; j++) /*cambio ARG_INVALIDO por CANT_PARAMETROS, no se puede usar un tipo enum como una macro*/
		
			/* Si las cadenas son iguales se procede al switch, de otra forma se sigue iterando */
			if(!strcmp(vec_argv[i], arg_validos[j]))
				break;
		
		switch (j)
		{
			case ARG_MEMORIA:
				i++;
				argv -> memoria = strtol (vec_argv[i], &endp, 10);
				if (*endp)
					return ST_ERROR_CARACTER_INCORRECTO_MEMORIA;
				if (argv -> memoria <= 0)
					return ST_ERROR_MEMORIA_INVALIDA;
				break;
				
			case ARG_FILE_INPUT: /*VALIDAR CARACTERES INVALIDOS??*/
				i++;
				if ((aux = strlen(vec_argv[i])) > (MAX_STR - 1))
					/*fprintf (stderr, blablabla...);*/
					return ST_ERROR_FILE_INPUT_DEMASIADO_LARGO; /*en realidad no es un error. deberiamos decirle al usuario que cambie el nombre o algo asi*/
				if (vec_argv[i][aux - 1] == EXTENSION[2] && vec_argv[i][aux - 2] == EXTENSION[1] && vec_argv[i][aux - 3] == EXTENSION[0] && vec_argv[i][aux - 4] == '.')
				
				/* wat?
				 * no entendi el renglon de arriba */
				 
				 /*si estas usando EXTENSION como un char * lo cambiaria y pondria un char * y le asignamos el string con la macro pero asi no creo que este bien*/
				
				{
					strcpy(argv -> file_input, vec_argv[i]);
					argv -> stdin_input = FALSE;
				}
				else
					return ST_ERROR_INPUT_EXTENSION_MAL;
				break;
					
			case ARG_BIN_INPUT:
				i++;
				if (!strcmp(vec_argv[i], TXT_INDICADOR_TEXTO))
					/*break*/;											/* ? */
				else if (!strcmp(vec_argv[i], TXT_INDICADOR_BINARIO))
					argv -> bin_input = TRUE;
				else
					return ST_ERROR_BIN_INPUT_MAL;
				break;
				
				/* ALTERNATIVA
				i++;
				if (!strcmp(vec_argv[i], TXT_INDICADOR_BINARIO))
					argv -> bin_input = TRUE;
				else if (strcmp (vec_argv[i], TXT_INDICADOR_TEXTO))
					return ST_ERROR_BIN_INPUT_MAL;
				break;
				*/
				
			case ARG_FILE_OUTPUT: /*VERIFICAR CARACTERES INVALIDOS??*/
				i++;
				if ((aux = strlen(vec_argv[i])) > (MAX_STR - 1))
					return ST_ERROR_FILE_OUTPUT_DEMASIADO_LARGO;	/*idem FILE_INPUT*/
				if (vec_argv[i][aux - 1] == EXTENSION[2] && vec_argv[i][aux - 2] == EXTENSION[1] && vec_argv[i][aux - 3] == EXTENSION[0] && vec_argv[i][aux - 4] == '.')
				
				/*idem*/
				
				{
					strcpy(argv -> file_output, vec_argv[i]);
					argv -> stdout_output = FALSE;
				}
				else
					return ST_ERROR_OUTPUT_EXTENSION_MAL;
				break;
					
			case ARG_BIN_OUTPUT:
				i++;
				if (!strcmp(vec_argv[i], TXT_INDICADOR_TEXTO))
					/*break*/;
				else if (!strcmp(vec_argv[i], TXT_INDICADOR_BINARIO))
					argv -> bin_output = TRUE;
				else
					return ST_ERROR_BIN_OUTPUT_MAL;
				break;
				
				/*misma alternativa*/
				
			case ARG_HELP:
				return ST_HELP; /*saco el break*/
				
			default:
				return ST_ERROR_ARGUMENTOS_INVALIDOS;
		}
	}
	return ST_OK;
}
