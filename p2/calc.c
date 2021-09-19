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
   if ( scanf( "%d", &base ) != 1 ) {
     exit(FAIL_INPUT);
}