#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentos.h"

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

status_t procesar_argumentos (const char ** vec_argv, struct parametros * argv, int argc)
{
	size_t i, j;
	long aux;
	char *endp;
	static char * arg_validos[] = {TXT_ARG_MEMORIA, TXT_ARG_FILE_INPUT, TXT_ARG_BIN_INPUT, TXT_ARG_FILE_OUTPUT, TXT_ARG_BIN_OUTPUT, TXT_ARG_HELP};
	if (argv == NULL || vec_argv == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (argc > MAX_ARGUMENTOS)
		return ST_ERROR_CANTIDAD_ARGUMENTOS;
	if (cargar_argumentos_por_omision(argv) == ST_ERROR_PUNTERO_NULO)
		return ST_ERROR_PUNTERO_NULO;
	for (i = 1; i < argc; i++)
	{
		for (j = 0; j < ARG_INVALIDO; j++)
		{
			if(!strcmp(vec_argv[i], arg_validos[j]))
				break;
		}
		switch (j)
		{
			case ARG_MEMORIA:
				i++;
				if ((argv -> memoria = strtol (vec_argv[i], &endp, 10)) <= 0)
					return ST_ERROR_MEMORIA_INVALIDA;
				if (*endp != '\0')
					return ST_ERROR_CARACTER_INCORRECTO_MEMORIA;
				break;
				
			case ARG_FILE_INPUT: /*VALIDAR CARACTERES INVALIDOS??*/
				i++;
				if ((aux = strlen(vec_argv[i])) > (MAX_STR - 1))
					return ST_ERROR_FILE_INPUT_DEMASIADO_LARGO;
				if (vec_argv[i][aux - 1] == EXTENSION[2] && vec_argv[i][aux - 2] == EXTENSION[1] && vec_argv[i][aux - 3] == EXTENSION[0] && vec_argv[i][aux - 4] == '.')
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
					;
				else if (!strcmp(vec_argv[i], TXT_INDICADOR_BINARIO))
					argv -> bin_input = TRUE;
				else
					return ST_ERROR_BIN_INPUT_MAL;
				break;
			case ARG_FILE_OUTPUT: /*VERIFICAR CARACTERES INVALIDOS??*/
				i++;
				if ((aux = strlen(vec_argv[i])) > (MAX_STR - 1))
					return ST_ERROR_FILE_OUTPUT_DEMASIADO_LARGO;
				if (vec_argv[i][aux - 1] == EXTENSION[2] && vec_argv[i][aux - 2] == EXTENSION[1] && vec_argv[i][aux - 3] == EXTENSION[0] && vec_argv[i][aux - 4] == '.')
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
					;
				else if (!strcmp(vec_argv[i], TXT_INDICADOR_BINARIO))
					argv -> bin_output = TRUE;
				else
					return ST_ERROR_BIN_OUTPUT_MAL;
				break;
					
			case ARG_HELP:
				return ST_HELP;
				break;
				
			default:
				return ST_ERROR_ARGUMENTOS_INVALIDOS;
		}
	}
	return ST_OK;
}
