#include "pattern.h"
#include <stdio.h> // just for debugging.

/**
   Report the array of flags computed during a match.  This can be
   useful for watching how your pattern matching is working.  The pat
   array should be the pattern given on the command line.  The flags
   array should be one element longer, representing states before each
   character of the pattern plus one more state at the end for when
   the whole pattern has ben matched.
   @param pat String containing the pattern
   @param flags Array contianing true for each state that can be reached.
 */
static void reportFlags( char const pat[], bool const flags[] )
{
  // Print the pattern and figure out how long it is.
  int n = 0;
  for ( int i = 0; pat[ i ]; i++, n++ )
    printf( "%c", pat[ i ] );
  printf( "\n" );

  // Print all the states.  For reachable states, print a caret pointing
  // up to the next character of the pattern that needs to be matched.
  for ( int i = 0; i <= n; i++ )
    printf( "%c", flags[ i ] ? '^' : ' ' );
  printf( "\n\n" ); // Extra blank line at the end.
}
