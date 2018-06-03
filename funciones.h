#ifndef FUNCIONES__H 
#define FUNCIONES__H 1

#include "error.h"
#include "simpletron.h"

status_t ejecutar_simpletron (struct simpletron * simpletron, long cantidad_de_memoria);
status_t leer (struct simpletron * simpletron);
status_t escribir (struct simpletron * simpletron);
status_t cargar (struct simpletron * simpletron);
status_t guardar (struct simpletron * simpletron);
status_t sumar (struct simpletron * simpletron);
status_t restar (struct simpletron * simpletron);
status_t dividir (struct simpletron * simpletron);
status_t multiplicar (struct simpletron * simpletron);
status_t jmp (struct simpletron * simpletron);
status_t pcargar (struct simpletron * simpletron, long cantidad_de_memoria);
status_t pguardar (struct simpletron * simpletron, long cantidad_de_memoria);

#endif
