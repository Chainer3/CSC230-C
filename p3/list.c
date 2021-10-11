/**
    @file list.c
    @author Stephen Gonsalves (dkgonsal)
    
    
  */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** The addLine() function adds a line of matching text to the matchList array.
    It also adds the line number of the matching text to the lineNum array.
     
    @param lno is the line number of the matching text.
    @param line is the string of matching text.
  */
void addLine( int lno, char const line[] ) 
{
//lno is the line number of the match
//line is the line of matching text
//both are added to the list in this method
  idx++;
  for ( int i = 0; i < strlen( line ); i++ ) {
    matchLine[ idx ][ i ] = line[ i ];
    matchList[ idx ][ i ] = line[ i ];
  }
  
  lineNum[ idx ] = lno;

}

/**


  */
void printList( bool numberFlag )
{
//prints all the matching lines from the addLine() function
//if numberFlag == true, each line number is added to the front of each line
//line numbers require 3 spaces each regardless of # of digits
  int len = idx;
  if ( numberFlag ) {
    while ( (idx - len) < idx ) {
      printf("  %d %s", &lineNum[(idx - len)], &matchLine[(idx - len)][] );
      len--;
    }
  } else {
    while ( (idx - len) < idx ) {
      printf("%s", &matchLine );
      len--;
    }  
  }
}