/*
   @file operation.c
   #author Stephen Gonsalves (dkgonsal)
   
   The operation.c program handles the arithmetic and functions received through
   input.
 */

#include "base.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "operation.h"
#include "limits.h"

#define IS_NEGATIVE -1

/** The plus() function facilitates safe addition of two long value before returning the
    sum. If an overflow would occur the program will safely exit.
   
    @param a is the first long value used for subtraction.
    @param b is the second long value used for subtraction.
    @return the result or safely exit the function if an overflow would occur.
  */
long plus( long a, long b)
{
  if ( a >= 0 && b >= 0) {
    if ( a + b < 0 || a + b > LONG_MAX ) {
      return EXIT_STATUS;
    } else {
      return a + b;
    }
  } else if ( a < 0 && b < 0 ) {
    if ( a + b > LONG_MAX || a + b < LONG_MIN ) {
      return EXIT_STATUS;
    } else {
      return a + b;
    }
  } else {
    return a + b;
  }
}

/** The minus() function facilitates safe subtraction of two long values by first
    checking scenarios that would cause an overflow of the long type and safely exiting 
    if it does occur.
 
    @param a is the first long value used for subtraction.
    @param b is the second long value used for subtraction.
    @return the result or safely exit the function if an overflow would occur.
  */
long minus( long a, long b)
{
  if ( a >= 0 && b <= 0 ) {
    if ( a - b < 0 || a - b > LONG_MAX ) {
      return EXIT_STATUS;
    } else {
      return a - b;
    }
  } else if ( a < 0 && b >= 0) {
    if ( a - b > 0 || a - b < LONG_MIN ) {
      return EXIT_STATUS;
    } else {
      return a - b;
    }
  } else {
    return a - b;
  }
}

/** The times() function facilitates safe multiplication of paramenters before returning
    their product. If an overflow would occur the program will safely exit.

    @param a is the first long value used for multiplication.
    @param b is the second long value used for multiplication.
    @return the result or safely exit the function if an overflow would occur.
  */
long times( long a, long b ) {
  long c = LONG_MAX / b;    
  long d = LONG_MAX / a;    
  long e = LONG_MIN / b;   
  long f = LONG_MIN / a;

  if (( a >= 0 && b >= 0 ) && ( a * b <= LONG_MAX ) && ( d * a <= LONG_MAX ) && 
            ( a > c || b > d )) {
    return EXIT_STATUS;
  } else if (( a >= 0 && b <= 0 ) && c * b <= LONG_MAX && f * a >= LONG_MIN  &&
            (a > c || b < f)) {
    return EXIT_STATUS;
  } else if (( a <= 0 && b <= 0 ) && e * a >= LONG_MIN && f * a >= LONG_MIN &&
            ( a < e || b < f )) {
    return EXIT_STATUS;
  } else if (( a <= 0 && b >= 0 ) && e * a >= LONG_MIN && d * a <= LONG_MAX &&
            ( a < e || b > d )) {
    return EXIT_STATUS;
  } else if( ( a == LONG_MIN && b == IS_NEGATIVE ) || 
             ( b == LONG_MIN && a == IS_NEGATIVE ) ) {
    return EXIT_STATUS;
  } else {
    return a * b;
  }
}

/** The divide() function facilitates safe division of the paramenters before returning 
    the result. If an overflow would occur the program will safely exit.
    
    @param a is the first long value used for division.
    @param b is the second long value used for division.
    @return the result or safely exit the function if an overflow would occur.
  */
long divide( long a, long b)
{
  if ( b == 0 ) {
    return EXIT_STATUS_ZERO;
  } else if (  a == LONG_MIN && b == IS_NEGATIVE ) {
    return EXIT_STATUS;
  } else {
    return a / b;
  }
}