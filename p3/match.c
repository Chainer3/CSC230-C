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

#define INPUT_LIMIT 1023

/* This is the starting point of the program. Here, the main function will
   receive command line args for searching a valid input file line-by-line
   for the matching string structure.

   @param argc is the number of arguments input at the command line
   @param argv is the array of arguments input at the command line
 */
int main ( int argc, char *argv[] )
{
  
  // Initialize pattern and flags for printing
  bool lineNums = NULL;
  bool opp = NULL;


  // Check args in flag section
  for ( int i = argc - 3; i >= 1; i-- ) {
    if ( strcmp(argv[i], "-n") == 0 ) {
      lineNums = true;
    } else if ( strcmp(argv[i], "-v") == 0 ) {
      opp = true;
    } else {
      fprintf( stderr, "usage: match [-n] [-v] pattern file\n" );
      exit( 1 );
    }
  }
  
  // Check pattern and file args for flags
  if ( strcmp(argv[argc - 2], "-n") == 0 || strcmp(argv[argc - 2], "-v") == 0 ||
       strcmp(argv[argc - 1], "-n") == 0 || strcmp(argv[argc - 1], "-v") == 0 ) {
    fprintf( stderr, "usage: match [-n] [-v] pattern file\n" );
    exit( 1 );  
  }



  
  // Find valid file and open FileStream for reading only
  char *fileName = argv[ argc - 1 ];
  char *pat = argv[ argc - 2 ];
  FILE *fp = fopen( fileName, "r");
  if ( !fp ) {
    fprintf(stderr, "%s%s\n", "Can't open file: ", fileName);
    exit( 1 );
  }
  
  // Create line array and read each line in the file for comparison
  char line[ INPUT_LIMIT ];
  int lno = 1;
  
  // Validate pattern and begin matching/adding to matchList
  if ( validPattern(pat) ) {
    while ( readLine(fp, line, INPUT_LIMIT) ) {
      if ( opp ) {
        if ( !matchPattern(pat, line) ) {
          addLine(lno, line);
        }
      } else {
        if ( matchPattern(pat, line) ) {
          addLine(lno, line);
        }
      }
      lno++;
    }
      
    printList(lineNums);
    fclose(fp);
  
  } else {
    fclose(fp);
    fprintf( stderr, "Invalid pattern: %s\n", argv[argc - 2]);
    exit( 1 );
  }
  
  // Exit successfully
  return EXIT_SUCCESS;

}