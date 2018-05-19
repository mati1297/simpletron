#makefile Simpletron

CC = gcc
CFLAGS = -ansi -Wall -pedantic

todo: simpletron_esp limpiar

simpletron_esp: main.o argumentos.o procesamiento.o funciones.o dump.o herramientas.o error.o
	$(CC) $(CFLAGS) -o simpletron main.o argumentos.o procesamiento.o funciones.o dump.o herramientas.o error.o
main.o: main.c argumentos.h procesamiento.h funciones.h dump.h types.h
	$(CC) $(CFLAGS) -o main.o -c main.c
argumentos.o: argumentos.c argumentos.h types.h herramientas.h error.h
	$(CC) $(CFLAGS) -o argumentos.o -c argumentos.c
procesamiento.o: procesamiento.c procesamiento.h argumentos.h herramientas.h types.h error.h
	$(CC) $(CFLAGS) -o procesamiento.o -c procesamiento.c
funciones.o: funciones.c funciones.h procesamiento.h types.h idioma.h error.h
	$(CC) $(CFLAGS) -o funciones.o -c funciones.c -D ESP
dump.o: dump.c dump.h argumentos.h procesamiento.h funciones.h types.h idioma.h error.h
	$(CC) $(CFLAGS) -o dump.o -c dump.c -D ESP
herramientas.o: herramientas.c herramientas.h types.h
	$(CC) $(CFLAGS) -o herramientas.o -c herramientas.c
error.o: error.c error.h types.h idioma.h
	$(CC) $(CFLAGS) -o error.o -c error.c -D ESP

limpiar:
	rm *.o

all: simpletron_eng clean

simpletron_eng: main.o argumentos.o procesamiento.o funciones.o dump.o herramientas.o error.o
	$(CC) $(CFLAGS) -o simpletron main.o argumentos.o procesamiento.o funciones.o dump.o herramientas.o error.o
main.o: main.c argumentos.h procesamiento.h funciones.h dump.h types.h
	$(CC) $(CFLAGS) -o main.o -c main.c
argumentos.o: argumentos.c argumentos.h types.h herramientas.h error.h
	$(CC) $(CFLAGS) -o argumentos.o -c argumentos.c
procesamiento.o: procesamiento.c procesamiento.h argumentos.h herramientas.h types.h error.h
	$(CC) $(CFLAGS) -o procesamiento.o -c procesamiento.c
funciones.o: funciones.c funciones.h procesamiento.h types.h idioma.h error.h
	$(CC) $(CFLAGS) -o funciones.o -c funciones.c -D ENG
dump.o: dump.c dump.h argumentos.h procesamiento.h funciones.h types.h idioma.h error.h
	$(CC) $(CFLAGS) -o dump.o -c dump.c -D ENG
herramientas.o: herramientas.c herramientas.h types.h
	$(CC) $(CFLAGS) -o herramientas.o -c herramientas.c
error.o: error.c error.h types.h idioma.h
	$(CC) $(CFLAGS) -o error.o -c error.c -D ENG

clean:
	rm *.o