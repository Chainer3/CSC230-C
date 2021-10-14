OBJ = match.o pattern.o list.o input.o
CC = gcc
CFLAGS = -Wall -std=c99 -g
LIBS = -lm

match: $(OBJ)
	$(CC) $(LIBS) $(CFLAGS) $(OBJ) -o match
	
match.o: match.c
	$(CC) $(CFLAGS) -c match.c -o match.o

pattern.o: pattern.c pattern.h 
	$(CC) $(CFLAGS) -c pattern.c -o pattern.o

list.o: list.c list.h 
	$(CC) $(CFLAGS) -c list.c -o list.o

input.o: input.c input.h 
	$(CC) $(CFLAGS) -c input.c -o input.o

clean:
	rm -f *.o
	rm -f match
	rm -f *.h.gch output.txt