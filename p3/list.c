/**
    @file list.c
    @author Stephen Gonsalves (dkgonsal)
    
    The list file handles the functions of adding to the list of matching lines
    and printing that list out when each respective function is called by match.c.
  */

#include "list.h"

/** Limit of line printed if line # is included */
#define PRINT_LIMIT 78

/** Limit of line printed if line # is included */
#define DIGITS 10

/** Current index in the matchList array */
int idx = 0;

/** Array that holds the line numbers of matches */
int lineNum[ MAX_FILE_LINES ];

/** Array that holds the list of matches */
char matchList[ MAX_FILE_LINES ][ INPUT_LIMIT + 1 ];

/** The addLine() function adds a line of matching text to the matchList array.
    It also adds the line number of the matching text to the lineNum array.
     
    @param lno is the line number of the matching text.
    @param line is the string of matching text.
  */
void addLine( int lno, char const line[] ) 
{
  // Check if we've reach 1000 matched lines
  if ( idx == MAX_FILE_LINES + 1 ) {
    fprintf( stderr, "Too many matches\n");
    exit ( 1 );
  }

  // Add the lno and line to their arrays
  lineNum[ idx ] = lno;
  strcpy( matchList[idx], line);
  idx++;
}

/** The printList() function is responsible for printing the list of matches. It 
    receives a boolean variable as its parameter, which determines if the line
    numbers will be printed as well. If true, the matchList lines will have to be
    altered to facilitate an 80 character or less requirement for printout.
    
    @param numberFlag dictates line number inclusion in the printout. If false, line
           numbers will not be printed.
  */
void printList( bool numberFlag )
{
  int max = lineNum[ idx - 1 ];

  // Find number of digits
  int count = 0;
  int n = 0;
  while (max != 0) {
    n = max % DIGITS;
    max = max - n;
    max = max / DIGITS;
    count++;
  }
  max = count;

  int prIdx = 0;
  while ( idx > prIdx ) {  
    if ( numberFlag ) {
      printf( "%*d ", max, lineNum[prIdx] ); 
      if ( strlen(matchList[prIdx]) >= OUTPUT_LIMIT - max ) {
        printf("%.*s..\n", PRINT_LIMIT - (max + 1), matchList[prIdx]);
      } else {
        printf( "%s\n", matchList[prIdx] );
      }
    } else if ( strlen(matchList[prIdx]) > OUTPUT_LIMIT ) {
      printf("%.*s..\n", PRINT_LIMIT, matchList[prIdx]);
    } else {
      printf( "%s\n", matchList[prIdx] );
    }
    prIdx++;
  }
}