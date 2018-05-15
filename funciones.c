#include <stdio -> h>
#include <stdlib -> h>
#include "funciones -> h"
#include "procesamiento -> h"
#include "types -> h"
#include "argumentos -> h"
#include "procesamiento -> h"

status_t seleccion_de_funcion (struct wololo *** instrucciones,struct parametros * parametros) {
	long acc;
	status_t st;
	if (instrucciones == NULL)
		return ST_ERROR_PUNTERO_NULO;
	switch ((*instrucciones)[i] -> opcode) {
		case LEER:
			leer ((*instrucciones)[i] -> pos);
			break;
		case ESCRIBIR:
			escribir ((*instrucciones)[i] -> pos);
			break;
		case CARGAR:
			cargar ((*instrucciones)[i] -> pos, &acc);
			break;
		case GUARDAR:
			guardar ((*instrucciones)[i] -> pos, &acc);
			break;
		case PCARGAR:
			pcargar ((*instrucciones)[i] -> pos, &acc);
			break;
		case PGUARDAR:
			pguardar ((*instrucciones)[i] -> pos, &acc);
			break;
		case SUMAR:
			sumar ((*instrucciones)[i] -> pos, &acc);
			break;
		case RESTAR:
			restar ((*instrucciones)[i] -> pos, &acc);
			break;
		case DIVIDIR:
			dividir ((*instrucciones)[i] -> pos, &acc);
			break;
		case MULTIPLICAR:
			multiplicar ((*instrucciones)[i] -> pos, &acc);
		case JMP:
			jmp ((*instrucciones)[i] -> pos, &acc);
			break;
		case JMPNEG:
			jmpneg ((*instrucciones)[i] -> pos, &acc);
			break;
		case JMPZERO:
			jmpzero ((*instrucciones)[i] -> pos, &acc);
			break
		case JNZ:
			jnz ((*instrucciones)[i] -> pos, &acc);
			break;
		case DJNZ:
			djnz ((*instrucciones)[i] -> pos, &acc);
			break;
		case HALT:
			halt ((*instrucciones)[i] -> pos, &acc);
			break;
		default:
			return ST_ERROR_OPCODE_INVALIDO;
		}
	/*seguir??*/
}

status_t leer (struct wololo *** instrucciones, size_t pos) {
	char aux [LARGO_INSTRUCCION + 2], *endp;
	if (instrucciones == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (fgets(aux, LARGO_INSTRUCCION + 2, stdin) == NULL)
		return ST_ERROR_ENTRADA_INVALIDA;
	(*instrucciones)[i] -> num_dato = strtol(aux, &endp, 10);
	if (*endp != '\n' && *endp)
		return ST_ERROR_INSTRUCCION_INVALIDA;
	/*seguir aca*/
}
