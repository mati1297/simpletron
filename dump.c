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
	if (estado == NULL || instrucciones == NULL || parametros == NULL) {
		imprimir_error(ST_ERROR_PUNTERO_NULO);
		return ST_ERROR_PUNTERO_NULO;
	}
	if (parametros -> bin_output == TRUE) {
		if((f_output = fopen(parametros -> file_output, "wb")) == NULL) {
			imprimir_error(ST_ERROR_LECTURA_ARCHIVO);
			return ST_ERROR_LECTURA_ARCHIVO;
		}
		if ((st = imprimir_bin(estado, f_output, instrucciones, parametros -> cantidad_de_memoria)) != ST_OK) {
			imprimir_error(st);
			return st;
		}
	}
	
	else {
		if ((parametros -> stdout_output) == TRUE)
			f_output = stdout;
		else {
			if((f_output = fopen(parametros -> file_output, "w")) == NULL) {
				imprimir_error(ST_ERROR_LECTURA_ARCHIVO);
				return ST_ERROR_LECTURA_ARCHIVO;
			}
		}
		if((st = imprimir_registros (estado, f_output)) != ST_OK) {
			imprimir_error (st);
			return st;
		}
		if((st = imprimir_memoria (instrucciones, parametros -> cantidad_de_memoria, f_output)) != ST_OK) {
			imprimir_error (st);
			return st;
		}
	}
	
	return ST_OK;
}

status_t imprimir_registros (struct estado * estado, FILE * f_output) {
	if (f_output == NULL || estado == NULL)
		return ST_ERROR_PUNTERO_NULO;
	fprintf(f_output, "%s:\n", MSJ_REGISTROS);
	fprintf(f_output, "%s: %ld\n", MSJ_ACUMULADOR, estado -> acc);
	fprintf(f_output, "%s: %lu\n", MSJ_CONTADOR, estado -> contador);
	fprintf(f_output, "%s: %+05d\n", MSJ_INSTRUCCION, (estado -> instruccion_actual).numero_dato);
	fprintf(f_output, "%s: %+02d\n", MSJ_OPCODE, (estado -> instruccion_actual).opcode);
	fprintf(f_output, "%s: %02lu\n", MSJ_OPERANDO, (estado -> instruccion_actual).operando);
	return ST_OK;
}

status_t imprimir_memoria (struct instruccion *** instrucciones, long cantidad_de_memoria, FILE * f_output) {
	size_t i;
	if (instrucciones == NULL || f_output == NULL)
		return ST_ERROR_PUNTERO_NULO;
	fprintf(f_output, "\n%s:\n", MSJ_MEMORIA);
	for (i = 0; i < COLUMNAS && i < cantidad_de_memoria; i++)
		fprintf(f_output, "      %lu", i);
	fputc('\n', f_output);
	for (i = 0; i < cantidad_de_memoria; i++) {
		if (!(i % COLUMNAS)) {
			fputc('\n', f_output);
			fprintf(f_output, "%2lu  ", i);
		}
		fprintf(f_output, "%+05d  ", (*instrucciones)[i] -> numero_dato);
	}
	fputc('\n', f_output);
	return ST_OK;
}

status_t imprimir_bin (struct estado * estado, FILE * f_output, struct instruccion *** instrucciones, long cantidad_de_memoria) {
	size_t i;
	if (estado == NULL || f_output == NULL || instrucciones == NULL)
		return ST_ERROR_PUNTERO_NULO;
	fwrite(&(estado -> acc), sizeof(long), 1, f_output);
	fwrite(&(estado -> contador), sizeof(size_t), 1, f_output);
	fwrite(&((estado -> instruccion_actual).numero_dato), sizeof(int), 1, f_output);
	fwrite(&((estado -> instruccion_actual).opcode), sizeof(int), 1, f_output);
	fwrite(&((estado -> instruccion_actual).operando), sizeof(size_t), 1, f_output);
	for (i = 0; i < cantidad_de_memoria; i++)
		fwrite(&((*instrucciones)[i] -> numero_dato), sizeof(int), 1, f_output);
	return ST_OK;
}
