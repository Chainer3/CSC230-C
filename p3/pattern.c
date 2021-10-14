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
  int p = strlen( pat );
  for ( int i = 0; i < p; i++ ) {
    if ( pat[ i ] == '*' ) {
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
  int l = strlen(line);
  int p = strlen(pat);
  bool match = NULL;
  bool cur[ strlen(pat) + 1 ];
  memset(cur, 0, sizeof(bool)* (p + 1));
  bool next[ strlen(pat) + 1 ];
  memset(cur, 0, sizeof(bool)* (p + 1));

  cur[0] = true;
  if( p > 0 && pat[0] == '*') {
    cur[1] = true;
  }
  // Iterate through the list
  for ( int i = 0; i < l; i++ ) {
    char ch = line[i];
    match = false;
    // Iterate through the pattern
    for ( int j = 0; j < p; j++ ) {
      
      // Check if current we've transitioned states
      if ( !cur[ j ] ) continue;
      switch ( pat[ j ] ) {
        case '?':
          next[ j + 1 ] = true;
          if ( j + 1 < p && pat[ j + 1 ] == '*' ) {
            next[ j + 2 ] = true;
          }
          match = true;
          break;
        case '*':
          next[ j ] = true;
          next[ j + 1 ] = true;
          match = true;
          break;
        default:
          if ( pat[ j ] == ch ) {
            next[ j + 1 ] = true;
            if ( j + 1 < p && pat[ j + 1 ] == '*' ) {
              next[ j + 2 ] = true;
            }
          }
          match = true;
          break;
      }
    }
    if (!match) {
      return false;
    }
    // Copy the next arr in cur arr
    memcpy( cur, next, p + 1);
    memset(next, 0, sizeof(bool) * (p + 1));
  }
  
  // Check results and return appropriate bool
  if ( cur[p] ) {
    return true;
  }
  if (pat[p - 1] == '*' ) {
    return cur[p - 1];
  }
  return false;
  
}

