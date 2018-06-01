#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "types.h"
#include "idioma.h"
#include "procesamiento.h"
#include "error.h"
#include "simpletron.h"


/* Recibe la cantidad de memoria pedida por el usuario y por puntero las
 * estruturas con el estado actual de Simpletron y las instrucciones
 * ingresadas por el usuario. La función se encarga de ejecutar los opcodes
 * adecuados en el orden que lo indique la estructura de instrucciones.
 * En caso de que alguna de las funciones llamadas falle, que haya un error
 * local, o que todo funcione en orden, devuelve un estado por la interfaz */
status_t seleccion_de_funcion (struct instruccion *** instrucciones, long cantidad_de_memoria, struct estado * estado) {
	status_t st;
	size_t i;
	if (instrucciones == NULL || estado == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	estado -> acc = 0;
	
	for (i = 0, estado -> contador = 0; i < cantidad_de_memoria; i++) {
		
		
		/*Se cargan los nuevos datos al estado*/
		estado -> instruccion_actual = *(*instrucciones)[i];
		(estado -> contador)++;
		
		if((*instrucciones)[i] -> opcode == OP_HALT)
			break;
			
		if((*instrucciones)[i] -> operando >= cantidad_de_memoria)
			return ST_ERROR_SIMPLETRON;

		
		switch ((*instrucciones)[i] -> opcode) {
			case OP_LEER:
				if((st = leer (instrucciones, (*instrucciones)[i] -> operando)) != ST_OK)
					return st;
				break;
			
			case OP_ESCRIBIR:
				if((st = escribir (instrucciones, (*instrucciones)[i] -> operando)) != ST_OK)
					return st;
				break;
			case OP_CARGAR:
				if((st = cargar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) 
					return st;
			case OP_GUARDAR:
				if((st = guardar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK)
					return st;
				break;
			case OP_PCARGAR:
				if((st = pcargar(instrucciones, cantidad_de_memoria, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) 
					return st;
				break;
			case OP_PGUARDAR:
				if((st = pguardar (instrucciones, cantidad_de_memoria, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) 
					return st;
				break;
			case OP_SUMAR:
				if((st = sumar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) 
					return st;
				break;
			case OP_RESTAR:
				if((st = restar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK)
					return st;
				break;
			case OP_DIVIDIR:
				if((st = dividir (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK) 
					return st;
				break;
			case OP_MULTIPLICAR:
				if((st = multiplicar (instrucciones, (*instrucciones)[i] -> operando, &(estado -> acc))) != ST_OK)
					return st;
				break;
			case OP_JMP:
				if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK)
					return st;
				break;
			case OP_JMPNEG:
				if ((estado -> acc) < 0)
					if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK) 
						return st;
				break;
			case OP_JMPZERO:
				if (!(estado -> acc))
					if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK) 
						return st;
				break;
			case OP_JNZ:
				if ((estado -> acc))
					if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK)
						return st;
				break;
			case OP_DJNZ:
				if (--(estado -> acc))
					if((st = jmp (instrucciones, (*instrucciones)[i] -> operando, &i)) != ST_OK) 
						return st;
				break;
			default:
				return ST_ERROR_SIMPLETRON;
		}	
	}
	
	if (i >= cantidad_de_memoria) 
		return ST_ERROR_SIMPLETRON;
		
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y el operando actual. Lee por pantalla el dato ingresado por
 * el usuario y lo guarda como una nueva instrucción en el vector de punteros
 * a estructuras, reemplazando lo que esté allí. En caso de un error o que
 * todo funcione en orden lo informa a través de la interfaz */
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
	(*instrucciones)[operando] -> instruccion = numero_aux;
	(*instrucciones)[operando] -> opcode = (*instrucciones)[operando] -> instruccion / MAX_CANT_OPERANDOS;
	(*instrucciones)[operando] -> operando = (*instrucciones)[operando] -> instruccion % MAX_CANT_OPERANDOS;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y el operando actual. Imprime por stdout la instrucción guardada
 * en el operando indicado. En caso de un error o que todo funcione en orden
 * lo informa a través de la interfaz */
status_t escribir (struct instruccion *** instrucciones, size_t operando) {
	if (instrucciones == NULL)
		return ST_ERROR_PUNTERO_NULO;
	fprintf(stdout, "%s %lu: %d\n", MSJ_CONTENIDO_POSICION, operando, (*instrucciones)[operando] -> instruccion);
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Guarda en el acumulador
 * el valor de la instrucción del operando actual. En caso de un error o
 * que todo funcione en orden lo informa a través de la interfaz */
status_t cargar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	*acc = (*instrucciones)[operando] -> instruccion;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Guarda en la posición que
 * indica el operando el valor de el acumulador. En caso de un error o
 * que todo funcione en orden lo informa a través de la interfaz */
status_t guardar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	int aux;
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	aux = *acc;
	if (aux > MAX_MODULO || aux < -MAX_MODULO)
		return ST_ERROR_SIMPLETRON;
	(*instrucciones)[operando] -> instruccion =  aux;
	(*instrucciones)[operando] -> opcode = (*instrucciones)[operando] -> instruccion / MAX_CANT_OPERANDOS;
	(*instrucciones)[operando] -> operando = (*instrucciones)[operando] -> instruccion % MAX_CANT_OPERANDOS;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Suma el valor guardado
 * en la posición que indica el operando con la del acumulador,
 * sobreescribiendo lo que estaba en este. En caso de un error o que todo
 * funcione en orden lo informa a través de la interfaz */
status_t sumar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	(*acc) += (*instrucciones)[operando] -> instruccion;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Resta el valor guardado
 * en la posición que indica el operando con la del acumulador,
 * sobreescribiendo lo que estaba en este. En caso de un error o que todo
 * funcione en orden lo informa a través de la interfaz */
status_t restar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	(*acc) -= (*instrucciones)[operando] -> instruccion;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Divide el valor guardado
 * en la posición que indica el operando con la del acumulador,
 * sobreescribiendo lo que estaba en este. En caso de un error o que todo
 * funcione en orden lo informa a través de la interfaz */
status_t dividir (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	(*acc) /= (*instrucciones)[operando] -> instruccion;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Multiplica el valor guardado
 * en la posición que indica el operando con la del acumulador,
 * sobreescribiendo lo que estaba en este. En caso de un error o que todo
 * funcione en orden lo informa a través de la interfaz */
status_t multiplicar (struct instruccion *** instrucciones, size_t operando, long * acc) {
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	(*acc) *= (*instrucciones)[operando] -> instruccion;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al número de instrucción actual, y el operando actual. Hace
 * un "salto" a la instrucción que se le indica enn el operando. En caso
 * de un error o que todo funcione en orden lo informa a través de la interfaz */
status_t jmp (struct instruccion *** instrucciones, size_t operando, size_t * i) {
	if (instrucciones == NULL)
		return ST_ERROR_PUNTERO_NULO;
	*i = operando - 1; /*Se le resta 1 para que cuando sume el ciclo, quede en la operandoicion correcta*/
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, la cantidad de memoria pedida por el usuario
 * y el operando actual. Guarda por puntero el valor del operando en el
 * acumulador. En caso de un error o que todo funcione en orden lo informa
 * a través de la interfaz */
status_t pcargar (struct instruccion *** instrucciones, long cantidad_de_memoria, size_t operando, long * acc) {
	int aux;
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if ((aux = (*instrucciones)[operando] -> instruccion) >= cantidad_de_memoria)
		return ST_ERROR_SIMPLETRON;
	*acc = (*instrucciones)[aux] -> instruccion;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, la cantidad de memoria pedida por el usuario
 * y el operando actual. Guarda por puntero el valor del acumulador en la
 * instrucción indicada por el operando. En caso de un error o que todo
 * funcione en orden lo informa a través de la interfaz */
status_t pguardar (struct instruccion *** instrucciones, long cantidad_de_memoria, size_t operando, long * acc) {
	int aux;
	if (instrucciones == NULL || acc == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if ((aux = (*instrucciones)[operando] -> instruccion) >= cantidad_de_memoria)
		return ST_ERROR_SIMPLETRON;
	if (*acc > MAX_MODULO || *acc < -MAX_MODULO)
		return ST_ERROR_SIMPLETRON;
	(*instrucciones)[aux] -> instruccion = *acc;
	(*instrucciones)[aux] -> opcode = (*instrucciones)[aux] -> instruccion / MAX_CANT_OPERANDOS;
	(*instrucciones)[aux] -> operando = (*instrucciones)[aux] -> instruccion % MAX_CANT_OPERANDOS;
	return ST_OK;
}
