/**
    @file input.c
    @author Stephen Gonsalves (dkgonsal)
    
    
  */

#include "input.h"

/** The readLine() method validates a received stream, copied into a char array
    and determines its validity based on the defined capacity. It returns a boolean
    response based on validity.
    
    @param *fp is the received file stream to read in.
    @param line is the char array for storing each char of the string.
    @param capacity is the max allowable capacity of the read input.
    @return It returns true if the line is valid. Otherwise, returns false.
  */
bool readLine( FILE *fp, char line[], int capacity ) 
{
  int len = 0;

  // Get/test first char and continue reading until newline char
  char ch = fgetc( fp );
  if ( ch == EOF ) {
    return false;
  } 
  
  // 
  while ( ch != '\n' ) {
    if ( len < capacity ) {
      line[ len++ ] = ch; 
    } else if ( len == capacity ){
      fprintf( stderr, "Line too long\n");
      exit( 1 );
    }
    ch = fgetc( fp );
  }

  line [ len ] = '\0';
  return true;
}