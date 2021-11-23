/**
 *
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/** Initial capacity of the return string */
#define CMD_CAP 10

/* The readLine() function receives a file stream pointer that it uses to read a single
   line of text from the input file. If the input reaches EOF, the function 
   
   @param the file stream opened in map.c
   @return the line of input.
*/
char *readLine( FILE *fp );