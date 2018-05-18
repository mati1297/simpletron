#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "procesamiento.h"
#include "types.h"
#include "argumentos.h"
#include "idioma.h"

status_t seleccion_de_funcion (struct instruccion *** instrucciones, long cantidad_de_memoria, struct estado * estado) {
	status_t st;
	size_t i;
	if (instrucciones == NULL || estado == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	for (i = 0, estado -> contador = 0; i < cantidad_de_memoria; ) {
		
		
		/*Se cargan los nuevos datos al estado*/
		estado -> instruccion_actual = *(*instrucciones)[i];
		(estado -> contador)++;
		
		if((*instrucciones)[i] -> opcode == HALT) /*Lo pongo aca porque no se como hacerlo en switch*/
			break;
		
		switch ((*instrucciones)[i] -> opcode) {
		case LEER:
			if(leer (instrucciones, (*instrucciones)[i] -> operando) != ST_OK)
				return st;
			break;
		case ESCRIBIR:
			if(escribir (instrucciones, (*instrucciones)[i] -> operando) != ST_OK)
				return st;
			break;
		case CARGAR:
			if(cargar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc)) != ST_OK)
				return st;
		case GUARDAR:
			if(guardar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc)) != ST_OK)
				return st;
			break;
		case PCARGAR:
			pcargar ((*instrucciones)[i] -> operando, &acc);
			break;
		case PGUARDAR:
			pguardar ((*instrucciones)[i] -> operando, &acc);
			break;
		case SUMAR:
			if(sumar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc)) != ST_OK)
				return st;
			break;
		case RESTAR:
			if(restar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc)) != ST_OK)
				return st;
			break;
		case DIVIDIR:
			if(dividir (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc)) != ST_OK)
				return st;
			break;
		case MULTIPLICAR:
			if(multiplicar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc)) != ST_OK)
				return st;
		case JMP:
			if(jmp (instrucciones, (*instrucciones)[i] -> operando, cantidad_de_memoria, &i) != ST_OK)
				return st;
			break;
		case JMPNEG:
			if ((estado -> acc) < 0)
				if(jmp (instrucciones, (*instrucciones)[i] -> operando, cantidad_de_memoria, &i) != ST_OK)
					return st;
			break;
		case JMPZERO:
			if (!(estado -> acc))
				if(jmp (instrucciones, (*instrucciones)[i] -> operando, cantidad_de_memoria, &i) != ST_OK)
					return st;
			break;
		case JNZ:
			if ((estado -> acc))
				if(jmp (instrucciones, (*instrucciones)[i] -> operando, cantidad_de_memoria, &i) != ST_OK)
					return st;
			break;
		case DJNZ:
			if (--(estado -> acc))
				if(jmp (instrucciones, (*instrucciones)[i] -> operando, cantidad_de_memoria, &i) != ST_OK)
					return st;
			break;
		default:
			return ST_ERROR_OPCODE_INVALIDO;
		}
	}
	
	if (i > cantidad_de_memoria)
		return ST_ERROR_POSICION_INEXISTENTE;
		
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
		return ST_ERROR_INSTRUCCION_INVALIDA;
	if (numero_aux > 9999 || numero_aux < -9999)
		return ST_ERROR_INSTRUCCION_INVALIDA;
	(*instrucciones)[operando] -> numero_dato = numero_aux;
	(*instrucciones)[operando] -> opcode = (*instrucciones)[operando] -> numero_dato / 100;
	(*instrucciones)[operando] -> operando = (*instrucciones)[operando] -> numero_dato % 100;
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
	if (aux > 9999 || aux < -9999)
		return ST_ERROR_ACUMULADOR_MUY_GRANDE;
	(*instrucciones)[operando] -> numero_dato =  aux;
	(*instrucciones)[operando] -> opcode = (*instrucciones)[operando] -> numero_dato / 100;
	(*instrucciones)[operando] -> operando = (*instrucciones)[operando] -> numero_dato % 100;
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

status_t jmp (struct instruccion *** instrucciones, size_t operando,  long cantidad_de_memoria, size_t * i) {
	if (instrucciones == NULL)
		return ST_ERROR_PUNTERO_NULO;
	*i = operando - 1; /*Se le resta 1 para que cuando sume el ciclo, quede en la operandoicion correcta*/
	return ST_OK;
}
