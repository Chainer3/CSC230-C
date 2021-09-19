/**
    @file base.c
    @author Stephen Gonsalves (dkgonsal)
    
    The base.c program houses three functions. The first, skipSpace(), clears any spaces
    between valid input characters and returns the first non-space character it gets. The 
    second function, readValue(), takes in the first character of a value and verifies it
    is a valid char. It then, creates a long int value from the received characters. THe 
    final function, writeValue(), writes the result to the console, via the putchar()
    operator.
  */

#include "base.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "operation.h"

// This preprocessor syntax makes it so we can override the value of BASE with
// a compiler option.  For some desired base, n, we can compile with: -DBASE=n
// Don't change these three lines of preprocessor directives.
#ifndef BASE
/** Base this program uses for input and output. */
#define BASE 7
/** Terminates BASE preprocessor */
#endif 

/** The skipSpace() function returns the first non-whitespace character it gets.

    @return the first non-whitespace character
  */
int skipSpace()
{
  int ch = getchar();
  while ( ch == ' ' ) {
    ch = getchar();
  }
  
  return ch;
  
}

/** The readValue() function uses the getchar() operator to create a long value 
    using Horner's Rule with the correct base applied.
    
    @return the long value that is created from input.
  */
long readValue()
{
  // Initialize an int value to store the number
  int value = 0;
  
  // One's place variable for Horner's Rule
  int d = 0;
  
  // Initialize and get the next character that's not a space
  int ch = skipSpace();
  
  // Special case of initial char being a '\n'
  if (ch == '\n' ) {
    return EXIT_SUCCESS;
  }
  // Exit on error
  if ( (ch < '0' || ch > 'z') && ch != '-' ) {
    return FAIL_INPUT;
  }
  // Perform Horner's Rule while we have a valid ASCII value
  while ( ch >= '0' && ch <= 'z' ) {
    
    // Convert ASCII to int
    d = (int) ch;

    value = times( value, BASE );

    value = plus( value, d );

    // Get the next character for calculation
    ch = getchar();
  }

  // Un-get the non-ASCII range character
  ungetc( ch, stdin );
  
  return value;
}

/** The writeValue() function receives a long int parameter and processes it
    through the Horner's Rule algorithm and utilizes recursion to combat 
    printing the value in reverse order.
    
    @param value is the long integer value received when the function is called.
  */
void writeValue( long value )
{
  int d;
  
  if (value < 0 ) {
    putchar('-');
    value = -value;
  }

  if ( value != 0 ) {
    // Apply Horner's Rule
    d = value % BASE; 
    value = minus( value, d);

    // Decrease size of value by base
    if ( value > 0 ) {
      value = divide( value, BASE );
    }
    
    // Make recursive call
    writeValue( value );
    
  }
    // Print the stack
    putchar( d + '0' );

}