/**
   @file style.c
   @author Stephen Gonsalves (dkgonsal)
   
   This program uses an random number generator (rng) to print a paragraph of 
   random strings comprised only of lower-case letters. It will print the total
   word count once the paragraph's line limit (10) has been reached.
*/

#include "base.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "operation.h"

int main( void )
{
  bool isEOL = false;
  long a = readValue();
  printf("a = %ld", a);
  long total = a;
  int ch = skipSpace();
     
  while (!isEOL) {
    long b;
    
    if (ch == '\n') {
      isEOL = true;
      exit(FAIL_INPUT);
    }
    
    if ( ch == '+' ) {
      b = readValue();
      total = plus( a, b );
    } else if ( ch == '-' ) {
      b = readValue();    
      total = minus( a, b );
    } else if ( ch == '*' ) {
      b = readValue();
      total = times( a, b );
    } else if ( ch == '/' ) {
      b = readValue();
      total = divide( a, b );
    } else {
      break;
    }
  }
  
  writeValue( total );
  
  // Exit the program
  return EXIT_SUCCESS; 
}