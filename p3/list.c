/**
    @file list.c
    @author Stephen Gonsalves (dkgonsal)
    
    The list file handles the functions of adding to the list of matching lines
    and printing that list out when each respective function is called by match.c.
  */

#include "list.h"

/** The addLine() function adds a line of matching text to the matchList array.
    It also adds the line number of the matching text to the lineNum array.
     
    @param lno is the line number of the matching text.
    @param line is the string of matching text.
  */
void addLine( int lno, char const line[] ) 
{
  // Check if we've reach 1000 matched lines
  if ( idx > MAX_FILE_LINES ) {
    fprintf( stderr, "Too many matches\n");
  }
  
  // Handle case where line length >= Output Limit (80)
  if ( strlen(line) >= MAX_NUMS_LINE_LEN - 1) {
    char newLine[OUTPUT_LIMIT];
    char newLineNums[ MAX_NUMS_LINE_LEN ];
    for ( int i = 0; i < OUTPUT_LIMIT; i++ ) {
      if (i < MAX_NUMS_LINE_LEN - 1) {
        newLine[i] = line[i];
        newLineNums[i] = line[i];
      } else {
        newLine[i] = line[i];
      }
    }
    
    matchList[ idx ] = newLine;
    matchListNums[ idx ] = newLineNums;
    lineNum[ idx ] = lno;
    idx++;
  } else {
    // Add line/number to each array
    matchList[ idx ]= line;
    matchListNums[ idx ]= line;
    lineNum[ idx ] = lno;
    idx++;
  }
}

/**


  */
void printList( bool numberFlag )
{
//prints all the matching lines from the addLine() function
//if numberFlag == true, each line number is added to the front of each line
//line numbers require 3 spaces each regardless of # of digits
  int len = 0;
  if ( numberFlag ) {
    while ( len < idx ) {
      printf( "  %d %s", lineNum[len], matchListNums[len] );
      len++;
    }
  } else {
    while ( len < idx ) {
      printf( "%s", matchList[len] );
      len++;
    }  
  }
}