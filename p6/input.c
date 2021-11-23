/**
 *  @file input.c
 *  @author Stephen Gonsalves (dkgonsal)
 *  
 *  The input file handles functions focused on File and Terminal I/O. 
 */

#include "input.h"

/* The readLine() function receives a file stream pointer that it uses to read a single
   line of text from the input file. If the input reaches EOF, the function 
   
   @param fp the file stream opened in map.c
   @return the line of input.
*/
char *readLine( FILE *fp )
{
  if ( !fp ) {
    return NULL;
  }
  
  // Allocate a string with a small, initial capacity.
  int capacity = CMD_CAP;
  int len = 0;
  char *input = ( char * ) malloc( capacity * sizeof( char ) + 1 );

  // Grab first char in case of empty file
  char ch = fgetc( fp );

  while ( ch != '\n' && ch != EOF ) {
    if ( len >= capacity ) {
      capacity *= 2;
      input = ( char * ) realloc(input, (capacity + 1) * sizeof( char ) );
    }

    input[ len++ ] = ch;
    ch = fgetc( fp );
  }

  input[ len ] = '\0';
  return input;
}