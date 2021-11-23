OBJGQ = gq.o queue.o input.o ntype.o

CC = gcc
FLAGS = -Wall -std=c99 -g -D_GNU_SOURCE
LIBS = -lm

gq: $(OBJGQ)
	$(CC) $(FLAGS) $(OBJGQ) -o gq $(LIBS)

gq.o : gq.c queue.o input.o ntype.o
	$(CC) $(FLAGS) -c gq.c -o gq.o $(LIBS)

ntype.o : ntype.h ntype.c queue.o
	$(CC) $(FLAGS) -c ntype.c -o ntype.o $(LIBS)

queue.o : queue.c queue.h
	$(CC) $(FLAGS) -c queue.c -o queue.o $(LIBS)

input.o : input.h input.c
	$(CC) $(FLAGS) -c input.c -o input.o $(LIBS)

clean:
	rm -f *.o
	rm -f gq
	rm -f *cmd.sh