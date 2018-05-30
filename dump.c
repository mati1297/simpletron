#include <stdio.h>
#include <stdlib.h>
#include "dump.h"
#include "types.h"
#include "argumentos.h"
#include "funciones.h"
#include "procesamiento.h"
#include "idioma.h"
#include "error.h"
#include "simpletron.h"
#include "main.h"

/* Recibe por puntero las estructuras conteniendo los datos sobre el estado
 * de Simpletron, sobre las instrucciones que corrieron en el programa y
 * sobre los parámetros ingresados por la línea de comandos. En base de la
 * información leída por la línea de comandos se imprime el estado final de
 * Simpletron en el formato deseado. Devuelve por la interfaz un estado en
 * caso de fallar o de que todo haya salido bien */
status_t imprimir_dump (struct estado * estado, struct instruccion *** instrucciones, struct parametros * parametros) {
	FILE * f_output;
	status_t st;
	if (estado == NULL || instrucciones == NULL || parametros == NULL) {
		return ST_ERROR_PUNTERO_NULO;
	}
	if (parametros -> bin_output == TRUE) {
		if((f_output = fopen(parametros -> file_output, "wb")) == NULL) {
			return ST_ERROR_LECTURA_ARCHIVO;
		}
		if ((st = imprimir_bin(estado, f_output, instrucciones, parametros -> cantidad_de_memoria)) != ST_OK) {
			fclose (f_output);
			return st;
		}
	}
	
	else {
		if ((parametros -> stdout_output) == TRUE)
			f_output = stdout;
		else {
			if((f_output = fopen(parametros -> file_output, "w")) == NULL) {
				return ST_ERROR_LECTURA_ARCHIVO;
			}
		}
		if((st = imprimir_registros (estado, f_output)) != ST_OK) {
			fclose (f_output);
			return st;
		}
		if((st = imprimir_memoria (instrucciones, parametros -> cantidad_de_memoria, f_output)) != ST_OK) {
			fclose (f_output);
			return st;
		}
	}
	
	fclose (f_output);
	
	return ST_OK;
}

/* Recibe un puntero a la estructura estado actual de Simpletron y otro
 * a la estructura con la información del archivo de salida. Imprime el
 * estado en el archivo y en caso de recibir un puntero nulo devuelve un 
 * estado por la interfaz informándolo */
status_t imprimir_registros (struct estado * estado, FILE * f_output) {
	if (f_output == NULL || estado == NULL)
		return ST_ERROR_PUNTERO_NULO;
	fprintf(f_output, "\n%s:\n", MSJ_REGISTROS);
	fprintf(f_output, "%s: %ld\n", MSJ_ACUMULADOR, estado -> acc);
	fprintf(f_output, "%s: %lu\n", MSJ_CONTADOR, estado -> contador);
	fprintf(f_output, "%s: %+05d\n", MSJ_INSTRUCCION, (estado -> instruccion_actual).numero_dato);
	fprintf(f_output, "%s: %+02d\n", MSJ_OPCODE, (estado -> instruccion_actual).opcode);
	fprintf(f_output, "%s: %02lu\n", MSJ_OPERANDO, (estado -> instruccion_actual).operando);
	return ST_OK;
}

/* Recibe un puntero a el vector de punteros a estructuras con la información
 * de cada instrucción, la cantidad de memoria pedida por el usuario un puntero
 * a la estructura con información del archivo de salida. Hace una impresión
 * de el estado final de la memoria de Simpletron en stdout o en el archivo
 * de texto indicado. En caso de fallar o que todo ande en orden devuelve
 * un estado por la interfaz */
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

/* Recibe por puntero la estructura con el estado de Simpletron, la información
 * del archivo de salida y las instrucciones cargadas en memoria y la cantidad
 * de memoria pedida por el usuario. La función imprime en el archivo indicado
 * el dump y el estado final de la memoria, en formato binario. En caso de
 * haber un error o de que esté todo en orden, devuelve un estado a través
 * de la interfaz */
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
