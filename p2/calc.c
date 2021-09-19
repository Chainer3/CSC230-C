/**
   @file style.c
   @author Stephen Gonsalves (dkgonsal)
   
   This program uses an random number generator (rng) to print a paragraph of 
   random strings comprised only of lower-case letters. It will print the total
   word count once the paragraph's line limit (10) has been reached.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdin.h>

//Minimum base to use for computation of input
#define BASE_MIN 2
//Minimum base to use for computation of input
#define BASE_MAX 36

int main( void )
{
   bool isEOF = false;
   long a = readValue();
   
   while (!isEOF) { 
     ch = skipSpace();
     
     if ( ch == '+' ) {
       long b = readValue();
       a = plus( a, b );
     } else if ( ch == '-' ) {
       long b = readValue();
       a = minus( a, b );
     } else if ( ch == '*' ) {
       long b = readValue();
       a = times( a, b );
     } else if ( ch == '/' ) {
       long b = readValue();
       a = divide( a, b );
     } else if (ch == '\n') {
       writeValue(a);
       isEOF = true;
       
       // Exit the program
       return EXIT_SUCCESS; 
     }
   }
}