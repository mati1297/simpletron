#ifndef TYPES__H
#define TYPES__H 1

#include <stdio.h>

#define MAX_STR 30
#define MAX_CADENA 100

typedef enum {
	FALSE,
	TRUE
} bool_t;

typedef enum {
	ST_OK,
	ST_ERROR_PUNTERO_NULO,
	ST_ERROR_CANTIDAD_ARGUMENTOS,
	ST_ERROR_MEMORIA_INVALIDA,
	ST_ERROR_ENTRADA_INVALIDA,
	ST_ERROR_FILE_INPUT_DEMASIADO_LARGO,
	ST_ERROR_BIN_INPUT_INCORRECTO,
	ST_ERROR_FILE_OUTPUT_DEMASIADO_LARGO,
	ST_ERROR_BIN_OUTPUT_INCORRECTO,
	ST_ERROR_ARGUMENTO_INVALIDO,
	ST_ERROR_INSTRUCCION_INVALIDA,
	ST_ERROR_DIMENSION,
	ST_ERROR_OPCODE_INVALIDO,
	ST_ERROR_LECTURA_ARCHIVO,
	ST_HELP
} status_t;

typedef enum {
	LEER = 10,
	ESCRIBIR = 11,
	CARGAR = 20,
	GUARDAR = 21,
	PCARGAR = 22,
	PGUARDAR = 23,
	SUMAR = 30,
	RESTAR = 31,
	DIVIDIR = 32,
	MULTIPLICAR = 33,
	JMP = 40,
	JMPNEG = 41,
	JMPZERO = 42,
	JNZ = 43,
	DJNZ = 44,
	HALT = 45
} opcode_t;

struct instruccion {
	int numero_dato;
	opcode_t opcode;
	size_t operando;
};

#endif
