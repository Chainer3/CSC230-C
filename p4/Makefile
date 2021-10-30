CC = gcc
CFLAGS = -Wall -std=c99 -D_GNU_SOURCE -c -g

tour: tour.o map.o input.o
	$(CC) tour.o map.o input.o -o tour -lm
	
tour.o: tour.c map.h input.h
	$(CC) $(CFLAGS) tour.c -o tour.o -lm

map.o: map.c map.h input.h
	$(CC) $(CFLAGS) map.c -o map.o -lm

input.o: input.c input.h 
	$(CC) $(CFLAGS) input.c -o input.o -lm

clean:
	rm -f *.o
	rm -f tour
	rm -f *cmd.sh output.txt stderr.txt
