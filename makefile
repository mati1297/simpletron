#makefile Simpletron

CC = gcc
CFLAGS = -ansi -Wall -pedantic
FLAG_ESP = -DIDIOMA_ESPANIOL
FLAG_ENG = -DLANG_ENGLISH

espaniol:
	make CFLAGS+="$(FLAGS_ESP)" all

english:
	make CFLAGS+="$(FLAGS_ENG)" all
	
all: simpletron clean

simpletron: main.o argumentos.o procesamiento.o funciones.o dump.o herramientas.o error.o
	$(CC) $(CFLAGS) -o simpletron main.o argumentos.o procesamiento.o funciones.o dump.o herramientas.o error.o
main.o: main.c main.h argumentos.h error.h herramientas.h simpletron.h procesamiento.h funciones.h dump.h types.h
	$(CC) $(CFLAGS) -o main.o -c main.c
argumentos.o: argumentos.c main.h argumentos.h types.h herramientas.h error.h
	$(CC) $(CFLAGS) -o argumentos.o -c argumentos.c
procesamiento.o: procesamiento.c procesamiento.h herramientas.h types.h error.h simpletron.h
	$(CC) $(CFLAGS) -o procesamiento.o -c procesamiento.c
funciones.o: funciones.c funciones.h procesamiento.h types.h idioma.h error.h simpletron.h
	$(CC) $(CFLAGS) -o funciones.o -c funciones.c
dump.o: dump.c dump.h simpletron.h procesamiento.h funciones.h types.h idioma.h error.h
	$(CC) $(CFLAGS) -o dump.o -c dump.c
herramientas.o: herramientas.c herramientas.h types.h idioma.h error.h simpletron.h
	$(CC) $(CFLAGS) -o herramientas.o -c herramientas.c
error.o: error.c error.h types.h idioma.h
	$(CC) $(CFLAGS) -o error.o -c error.c

clean:
	rm *.o
