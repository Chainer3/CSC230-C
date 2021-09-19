#include <base.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <operation.h>

// This preprocessor syntax makes it so we can override the value of BASE with
// a compiler option.  For some desired base, n, we can compile with: -DBASE=n
// Don't change these three lines of preprocessor directives.
#ifndef BASE
/** Base this program uses for input and output. */
#define BASE 7

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
    using Horner's Rule.
    
    @return the long value that is created from input.
  */
long readValue()
{

  // Initialize an int value to store the number
  int value = 0;
  
  // Initialize and get the next character
  int ch = skipSpace();
 
  // Exit on error
  if ( ch < '0' || ch > 'z' || ch != '-' ) {
    return FAIL_INPUT;
  
  // Perform Horner's Rule while we have valid ASCII value
  while ( ch >= '0' && ch <= 'z' ) {
    // Convert ASCII to int
    d = atoi( ch );

    value = times( value, BASE);

    value = plus( value, d);

    // Get the next character for calculation
    ch = next_input_char();
  }

  // Un-get the non-ASCII range character
  int unget( ch );
  
  return value;
}

/** The writeValue() function receives a long int parameter and processes it
    through the Horner's Rule algorithm and utilizes recursion to combat 
    printing the value in reverse order.
    
    @param value is the long integer value received when the function is called.
  */
void writeValue( long value )
{
  int ch;
  int d;
  
  if (value < 0) {
    putchar('-');
  }

  if ( value != 0 ) {
    d = value % BASE; 
    value = minus( value, d);
    
    // Changes int to char
    ch = d + '0';
    
    // Decrease size of value by base
    if ( value > 0) {
    value = divide( value, BASE);
    }
    
    if (value == 0) {
      return;
    }
    
    writeValue( value );
    putchar( ch );
  }

}