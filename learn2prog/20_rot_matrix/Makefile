CC=gcc
CFLAGS=-std=gnu99 -Wall
rotate-matrix: rotate.o read-matrix.o
	$(CC) -o rotate-matrix rotate.o read-matrix.o
.PHONY: clean
clean:
	rm -f rotate *.o *.c~ *.h~
