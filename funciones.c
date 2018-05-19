#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "types.h"
#include "idioma.h"
#include "procesamiento.h"
#include "error.h"

status_t seleccion_de_funcion (struct instruccion *** instrucciones, long cantidad_de_memoria, struct estado * estado) {
	status_t st;
	size_t i;
	if (instrucciones == NULL || estado == NULL) {
		imprimir_error(ST_ERROR_PUNTERO_NULO);
		return ST_ERROR_PUNTERO_NULO;
	}
	
	for (i = 0, estado -> contador = 0; i < cantidad_de_memoria; ) {
		
		
		/*Se cargan los nuevos datos al estado*/
		estado -> instruccion_actual = *(*instrucciones)[i];
		(estado -> contador)++;
		
		if((*instrucciones)[i] -> opcode == HALT) /*Lo pongo aca porque no se como hacerlo en switch*/
			break;
			
		if((*instrucciones)[i] -> operando >= cantidad_de_memoria) {
			imprimir_error(ST_ERROR_SIMPLETRON);
			return ST_ERROR_SIMPLETRON;
		}
		
		switch ((*instrucciones)[i] -> opcode) {
		case LEER:
			if((st = leer (instrucciones, (*instrucciones)[i] -> operando)) != ST_OK) {
				imprimir_error(st);
				return st;
			}
			break;
		case ESCRIBIR:
			if((st = escribir (instrucciones, (*instrucciones)[i] -> operando)) != ST_OK) {
				imprimir_error(st);
				return st;
			}
			break;
		case CARGAR:
			if((st = cargar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) {
				imprimir_error(st);
				return st;
			}
		case GUARDAR:
			if((st = guardar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) {
				imprimir_error(st);
				return st;
			}
			break;
		case PCARGAR:
			if((st = pcargar(instrucciones, cantidad_de_memoria, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) {
				imprimir_error(st);
				return st;
			}
			break;
		case PGUARDAR:
			if((st = pguardar (instrucciones, cantidad_de_memoria, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) {
				imprimir_error(st);
				return st;
			}
			break;
		case SUMAR:
			if((st = sumar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) {
				imprimir_error(st);
				return st;
			}
			break;
		case RESTAR:
			if((st = restar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) {
				imprimir_error(st);
				return st;
			}
			break;
		case DIVIDIR:
			if((st = dividir (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) {
				imprimir_error(st);
				return st;
			}
			break;
		case MULTIPLICAR:
			if((st = multiplicar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) {
				imprimir_error(st);
				return st;
			}
		case JMP:
			if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK) {
				imprimir_error(st);
				return st;
			}
			break;
		case JMPNEG:
			if ((estado -> acc) < 0)
				if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK) {
					imprimir_error(st);
					return st;
				}
			break;
		case JMPZERO:
			if (!(estado -> acc))
				if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK) {
					imprimir_error(st);
					return st;
				}
			break;
		case JNZ:
			if ((estado -> acc))
				if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK) {
					imprimir_error(st);
					return st;
				}
			break;
		case DJNZ:
			if (--(estado -> acc))
				if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK) {
					imprimir_error(st);
					return st;
				}
			break;
		default:
			imprimir_error(ST_ERROR_SIMPLETRON);
			return ST_ERROR_SIMPLETRON;
		}
	}
	
	if (i >= cantidad_de_memoria) {
		imprimir_error(ST_ERROR_SIMPLETRON);
		return ST_ERROR_SIMPLETRON;
	}
		
	return ST_OK;
}

status_t leer (struct instruccion *** instrucciones, size_t operando) {
	char cadena_aux [LARGO_INSTRUCCION + 2], *endp;
	int numero_aux;
	fprintf(stdout, "%s: ", MSJ_INGRESO_PALABRA);
	if (instrucciones == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (fgets(cadena_aux, LARGO_INSTRUCCION + 2, stdin) == NULL)
		return ST_ERROR_ENTRADA_INVALIDA;
	numero_aux = strtol(cadena_aux, &endp, 10);
	if (*endp != '\n' && *endp)
		return ST_ERROR_SIMPLETRON;
	if (numero_aux > MAX_MODULO || numero_aux < -MAX_MODULO)
		return ST_ERROR_SIMPLETRON;
	(*instrucciones)[operando] -> numero_dato = numero_aux;
	(*instrucciones)[operando] -> opcode = (*instrucciones)[operando] -> numero_dato / MAX_CANT_OPERANDOS;
	(*instrucciones)[operando] -> operando = (*instrucciones)[operando] -> numero_dato % MAX_CANT_OPERANDOS;
	return ST_OK;
}

status_t escribir (struct instruccion *** instrucciones, size_t operando) {
	fprintf(stdout, "%s %lu: ", MSJ_CONTENIDO_POSICION, operando);
	if (instrucciones == NULL)
		return ST_ERROR_PUNTERO_NULO;
	fprintf(stdout, "%d", (*instrucciones)[operando] -> numero_dato);
	return ST_OK;
}

status_t cargar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	*acc = (*instrucciones)[operando] -> numero_dato;
	return ST_OK;
}

status_t guardar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	int aux;
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	aux = *acc;
	if (aux > MAX_MODULO || aux < -MAX_MODULO)
		return ST_ERROR_SIMPLETRON;
	(*instrucciones)[operando] -> numero_dato =  aux;
	(*instrucciones)[operando] -> opcode = (*instrucciones)[operando] -> numero_dato / MAX_CANT_OPERANDOS;
	(*instrucciones)[operando] -> operando = (*instrucciones)[operando] -> numero_dato % MAX_CANT_OPERANDOS;
	return ST_OK;
}


/*FALTA PCARGAR Y PGUARDAR*/

status_t sumar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	(*acc) += (*instrucciones)[operando] -> numero_dato;
	return ST_OK;
}

status_t restar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	(*acc) -= (*instrucciones)[operando] -> numero_dato;
	return ST_OK;
}

status_t dividir (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	(*acc) /= (*instrucciones)[operando] -> numero_dato;
	return ST_OK;
}

status_t multiplicar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	(*acc) *= (*instrucciones)[operando] -> numero_dato;
	return ST_OK;
}

status_t jmp (struct instruccion *** instrucciones, size_t operando, size_t * i) {
	if (instrucciones == NULL)
		return ST_ERROR_PUNTERO_NULO;
	*i = operando - 1; /*Se le resta 1 para que cuando sume el ciclo, quede en la operandoicion correcta*/
	return ST_OK;
}

status_t pcargar (struct instruccion *** instrucciones, long cantidad_de_memoria, size_t operando, long * acc) {
	int aux;
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if ((aux = (*instrucciones)[operando] -> numero_dato) >= cantidad_de_memoria)
		return ST_ERROR_SIMPLETRON;
	*acc = (*instrucciones)[aux] -> numero_dato;
	return ST_OK;
}

status_t pguardar (struct instruccion *** instrucciones, long cantidad_de_memoria, size_t operando, long * acc) {
	int aux;
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if ((aux = (*instrucciones)[operando] -> numero_dato) >= cantidad_de_memoria)
		return ST_ERROR_SIMPLETRON;
	if (*acc > MAX_MODULO || *acc < -MAX_MODULO)
		return ST_ERROR_SIMPLETRON;
	(*instrucciones)[aux] -> numero_dato = *acc;
	(*instrucciones)[aux] -> opcode = (*instrucciones)[aux] -> numero_dato / MAX_CANT_OPERANDOS;
	(*instrucciones)[aux] -> operando = (*instrucciones)[aux] -> numero_dato % MAX_CANT_OPERANDOS;
	return ST_OK;
}
