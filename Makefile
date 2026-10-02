CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
INCLUDES = -Iinclude

programa: src/main.c src/grafo.c include/grafo.h
	$(CC) $(CFLAGS) src/main.c src/grafo.c $(INCLUDES) -o programa

testes: tests/test_grafo.c src/grafo.c include/grafo.h
	$(CC) $(CFLAGS) tests/test_grafo.c src/grafo.c $(INCLUDES) -o testes

all: programa testes

clean:
	rm -f programa testes programa.exe testes.exe *.o
