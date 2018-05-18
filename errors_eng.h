#ifndef ERRORS_ENG__H
#define ERRORS_ENG__H

#define MAX_ERROR_STR 35

#define ERROR "Error"
#define NO_HAY_ERROR "There is no error"
#define MSG_ERROR_NULL_POINTER "A null pointer has been encountered"
#define MSG_ERROR_ARGS_QUANTITY "Invalid argument quantity"
#define MSG_ERROR_NO_MEMORY "There is not enough memory"
#define MSG_ERROR_INVALID_INPUT "Invalid input"
#define MSG_ERROR_FILE_INPUT_DEMASIADO_LARGO 
#define MSG_ERROR_BIN_INPUT_INCORRECTO 
#define MSG_ERROR_FILE_OUTPUT_DEMASIADO_LARGO 
#define MSG_ERROR_BIN_OUTPUT_INCORRECTO 
#define MSG_ERROR_INVALID_ARGUMENT "Invalid argument"
#define MSG_ERROR_INVALID_INSTRUCTION "Invalid instruction"
#define MSG_ERROR_DIMENSION 
#define MSG_ERROR_INVALID_OPCODE "Invalid  opcode"
#define MSG_ERROR_READING_FILE "File could not be read"

char error [][MAX_ERROR_STR] = {
	NO_HAY_ERROR,
	MSG_ERROR_NULL_POINTER,
	MSG_ERROR_ARGS_QUANTITY,
	MSG_ERROR_NO_MEMORY,
	MSG_ERROR_INVALID_INPUT,
	MSG_ERROR_FILE_INPUT_DEMASIADO_LARGO,
	MSG_ERROR_BIN_INPUT_INCORRECTO,
	MSG_ERROR_FILE_OUTPUT_DEMASIADO_LARGO,
	MSG_ERROR_BIN_OUTPUT_INCORRECTO,
	MSG_ERROR_INVALID_ARGUMENT,
	MSG_ERROR_INVALID_INSTRUCTION,
	MSG_ERROR_DIMENSION,
	MSG_ERROR_INVALID_OPCODE,
	MSG_ERROR_READING_FILE
};


#endif
