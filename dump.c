#include <stdio.h>
#include <stdlib.h>
#include "dump.h"
#include "types.h"
#include "argumentos.h"
#include "funciones.h"
#include "procesamiento.h"
#include "idioma.h"


status_t imprimir_dump (struct estado * estado, struct instruccion *** instrucciones, struct parametros * parametros) {
	FILE * f_output;
	status_t st;
	if (estado == NULL || instrucciones == NULL || parametros == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if ((parametros -> stdout_output) == TRUE)
		f_output = stdout;
	else
		if((f_output = fopen(parametros -> file_output, "w")) == NULL)
			return ST_ERROR_ARCHIVO;
	if((st = imprimir_registros (estado, f_output)) != ST_OK)
		return st;
	if((st = imprimir_memoria (instrucciones, parametros -> cantidad_de_memoria, f_output)) != ST_OK)
		return st;
	
	
	
	return ST_OK;
}

status_t imprimir_registros (struct estado * estado, FILE * f_output) {
	if (f_output == NULL || estado == NULL)
		return ST_ERROR_PUNTERO_NULO;
	fprintf(f_output, "%s:\n", MSJ_REGISTROS);
	fprintf(f_output, "%s: %ld\n", MSJ_ACUMULADOR, estado -> acc);
	fprintf(f_output, "%s: %lu\n", MSJ_CONTADOR, estado -> contador);
	fprintf(f_output, "%s: %+05d\n", MSJ_INSTRUCCION, (estado -> instruccion_actual).numero_dato);
	fprintf(f_output, "%s: %+05d\n", MSJ_OPCODE, (estado -> instruccion_actual).opcode);
	fprintf(f_output, "%s: %02lu\n", MSJ_OPERANDO, (estado -> instruccion_actual).operando);
	return ST_OK;
}

status_t imprimir_memoria (struct instruccion *** instrucciones, long cantidad_de_memoria, FILE * f_output) {
	size_t i;
	if (instrucciones == NULL || f_output == NULL)
		return ST_ERROR_PUNTERO_NULO;
	for (i = 0; i < 10 && i < cantidad_de_memoria; i++)
		fprintf(f_output, "      %lu", i);
	fputc('\n', f_output);
	for (i = 0; i < cantidad_de_memoria; i++) {
		if (!(i % 10)) {
			fputc('\n', f_output);
			fprintf(f_output, "%2lu  ", i);
		}
		fprintf(f_output, "%+5d  ", (*instrucciones)[i] -> numero_dato);
	}
	return ST_OK;
}
