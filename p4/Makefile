OBJ = tour.o map.o input.o
CC = gcc
CFLAGS = -g -Wall -std=c99 -D_GNU_SOURCE

tour: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o tour
	
tour.o: tour.c map.h input.h
	$(CC) $(CFLAGS) -c tour.c -o tour.o

map.o: map.c map.h input.h
	$(CC) $(CFLAGS) -c map.c -o map.o

input.o: input.c input.h 
	$(CC) $(CFLAGS) -c input.c -o input.o

clean:
	rm -f *.o
	rm -f tour
	rm -f *cmd.sh output.txt stderr.txt