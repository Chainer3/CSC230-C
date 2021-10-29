#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* The readLine() function receives a file stream pointer that it uses to read a single
   line of text from the input file. If the input reaches EOF, the function 
   
   @param the file stream opened in map.c
   @return the line of input.
*/
char *readLine( FILE *fp );
