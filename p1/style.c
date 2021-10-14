/**
   @file style.c
   @author Stephen Gonsalves (dkgonsal)
   This program uses an random number generator (rng) to print a paragraph of 
   random strings comprised only of lower-case letters. It will print the total
   word count once the paragraph's line limit (10) has been reached.
*/

#include <stdio.h>
#include <stdlib.h>

/** Character limit for each line */
#define CHARLIMIT 72
/** Min ASCII value of a lower-case letter */
#define LC_MIN 97
/** Value added to LC_MIN to reach max ASCII value of lower-case letter */
#define LC_MAX 26
/**  Line limit for each paragraph */
#define PARA_LINE_LIM 10

/** The printWord() method receives an integer value x as a parameter and
    prints an amount of random lower-case letters equivalent to x.
    @param x is the integer amount of random lower-case letters to print.
  */
void printWord( int x )
{
  for ( int i = 0; i < x; i++ ) {
    // Print a random lower-case letter.
    printf( "%c", LC_MIN + rand() % LC_MAX );
  }
}

/** The printLine() method prints a single line of text that falls within the
    character limit of a line in the paragraph
    @return the line count for tracking in the printParagraph() method.
  */
int printLine()
{
  int count = 0, pos = 0, space = 0;
  int len = 1 + rand() % PARA_LINE_LIM;

  // Print a line of words up to a limited length.
  while ( pos + len + space < CHARLIMIT ) {
    if ( space > 0 ) {
      printf( " " );
    }
    
	printWord( len );
	pos += len + space;
	len = 1 + rand() % PARA_LINE_LIM;
	space = 1;
	count += 1;
  }
	printf( "\n" );
	return count;
}

/** This method tracks the word count while it calls the printLine() method on 
    each iteration of the for loop.
    @param n int value received from main() method used to dictate the number of
             lines in a paragraph 
    @returns the total number of words in the printed paragraph.
  */
int printParagraph( int n )
{
  int total = 0;
  
  // Print n lines to the paragraph
  for ( int i = 0; i < n; i++ ) {
    total += printLine();
  }

  return total;
}

/** Starting point of the program. The main method calls the printParagraph() method
    to build a paragraph of random strings of lower-case characters. It will then 
    print the word count received in the variable w.
    @return a 0 representing successful termination of the program.
  */
int main()
{
  // Calls the printParagraph method with the defined constant
  int w = printParagraph(PARA_LINE_LIM);
  printf("Words: %d\n", w);

  //Exit successfully
  return EXIT_SUCCESS;
  
}