CC=gcc
CFLAGS=-g -Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca dehilos
LIBS = -lm -pthread
all: p2_e1a
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':'(dependencias)
########################################################################
all: p2_e1a p2_e1b p2_e2

p2_e1a: p2_e1a.o libstack.a
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e1b: p2_e1b.o graph.o vertex.o libstack.a
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) graph.o vertex.o

p2_e2: p2_e2.o graph.o vertex.o libstack.a
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) graph.o vertex.o

vertex.o: vertex.c vertex.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

graph.o: graph.c graph.h vertex.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e1a.o: p2_e1a.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e1b.o: p2_e1b.c vertex.h graph.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e2.o: p2_e2.c vertex.h graph.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

run:
	./p2_e1b grades1.txt grades2.txt

runv:
	valgrind --leak-check=full ./p2_e1b cities1.txt cities2.txt

clear:
	rm -rf *.o 

clean:
	rm -rf *.o p2_e1a p2_e1b p2_e2