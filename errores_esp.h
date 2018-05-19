#ifndef ERRORES_ESP__H
#define ERRORES_ESP__H

#define MAX_ERROR_STR 50

#define ERROR "Error"
#define NO_HAY_ERROR "No hay error"
#define MSJ_ERROR_PUNTERO_NULO "Se encontró un puntero nulo"
#define MSJ_ERROR_CANTIDAD_DE_ARGS "Cantidad de argumentos inválida"
#define MSJ_ERROR_MEMORIA_INVALIDA "No hay memoria disponible"
#define MSJ_ERROR_ENTRADA_INVALIDA "Se ingresó un caracter inválido"
#define MSJ_ERROR_FILE_INPUT_DEMASIADO_LARGO "Nombre de archivo de entrada demasiado largo"
#define MSJ_ERROR_BIN_INPUT_INCORRECTO "No es un argumento valido para -if"
#define MSJ_ERROR_FILE_OUTPUT_DEMASIADO_LARGO "Nombre de archivo de salida demasiado largo"
#define MSJ_ERROR_BIN_OUTPUT_INCORRECTO "No es un argumento valido para -of"
#define MSJ_ERROR_ARGUMENTO_INVALIDO "El argumento ingresado es inválido"
#define MSJ_ERROR_INSTRUCCION_INVALIDA "La instrucción es inválida"
#define MSJ_ERROR_LECTURA_ARCHIVO "No se pudo leer el archivo"
#define MSJ_ERROR_SIMPLETRON "En ejecucion de Simpletron"

char error [][MAX_ERROR_STR] = {
	NO_HAY_ERROR,
	MSJ_ERROR_PUNTERO_NULO,
	MSJ_ERROR_CANTIDAD_DE_ARGS,
	MSJ_ERROR_MEMORIA_INVALIDA,
	MSJ_ERROR_ENTRADA_INVALIDA,
	MSJ_ERROR_FILE_INPUT_DEMASIADO_LARGO,
	MSJ_ERROR_BIN_INPUT_INCORRECTO,
	MSJ_ERROR_FILE_OUTPUT_DEMASIADO_LARGO,
	MSJ_ERROR_BIN_OUTPUT_INCORRECTO,
	MSJ_ERROR_ARGUMENTO_INVALIDO,
	MSJ_ERROR_INSTRUCCION_INVALIDA,
	MSJ_ERROR_LECTURA_ARCHIVO,
	MSJ_ERROR_SIMPLETRON
};

#endif
