#ifndef SIMPLETRON__H 
#define SIMPLETRON__H 1

#include <stdio.h>

typedef enum {
	OP_LEER = 10,
	OP_ESCRIBIR = 11,
	OP_CARGAR = 20,
	OP_GUARDAR = 21,
	OP_PCARGAR = 22,
	OP_PGUARDAR = 23,
	OP_SUMAR = 30,
	OP_RESTAR = 31,
	OP_DIVIDIR = 32,
	OP_MULTIPLICAR = 33,
	OP_JMP = 40,
	OP_JMPNEG = 41,
	OP_JMPZERO = 42,
	OP_JNZ = 43,
	OP_DJNZ = 44,
	OP_HALT = 45
} opcode_t;

struct instruccion {
	int instruccion;
	opcode_t opcode;
	size_t operando;
};

struct estado
{
	long acc;
	size_t contador;
	struct instruccion * memoria_simpletron;
	struct instruccion instruccion_actual;
};

#endif
