CC = gcc
CFLAGS= -Wall -c


build: tema1

tema1: tema1.o ht.o list.o
	$(CC) $^ -o $@ -lhash -L.

tema1.o: tema1.c
	$(CC) $(CFLAGS) $^ -o $@

ht.o: ht.c
	$(CC) $(CFLAGS) $^ -o $@

list.o: list.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf *.o tema1
