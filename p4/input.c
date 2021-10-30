/**
   @file input.c
   @author Stephen Gonsalves (dkgonsal)
   
   The input file handles functions focused on File and Terminal I/O. 
 */

#include <math.h>
#include "input.h"

/* The readLine() function receives a file stream pointer that it uses to read a single
   line of text from the input file. If the input reaches EOF, the function 
   
   @param the file stream opened in map.c
   @return the line of input.
*/
char *readLine( FILE *fp )
{
  // Allocate a string with a small, initial capacity.
  int capacity = 5;
  char *input = ( char * ) malloc( capacity * sizeof( char ) + 1) ;
  
  // Grab first char in case of empty file
  char ch = fgetc( fp );
  if ( ch == EOF ) {
    free( input );
    return NULL;
  }

  // Number of characters we're currently using.
  int len = 0;

  while ( ch != '\n') {
    if ( len >= capacity ) {
      capacity *= 2;
      char *temp = ( char *) malloc( capacity * sizeof( char ) + 1 );
      temp = input;
      free( input );
      input = temp;
    }

    input[ len++ ] = ch;
    ch = fgetc( fp );
  }

  input[ len ] = '\0';
  return input;
}