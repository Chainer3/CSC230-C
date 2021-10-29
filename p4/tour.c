/**
   @file tour.c
   @author Stephen Gonsalves (dkgonsal) w/ excerpts from Ex. 14 (Dr. Sturgill)
   
   The tour file houses the main function which is the starting point of the program. The main function
   will receive args from the user and call various functions based on the command received. It can
   build a list of destinations in the tour from an input file, as well as add and remove locations from 
   the tour, all while maintaining the total distance traveled for each destination on the tour.
 */

#include "map.h"
#include "input.h"

/** The last location in the tour */
static Location *loca;
/** The parameter of the command */
static char *par;
/** The last index of the tour list */
static int tCount;
/** The count of nearby locations */
static int nearCount;
/** The tour itinerary */
static Map *tour;


/* Print a usage message to standard error and exit unsuccessfully. 

   @author Dr. Sturgill
*/
static void usage()
{
  fprintf( stderr, "usage: tour <location-file>\n" );
  exit( 1 );
}

/* General-purpose function to complain about the input format (which
   shouldn't actualy happen when we're testing your code (but it's good
   to think about how you could handle this). 
    
   @author Dr. Sturgill
*/
static void invalidCommand()
{
  fprintf( stderr, "invalid command\n" );
  printf( "\ncmd> " );
}

/*The compareLoc() function receives two locations as parameters for comparison. It
  will return an integer value that indicates which location should come first.

  @param *va the first location in the comparison.
  @param *vb the second location in the comparison.
  @return the integer value of the comparison.
*/
int compareLoc( void const *va, void const *vb )
{
  Location *aLoc = *( ( Location ** ) va);
  Location *bLoc = *( ( Location ** ) vb);

  if ( strcmp( aLoc->name, bLoc->name ) == 0 ) {
    if ( strcmp( aLoc->country, bLoc->country ) < 0 ) {
      return -1;
    }
    if ( strcmp( aLoc->country, bLoc->country ) > 0 ) {
      return 1;
    }
  }
  return 0;
}

/*Compares two locations to the final tour location to find which location is nearest.

  @param *va the first location in the map.
  @param *vb the second location in the map.
  @return the lowest of the two locations.
*/
int compNearest( void const *va, void const *vb )
{
  Location *aLoc = *( ( Location ** ) va);
  Location *bLoc = *( ( Location ** ) vb);
  
  double a = distance( loca, aLoc );
  double b = distance( loca, bLoc );

  if ( a < b ) {
    return 1;
  }
  return -1;
  
}

/*Simple helper function that will always return true.

  @param *loc is the location being tested.
*/
bool testTrue( Location const *loc )
{
  return true;
}

/* Return the lower-case version of the given code.  There's a standard
   library function for this, but we haven't seen it yet.
   
   @param ch is the char to be converted to lower-case. 
*/
int toLower( int ch )
{
  if ( ch >= 'A' && ch <= 'Z' ) {
    return ch - 'A' + 'a';
  }
  return ch;
}

/* Boolean function that checks the location for a specific word parameter received
   in the list command.

   @param *loc is the location be
   @return true if the location name/country 
*/
bool testMatch( Location const *loc )
{
  int ch1, ch2, ch3;

  for ( int i = 0; i < strlen(par); i++) {
    ch1 = par[i];
    ch2 = loc->name[ i ];
    ch3 = loc->country[ i ];
    
    if ( toLower( ch1 ) != toLower( ch2 ) ) {
      if ( toLower( ch1 ) != toLower( ch3 ) ) {
        return false;
      } else {
        continue;
      }
    }
  }
  return true;
}

/* Tests to determine which location is the closes to the last location in the tour.
    
   @param *loc is the location being compared to the final location in the tour.
   @return true if it is not in the tour already. Otherwise, returns false.
*/
bool testInTour(  Location const *loc )
{

  for ( int i = 0; i < tour->count; i++ ) {
    if ( loc->id == tour->list[ i ]->id ) {
      return false;
    }
    
    if ( strlen( par ) > nearCount )
      nearCount++;
      return true;
  }
  return false;
}

/* This is the starting point of the program. Various functions of the program will be utilized based
   on the args received from the user. Ultimately, a tour itinerary will be built and listed in
   alphabetical order.
    
   @param argc is the number of args received in the terminal.
   @param argv is an array of args received in the terminal.
*/
int main( int argc, char *argv[] )
{
  
  // Error if invalid number args
  if ( argc < 2 ) {
    usage();
    exit( 1 );
  }
  
  int numFiles = argc - 1;
  char **allFiles = ( char **) malloc( numFiles * sizeof( char * ) );
  for ( int i = 1; i < argc; i++ ) {
    int n = strlen( argv[ i ] );
    allFiles[ i - 1 ] = ( char * ) malloc( n * sizeof( char ) + 1 );
    strcpy( allFiles[ i - 1 ], argv[i] );
  }

  Map *map = makeMap();
  tour = makeMap();
  
  for ( int i = 1; i < argc; i++ ) {
    readLocations( argv[ i ], map );
  }
  
  // Free the file memory
  for ( int i = 1; i < numFiles; i++ ) {
    free( allFiles[ i ] );
  }
  free( allFiles );
  
  
  char *cmd;
  tCount = 0;
  
  printf( "cmd> " );
  
  do {
    cmd = readLine( stdin );
    if (strlen( cmd ) > MAX_CMD_LEN + MAX_NAME_LEN + 1) {
      invalidCommand();
      printf("\ncmd> ");
    }
    char delimiter[] = " \n"; 
    int newID = 0;

    // list
    if (strcmp("list\0", cmd) == 0 ) {                      
      par = strtok( NULL, delimiter );
      int len = strlen(par);
        
      if ( par == NULL ) {
        listLocations( map, compareLoc, testTrue );
        continue;
      } else {
        if ( len > ( MAX_NAME_LEN + MAX_CMD_LEN + 1 ) ) {
          invalidCommand();
          printf("\ncmd> ");
        } else {
          listLocations( map, compareLoc, testMatch );
          continue;
        }
      }
    } else if ( strcmp( "nearest", cmd ) == 0 ) {                    
      par = strtok( NULL, delimiter );

      if ( newID < 0 || tCount == 0 || par == NULL || 
          (sscanf( par, "%d", &newID) != 1 )) {
        invalidCommand();
        printf("\ncmd> ");
        continue;
      }
        
      // Create a temp tour
      Map *temp = makeMap();
      temp->capacity = map->capacity;
      temp->count = map->count;
      temp->list = ( Location **) realloc( map->list, sizeof( Location *) * temp->capacity );

      loca = tour->list[ tCount ];
        
      for ( int i = 0; i < tCount; i++ ) {
        if ( !testInTour( map->list[ i ] ) ) {
          memcpy( temp->list[ temp->count++ ], map->list[ i ], sizeof( Location ) );
        }
        if ( temp->count == ( strlen(par) - 1 ) ||
           ( strlen(par) > map->count && i == map->count )) {
          continue;
        }
      }

      listLocations( temp, compNearest, testInTour );
      continue;
    } else if ( strcmp( "add", cmd ) == 0) {                    
      par = strtok( NULL, delimiter );
      if ( sscanf( par, "%d", &newID ) != 1 || par == NULL || 
        !( newID > 0 && newID < map->count + 1 ) ) {
        invalidCommand();
        printf("\ncmd> ");
        continue;
      }  
      for ( int i = 0; i < map->count; i++ ) {
        if ( tCount >= tour->capacity) {
          tour->capacity *= 2;
          tour->list = ( Location **) realloc( tour->list, sizeof(Location *) * tour->capacity );
        }
        if ( tour->list[ i ]->id == newID ) {
          memcpy( tour->list[ tCount++ ], map->list[ i ], sizeof( Location ) );
          break;
        } 

      }
      printf( "add %s\n", cmd );
    } else if ( strcmp( "remove", cmd ) == 0) {
      par = strtok( NULL, delimiter );
      if ( sscanf( par, "%d", &newID ) != 1 || par == NULL ) {
        invalidCommand();
        continue;
      }  
      bool isValCmd = false;
      for ( int i = 0; i < tCount; i++ ) {
        if ( tour->list[ i ]->id == newID ) {
          isValCmd = true;
          memcpy( tour->list[ i ], tour->list[ i + 1 ], sizeof( Location ) );
          tour->list[ tCount - 1 ] = NULL;
          tCount--;
          continue;
        }
      }
      if ( !isValCmd ) {
        invalidCommand();
        printf("\ncmd> ");
        continue;
      }   
    } else if (strcmp("tour\0", cmd) == 0 ) {
      par = strtok( NULL, delimiter );
      if ( par != NULL ) {
        invalidCommand();
        continue;
      }
  
      printf( "%s\n", cmd );
      printf( "%4s %-30s %-30s %8s\n", "ID", "Name", "Country", "Dist");
  
      double totDist = 0;
      for ( int i = 1; i < tCount; i++ ) {
        printf( "%4d %-30s %-30s %8.1f\n", tour->list[i]->id, tour->list[i]->name, 
                tour->list[i]->country, totDist );
        totDist += distance( tour->list[ i - 1 ], tour->list[ i ] );
      }
      printf("\n");
    } else if (strcmp("quit\n", cmd) == 0) {
      freeMap( map );
      freeMap( tour );
      free( cmd );
      return EXIT_SUCCESS;   
    } else {
      invalidCommand();
      printf("\ncmd> ");
      continue;
    }
      
  } while ( cmd != NULL );
  
  freeMap( map );
  freeMap( tour );
  free( cmd );
}

// int n = sizeof(list)/sizeof(Location*);
// qsort( list, n, sizeof( Location * ), strcmp());