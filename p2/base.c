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
#include "operation.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// This preprocessor syntax makes it so we can override the value of BASE with
// a compiler option.  For some desired base, n, we can compile with: -DBASE=n
// Don't change these three lines of preprocessor directives.
#ifndef BASE
/** Base this program uses for input and output. */
#define BASE 7
/** Terminates BASE preprocessor */
#endif 
// Minimum ASCII value of uppercase chars
#define MIN_ASCII_LETTER 65
// Maximum ASCII value of uppercase chars
#define MAX_ASCII_LETTER 90
// Minimum ASCII value of number
#define MIN_ASCII_NUMBER 48
// Maximum ASCII value of number
#define MAX_ASCII_NUMBER 57
// Value of first switch to letters in hexidecimal
#define DECIMAL_VAL 10


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

/** The isNumber() function determines if the char is a valid number.
    
    @param ch is the char being assessed.
    @return true if ch is a valid char. Otherwise, return false.
  */
bool isNumber( char ch ) {
  bool number;
  if ( (ch <  MIN_ASCII_NUMBER || ch > MAX_ASCII_NUMBER) && 
       (ch < MIN_ASCII_LETTER || ch > MAX_ASCII_LETTER) ) {
    number = false;
  }
  
  return number;
}

/** The readValue() function uses the getchar() operator to create a long value 
    using Horner's Rule with the correct base applied.
    
    @return the long value that is created from input.
  */
long readValue()
{
  // Initialize an int value to store the number
  long value = 0;
  
  // One's place variable for Horner's Rule
  long d = 0;
  
  // Read first char
  int ch = skipSpace();
  // Check for negative value
  bool isNeg = false;
  if (ch == '-') {
    ch = getchar();
    isNeg = true;
  }
  
  // Exit on error if invalid char
//   if ( !isNumber( ch ) ) {
//     exit(FAIL_INPUT);
//   }
  
  // Perform Horner's Rule while we have a valid ASCII value
  while ( isNumber( ch ) ) {

    
    // Assign correct value to d
    if ( ch >= MIN_ASCII_LETTER ) {
      d = ch - MAX_ASCII_LETTER + DECIMAL_VAL;
    } else {
      d = ch - MIN_ASCII_NUMBER;
    }

    if ( d >= BASE ) {
      exit(FAIL_INPUT);
    }
    
    // Horner's Rule
    value = times( value, BASE );
    value = plus( value, d );
    
    ch = getchar();
  }

  // Un-get the non-ASCII range character
  ungetc( ch, stdin );
  
  // Return the value of the first input
  if ( isNeg ) {
    return times( value, -1 );
  } else {
    return value;
  }
  
}

/** The writeValue() function receives a long int parameter and processes it
    through the Horner's Rule algorithm and utilizes recursion to combat 
    printing the value in reverse order.
    
    @param value is the long integer value received when the function is called.
  */
void writeValue( long value )
{
  long d = 0;
  
  if (value < 0 ) {
    putchar('-');
    value = minus( 0, value );
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