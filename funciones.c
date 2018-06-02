#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "types.h"
#include "idioma.h"
#include "procesamiento.h"
#include "error.h"
#include "simpletron.h"


/* Recibe la cantidad de memoria pedida por el usuario y por puntero las
 * estruturas con el simpletron actual de Simpletron y las instrucciones
 * ingresadas por el usuario. La función se encarga de ejecutar los opcodes
 * adecuados en el orden que lo indique la estructura de instrucciones.
 * En caso de que alguna de las funciones llamadas falle, que haya un error
 * local, o que todo funcione en orden, devuelve un simpletron por el nombre */
status_t ejecutar_simpletron (struct simpletron * simpletron, long cantidad_de_memoria) {
	status_t st;
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	simpletron -> acc = 0;
	
	while(simpletron -> contador < cantidad_de_memoria) {
		
		
		/*Se cargan los nuevos datos al simpletron*/
		simpletron -> instruccion_actual = *(simpletron -> memoria[simpletron -> contador]);
		
		if(simpletron -> memoria[simpletron -> contador] -> opcode == OP_HALT)
			break;
		
		/*Se verifica que la posicion indicada por el operando sea
		 * valida para no tener que validarlo en cada funcion*/	
		if(simpletron -> instruccion_actual.operando >= cantidad_de_memoria)
			return ST_ERROR_SIMPLETRON;

		
		switch (simpletron -> instruccion_actual.opcode) {
			case OP_LEER:
				if((st = leer (simpletron)) != ST_OK)
					return st;
				break;
			
			case OP_ESCRIBIR:
				if((st = escribir (simpletron)) != ST_OK)
					return st;
				break;
			case OP_CARGAR:
				if((st = cargar (simpletron)) != ST_OK)
					return st;
			case OP_GUARDAR:
				if((st = guardar (simpletron)) != ST_OK)
					return st;
				break;
			case OP_PCARGAR:
				if((st = pcargar(simpletron, cantidad_de_memoria)) != ST_OK)
					return st;
				break;
			case OP_PGUARDAR:
				if((st = pguardar (simpletron, cantidad_de_memoria)) != ST_OK)
					return st;
				break;
			case OP_SUMAR:
				if((st = sumar (simpletron)) != ST_OK)
					return st;
				break;
			case OP_RESTAR:
				if((st = restar (simpletron)) != ST_OK)
					return st;
				break;
			case OP_DIVIDIR:
				if((st = dividir (simpletron)) != ST_OK) 
					return st;
				break;
			case OP_MULTIPLICAR:
				if((st = multiplicar (simpletron)) != ST_OK)
					return st;
				break;
			case OP_JMP:
				if((st = jmp (simpletron)) != ST_OK)
					return st;
				break;
			case OP_JMPNEG:
				if ((simpletron -> acc) < 0)
					if((st = jmp (simpletron)) != ST_OK) 
						return st;
				break;
			case OP_JMPZERO:
				if (!(simpletron -> acc))
					if((st = jmp (simpletron)) != ST_OK) 
						return st;
				break;
			case OP_JNZ:
				if ((simpletron -> acc))
					if((st = jmp (simpletron)) != ST_OK)
						return st;
				break;
			case OP_DJNZ:
				if (--(simpletron -> acc))
					if((st = jmp (simpletron)) != ST_OK) 
						return st;
				break;
			default:
				return ST_ERROR_SIMPLETRON;
		}	
	}
	
	if (simpletron -> contador >= cantidad_de_memoria) 
		return ST_ERROR_SIMPLETRON;
		
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y el operando actual. Lee por pantalla el dato ingresado por
 * el usuario y lo guarda como una nueva instrucción en el vector de punteros
 * a estructuras, reemplazando lo que esté allí. En caso de un error o que
 * todo funcione en orden lo informa a través del nombre */
status_t leer (struct simpletron * simpletron) {
	char cadena_aux [LARGO_INSTRUCCION + 2], *endp;
	int numero_aux;
	size_t operando = simpletron -> instruccion_actual.operando;
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	printf("%s: ", MSJ_INGRESO_PALABRA);
	if (fgets(cadena_aux, LARGO_INSTRUCCION + 2, stdin) == NULL)
		return ST_ERROR_ENTRADA_INVALIDA;
		
	numero_aux = strtol(cadena_aux, &endp, 10);
	if (*endp != '\n' && *endp)
		return ST_ERROR_SIMPLETRON;
	if (numero_aux > MAX_PALABRA || numero_aux < MIN_PALABRA)
		return ST_ERROR_SIMPLETRON;
		
	simpletron -> memoria [operando] -> instruccion = numero_aux;
	simpletron -> memoria [operando] -> opcode = numero_aux / MAX_CANT_OPERANDOS;
	simpletron -> memoria [operando] -> operando = numero_aux  % MAX_CANT_OPERANDOS;
	
	simpletron -> contador++;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y el operando actual. Imprime por stdout la instrucción guardada
 * en el operando indicado. En caso de un error o que todo funcione en orden
 * lo informa a través del nombre */
status_t escribir (struct simpletron * simpletron) {
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	printf("%s %lu: %d\n", MSJ_CONTENIDO_POSICION, simpletron -> instruccion_actual.operando, simpletron -> memoria [simpletron -> instruccion_actual.operando] -> instruccion);
	
	simpletron -> contador++;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Guarda en el acumulador
 * el valor de la instrucción del operando actual. Se da por sentado que
 * si el valor estaba guardado en memoria, es un valor valido.
 * En caso de un error o que todo funcione en orden lo informa a través 
 * del nombre */
status_t cargar (struct simpletron * simpletron) {
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	simpletron -> acc = simpletron -> memoria[simpletron -> instruccion_actual.operando] -> instruccion;
	
	simpletron -> contador++;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Guarda en la posición que
 * indica el operando el valor del acumulador. En caso de un error o
 * que todo funcione en orden lo informa a través del nombre */
status_t guardar (struct simpletron * simpletron) {
	int aux;
	size_t operando = simpletron -> instruccion_actual.operando;
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	aux = simpletron -> acc;
	
	if (aux > MAX_PALABRA || aux < MIN_PALABRA)
		return ST_ERROR_SIMPLETRON;
		
	simpletron -> memoria[operando] -> instruccion =  aux;
	simpletron -> memoria[operando] -> opcode = aux / MAX_CANT_OPERANDOS;
	simpletron -> memoria[operando] -> operando = aux % MAX_CANT_OPERANDOS;
	
	simpletron -> contador++;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Suma el valor guardado
 * en la posición que indica el operando con la del acumulador,
 * sobreescribiendo lo que estaba en este. En caso de un error o que todo
 * funcione en orden lo informa a través del nombre */
status_t sumar (struct simpletron * simpletron) {
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	if(((simpletron -> acc) += simpletron -> memoria[simpletron -> instruccion_actual.operando] -> instruccion) > MAX_PALABRA)
		return ST_ERROR_SIMPLETRON;
		
	simpletron -> contador++;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Resta el valor guardado
 * en la posición que indica el operando con la del acumulador,
 * sobreescribiendo lo que estaba en este. En caso de un error o que todo
 * funcione en orden lo informa a través del nombre */
status_t restar (struct simpletron * simpletron) {
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	if(((simpletron -> acc) -= simpletron -> memoria[simpletron -> instruccion_actual.operando] -> instruccion) < MIN_PALABRA)
		return ST_ERROR_SIMPLETRON;
		
	simpletron -> contador++;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Divide el valor guardado
 * en la posición que indica el operando con la del acumulador,
 * sobreescribiendo lo que estaba en este. En caso de un error o que todo
 * funcione en orden lo informa a través del nombre */
status_t dividir (struct simpletron * simpletron) {
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	simpletron -> acc /= simpletron -> memoria [simpletron -> instruccion_actual.operando] -> instruccion;
	
	simpletron -> contador++;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, y el operando actual. Multiplica el valor guardado
 * en la posición que indica el operando con la del acumulador,
 * sobreescribiendo lo que estaba en este. En caso de un error o que todo
 * funcione en orden lo informa a través del nombre */
status_t multiplicar (struct simpletron * simpletron) {
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	if ((simpletron -> acc *= simpletron -> memoria[simpletron -> instruccion_actual.operando] -> instruccion) > MAX_PALABRA || simpletron -> acc < MIN_PALABRA)
		return ST_ERROR_SIMPLETRON;
		
	simpletron -> contador++;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al número de instrucción actual, y el operando actual. Hace
 * un "salto" a la instrucción que se le indica enn el operando. En caso
 * de un error o que todo funcione en orden lo informa a través del nombre */
status_t jmp (struct simpletron * simpletron) {
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	simpletron -> contador = simpletron -> instruccion_actual. operando;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, la cantidad de memoria pedida por el usuario
 * y el operando actual. Guarda por puntero el valor del operando en el
 * acumulador. En caso de un error o que todo funcione en orden lo informa
 * a través del nombre */
status_t pcargar (struct simpletron * simpletron, long cantidad_de_memoria) {
	int aux;
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if ((aux = simpletron -> memoria[simpletron -> instruccion_actual.operando] -> instruccion) >= cantidad_de_memoria || aux < 0)
		return ST_ERROR_SIMPLETRON;
		
	simpletron -> acc = simpletron -> memoria[aux] -> instruccion;
	
	simpletron -> contador++;
	return ST_OK;
}

/* Recibe un puntero a la estructura con los comandos ingresados por el
 * usuario y al acumulador, la cantidad de memoria pedida por el 
 usuario * y el operando actual. Guarda por puntero el valor del 
 acumulador en la * instrucción indicada por el operando. En caso de un 
 error o que todo * funcione en orden lo informa a través del nombre 
 */
status_t pguardar (struct simpletron * simpletron, long cantidad_de_memoria) {
	int aux;
	
	if (simpletron == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if ((aux = simpletron -> memoria[simpletron -> instruccion_actual.operando] -> instruccion) >= cantidad_de_memoria || aux < 0)
		return ST_ERROR_SIMPLETRON;
	if (simpletron -> acc > MAX_PALABRA || simpletron -> acc < MIN_PALABRA)
		return ST_ERROR_SIMPLETRON;
		
	simpletron -> memoria[aux] -> instruccion = simpletron -> acc;
	simpletron -> memoria[aux] -> opcode = simpletron -> acc / MAX_CANT_OPERANDOS;
	simpletron -> memoria[aux] -> operando = simpletron -> acc % MAX_CANT_OPERANDOS;
	
	simpletron -> contador++;
	return ST_OK;
}
