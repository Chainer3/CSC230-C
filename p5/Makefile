OBJDef = deflate.o buffer.o dictionary.o
OBJInf = inflate.o buffer.o dictionary.o

CC = gcc -D_GNU_SOURCE
CFLAGS = -Wall -std=c99 -g -c

all: deflate inflate

deflate: $(OBJDef)
	$(CC) $(OBJDef) -o deflate -lm

inflate: $(OBJInf)
	$(CC) $(OBJInf) -o inflate -lm

deflate.o: deflate.c buffer.o dictionary.o
	$(CC) $(CFLAGS) -o deflate.o deflate.c -lm

inflate.o: inflate.c buffer.o dictionary.o
	$(CC) $(CFLAGS) -o inflate.o inflate.c -lm

buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -o buffer.o buffer.c -lm

dictionary.o: dictionary.c dictionary.h
	$(CC) $(CFLAGS) -o dictionary.o dictionary.c -lm

clean:
	rm -f *.o
	rm -f bufferTest inflate deflate
	rm -f *cmd.sh output.txt stderr.txt