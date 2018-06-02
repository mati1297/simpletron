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

/* Recibe por puntero la estructura simpletron, y recibe ademas los parametros
 * ingresados por linea de comandos al comienzo de la ejecucion del programa
 * que sean necesarios. En base a esta informacion abre el archivo de la 
 * manera necesaria y decide como debe imprimir la informacion de la ejecucion 
 * del simpletron. Devuelve por el nombre un estado en caso de fallar o de que
 * todo haya salido bien */
status_t imprimir_dump (struct simpletron * simpletron, bool_t bin_output, bool_t stdout_output, size_t cantidad_de_memoria, char * file_output) {
	FILE * f_output;
	status_t st;
	if (simpletron == NULL) {
		return ST_ERROR_PUNTERO_NULO;
	}
	if (bin_output == TRUE) {
		if((f_output = fopen(file_output, "wb")) == NULL) {
			return ST_ERROR_LECTURA_ARCHIVO;
		}
		if ((st = imprimir_bin(simpletron, f_output, cantidad_de_memoria)) != ST_OK) {
			fclose (f_output);
			return st;
		}
	}
	
	else {
		if ((stdout_output) == TRUE)
			f_output = stdout;
		else {
			if((f_output = fopen(file_output, "w")) == NULL) {
				return ST_ERROR_LECTURA_ARCHIVO;
			}
		}
		if((st = imprimir_registros (simpletron, f_output)) != ST_OK) {
			fclose (f_output);
			return st;
		}
		if((st = imprimir_memoria (simpletron, cantidad_de_memoria, f_output)) != ST_OK) {
			fclose (f_output);
			return st;
		}
	}
	
	fclose (f_output);
	
	return ST_OK;
}

/*Recibe un puntero a la estructura simpletron y otro al archivo de salida.
 * Imprime en formato texto la parte de los registros de la ejecucion 
 * del simpletron. Devuelve estado por el nombre.*/
status_t imprimir_registros (struct simpletron * simpletron, FILE * f_output) {
	if (simpletron == NULL || f_output == NULL)
		return ST_ERROR_PUNTERO_NULO;
	fprintf(f_output, "\n%s:\n", MSJ_REGISTROS);
	fprintf(f_output, "%s: %ld\n", MSJ_ACUMULADOR, simpletron -> acc);
	fprintf(f_output, "%s: %lu\n", MSJ_CONTADOR, simpletron -> contador);
	fprintf(f_output, "%s: %+05d\n", MSJ_INSTRUCCION, simpletron -> instruccion_actual.instruccion);
	fprintf(f_output, "%s: %+02d\n", MSJ_OPCODE, simpletron -> instruccion_actual.opcode);
	fprintf(f_output, "%s: %02lu\n", MSJ_OPERANDO, simpletron -> instruccion_actual.operando);
	return ST_OK;
}

/*Recibe un puntero a la estructura simpletron, la cantidad de memoria del programa y 
 * un puntero al archivo de salida. Imprime en formato texto los datos cargados 
 * en memoria al final de la ejecucion del simpletron en forma de tabla. 
 * Devuelve el estado por el nombre*/
status_t imprimir_memoria (struct simpletron * simpletron, long cantidad_de_memoria, FILE * f_output) {
	size_t i;
	if (simpletron == NULL || f_output == NULL)
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
		fprintf(f_output, "%+05d  ", simpletron -> memoria[i] -> instruccion);
	}
	fputc('\n', f_output);
	return ST_OK;
}

/*Recibe por puntero la estructura simpletron, el archivo de salida y la
 * cantidad de memoria. Imprime en binario tanto los registros como los
 * datos guardados en memoria al final de la ejecucion del simpletron.
 * Imprime los datos en el siguiente orden: acumulador, contador, instruccion actual: instruccion,
 * opcode, operando; y finalmente las posiciones de memoria. Devuelve
 * estado por el nombre*/
status_t imprimir_bin (struct simpletron * simpletron, FILE * f_output, long cantidad_de_memoria) {
	size_t i;
	if (simpletron == NULL || f_output == NULL)
		return ST_ERROR_PUNTERO_NULO;
	fwrite(&(simpletron -> acc), sizeof(long), 1, f_output);
	fwrite(&(simpletron -> contador), sizeof(size_t), 1, f_output);
	fwrite(&((simpletron -> instruccion_actual).instruccion), sizeof(int), 1, f_output);
	fwrite(&((simpletron -> instruccion_actual).opcode), sizeof(int), 1, f_output);
	fwrite(&((simpletron -> instruccion_actual).operando), sizeof(size_t), 1, f_output);
	for (i = 0; i < cantidad_de_memoria; i++)
		fwrite(&(simpletron -> memoria[i] -> instruccion), sizeof(int), 1, f_output);
	return ST_OK;
}
