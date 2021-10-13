/**
   @file match.c
   @author Stephen Gonsalves (dkgonsal)

    The match file is the centerpiece of the program structure. It houses
    the main method that reaches out to the other files to accomplish reading
    a valid file and matching strings from command line arguments.
  */

#include "input.h"
#include "list.h"
#include "pattern.h"

#define MAX_LINE_LEN 1024

/* This is the starting point of the program. Here, the main function will
   receive command line args for searching a valid input file line-by-line
   for the matching string structure.

   @param argc is the number of arguments input at the command line
   @param argv is the array of arguments input at the command line
 */
int main ( int argc, char *argv[] )
{
  
  // Initialize pattern and flags for printing
  bool lineNums = false;
  bool opp = false;
  char *pat = argv[ argc - 2 ];

  // Check args in flag section
  for ( int i = 1; i < (argc - 2); i++ ) {
    if ( strcmp(argv[i], "-n") ) {
      lineNums = true;
    } else if ( strcmp(argv[i], "-v") ) {
      opp = true;
    } else {
     fprintf( stderr, "usage: match [-n] [-v] pattern file" );
     exit( 1 );
    }
  }
  
  // Check pattern and file args for flags
  if ( strcmp(argv[argc - 2], "-n") || strcmp(argv[argc - 2], "-v") ) {
    fprintf( stderr, "usage: match [-n] [-v] pattern file" );
    exit( 1 );  
  }
  if ( strcmp(argv[argc - 1], "-n") || strcmp(argv[argc - 1], "-v") ) {
    fprintf( stderr, "usage: match [-n] [-v] pattern file" );
    exit( 1 );
  }

  // Find valid file and open FileStream for reading only
  char *fileName = argv[ argc - 1 ];
  FILE *fp = fopen( fileName, "r");
  if ( !fp ) {
    fprintf(stderr, "%s%s\n", "Can't open file: ", fileName);
    exit( 1 );
  }
  
  // Create pattern and read each line in the file for comparison
  char line[MAX_LINE_LEN];
  int lno = 1;
  
  // Validate pattern and begin matching/adding to matchList
  if ( validPattern(pat) ) {
    if ( opp ) {
      while ( readLine(fp, line, MAX_LINE_LEN) ) {
        if ( !matchPattern(pat, line) ) {
          addLine(lno, line);
        }
      }
    } else {
      while ( readLine(fp, line, MAX_LINE_LEN) ) {
        if ( matchPattern(pat, line) ) {
          addLine(lno, line);
        }
      }
    }
  }
  
  printList(lineNums);

  fclose(fp);
  fp = NULL;
  return EXIT_SUCCESS;

}