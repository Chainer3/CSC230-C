OBJECTS = calc7.o base.o operation.o calc20.o operation.o
OUTPUT = calc7,calc20

OBJECTS7 = calc7.o base7.o operation.o
SOURCE_FILES7 = calc7.c base.c operation.c
HEADER7 = base.h operation.h
OUT7 = calc7

OBJECTS20 = calc20.o base20.o operation.o
SOURCE_FILES20 = calc20.c base.c operation.c
HEADER7 = base.h operation.h
OUT20 = calc20

CC = gcc
CFLAGS = -Wall -std=c99 -c -g
LDLIBS = -lm


all: calc7 calc20

calc7: $(OBJECTS7)
	$(CC) $(LDLIBS) -g $(OBJECTS7) -o $(OUT7)
    
calc20: $(OBJECTS20)
	$(CC) $(LDLIBS) -g $(OBJECTS20) -o $(OUT20)
    
calc7.o: calc.c base7.o
	$(CC) $(CFLAGS) calc.c -o calc7.o

base7.o: base.c operation.c
	$(CC) $(CFLAGS) "-DBASE=7" base.c -o base7.o

base20.o: base.c operation.o
	$(CC) $(CFLAGS) "-DBASE=20" base.c -o base20.o

operation.o: operation.c
	$(CC) $(CFLAGS) operation.c -o operation.o

calc20.o: calc.o base20.o operation.o
	$(CC) $(CFLAGS) calc.c -o calc20.o
    
calc.o: calc.c base.c operation.c base.h operation.h 
	$(CC) $(CFLAGS) calc.c base.c operation.c base.h operation.h 

clean:
	rm -f *.o
	rm -f calc base operation
	rm -f calc7 calc20
	rm -f *.h.gch calc20. output.txt