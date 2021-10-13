/**
   @file pattern.c
   @author Stephen Gonsalves (dkgonsal)

   The pattern file serves two functions within the match program. First, it validates
   the pattern received through args. Second, using a valid pattern, it compares the 
   line of text to determine if it is a match or not.
 */

#include "pattern.h"

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
// static void reportFlags( char const pat[], bool const flags[] )
// {
//   // Print the pattern and figure out how long it is.
//   int n = 0;
//   for ( int i = 0; pat[ i ]; i++, n++ )
//     printf( "%c", pat[ i ] );
//   printf( "\n" );
// 
//   // Print all the states.  For reachable states, print a caret pointing
//   // up to the next character of the pattern that needs to be matched.
//   for ( int i = 0; i <= n; i++ )
//     printf( "%c", flags[ i ] ? '^' : ' ' );
//   printf( "\n\n" ); // Extra blank line at the end.
// }

/** The validPattern() function checks to make sure the pattern is valid and returns
    true or false accordingly.

    @param pat is the given pattern to be validated.
    @return true if the pattern is valid. Otherwise, returns false.
 */
bool validPattern( char const pat[] )
{
  for ( int i = 0; i < strlen( pat ); i++ ) {
    if ( pat [ i ] == '*' ) {
      if ( pat [ i + 1 ] == '*' ) {
        return false;
      }
    }
  }
  return true;
}

/** The matchPattern() function compares the line of text to the pattern and returns
    true or false according to the congruency of the two parameters. 

    @param pat is the given pattern to match text with.
    @param line is the string being compared to the pattern.
    @return true if the string matches. Otherwise, returns false.
 */
bool matchPattern( char const pat[], char const line[] )
{

  int cur[ strlen(pat) + 1 ];
  int next[ strlen(pat) + 1 ];
  int n = sizeof(cur) / sizeof(cur[0]);

  for ( int i = 0; i < strlen(line); i++ ) {
    if ( !cur[i] ) continue;
    switch ( pat[i] ) {
      case '?':
        next[i + 1] = 1;
        break;
      case '*': 
        next[i] = 1;
        next[i + 1] = 1;
        break;
      default:
        if ( cur[i] == line[i] ) {
          next[i + 1] = 1;
          break;
        } else {
          return false;
        }
    }
    
    for ( int i = 0; i < n; i++ ) {
      cur[ i ] = next[ i ];
    }
  }
  return true;
}

