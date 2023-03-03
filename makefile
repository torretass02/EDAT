CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
all: main
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':'
########################################################################
main: main.o libstack.a
$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)
main.o: main.c
$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)