/**
    @file list.c
    @author Stephen Gonsalves (dkgonsal)
    
    The list file handles the functions of adding to the list of matching lines
    and printing that list out when each respective function is called by match.c.
  */

#include "list.h"

int idx = 0;
int maxLineNum = 0;
int lineNum[ MAX_FILE_LINES ];
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
  if ( maxLineNum < lno ) {
    maxLineNum = lno;
  }
  // Add the lno and line to their arrays
  lineNum[ idx ] = lno;
  strcpy( matchList[idx], line);
  idx++;
}

/**


  */
void printList( bool numberFlag )
{

  int prIdx = 0;
  while ( idx > prIdx ) {  
    if ( numberFlag ) {
      if ( strlen(matchList[prIdx]) > OUTPUT_LIMIT ) {
        printf( "%.3d %.74s..\n", lineNum[prIdx], matchList[prIdx] );     
      } else {
        printf( "%.3d %s\n", lineNum[prIdx], matchList[prIdx] );
      }
    } else {
      printf( "%.80s\n", matchList[prIdx] );
    }
    prIdx++;
  }
}