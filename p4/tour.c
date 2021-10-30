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
/** The string parameter of the command */
static char *par;
/** The last index of the tour list */
static int tCount = 0;
/** The count of nearby locations */
static int nearCount = 0;
/** The count of nearby locations */
static int upperNear = 0;
/** The tour itinerary */
static Map *tour;


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
    return strcmp( aLoc->country, bLoc->country );
  }
  return strcmp( aLoc->name, bLoc->name );
  
}

/*Simple helper function that will always return true.

  @param *loc is the location being tested.
*/
bool testTrue( Location const *loc )
{
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
  }
  if ( strlen( par ) > nearCount ) {
    nearCount++;
    return true;
  }
  return false;
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

  return (a - b);
  
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
    ch1 = par[ i ];
    ch2 = loc->name[ i ];
    ch3 = loc->country[ i ];
    
    if ( toLower( ch1 ) != toLower( ch2 ) ) {
      if ( toLower( ch1 ) != toLower( ch3 ) ) {
        return false;
      } else {
        continue;
      }
    } else {
      continue;
    }
  }
  return false;
}

/* This is the starting point of the program. Various functions of the program will be 
   utilized based on the args received from the user. Ultimately, a tour itinerary will 
   be built and listed in alphabetical order.
    
   @param argc is the number of args received in the terminal.
   @param argv is an array of args received in the terminal.
*/
int main( int argc, char *argv[] )
{
  // Error if invalid number args
  if ( argc < 2 || strcmp( "./tour", argv[ 0 ]) != 0 ) {
    fprintf( stderr, "usage: tour <location-file>\n" );
    exit( EXIT_FAILURE );
  }

  Map *map = makeMap();

//   int numFiles = argc - 1;
//   char **files = ( char **) malloc( numFiles * sizeof( char * ) );
//   for (int i = 1; i < argc; i++) {
//     int n = strlen(argv[ i ]);
//     files[i - 1] = ( char *) malloc( n * sizeof( char ) + 1 );
//     strcpy( files[ i - 1 ], argv[ i ] );
//   }
  
  for ( int i = 1; i < argc; i++ ) {
    readLocations( argv[ i ], map );
  }
  
  char *cmd;
  tCount = 0;
  tour = makeMap();
  
  do {
    printf( "cmd> " );
    cmd = readLine( stdin );
    
    // Invalid/NULL input checks
    if ( cmd == NULL ) {
      free( cmd );
      break;
    }
    
    // Begin checking commands
    char delimiter[] = " \n"; 
    char *par = strtok( cmd, delimiter );
    
    // Commands section
    // QUIT
    if ( strcmp("quit\n", cmd) == 0 ) {
      printf( "%s", cmd );
      freeMap( map );
      freeMap( tour );
      free( cmd );
      return EXIT_SUCCESS;   
    }
    
    // LIST
    else if ( strcmp( "list\0", cmd ) == 0 ) {                      
      par = strtok( NULL, delimiter );

      char *par2;
      if ( par != NULL ) {
        par2 = strtok( NULL, delimiter );
        if ( par2 != NULL || strlen( par ) > 4 || ( strcmp( " \0", par ) == 0 )) {
          printf( "list %s", par );
          while ( par2 != NULL ) {
            printf( " %s", par2 );
            par2 = strtok( NULL, delimiter );
          }
          printf( "\nInvalid command\n\n" );
          continue;
        }
      }

      if ( par == NULL ) {
        printf( "list\n" );
        listLocations( map, compareLoc, testTrue );
      } else {
        printf( "Invalid command\n" );
          printf( "\ncmd> " );
          continue;
      }
    }
    
    // ADD
    else if ( strcmp( "add", cmd ) == 0 ) {                    
      int intParam = 0;
      par = strtok( NULL, delimiter );
      
      if ( sscanf( par, "%d", &intParam ) != 1 || par == NULL || 
         ( intParam < 0 && intParam > map->count + 1 ) ) {
        printf( "invalid command\n" );
        continue;
      }
      
      printf( "add %s\n", par);
      if ( tCount >= tour->capacity) {
        tour->capacity *= CAP_RESIZE;
        tour->list = ( Location **) realloc( tour->list, sizeof(Location *) * tour->capacity );
      }
        
      for ( int i = 0; i < map->count; i++ ) {
        if ( map->list[ i ]->id == intParam ) {
          tour->list[ tCount ] = map->list[ i ];
          break;
        } 
      }
      tCount++;
      printf( "\n" );
    } 
    
    // REMOVE
    else if ( strcmp( "remove", cmd ) == 0 ) {
      int intParam = 0;
      bool inList = false;
      par = strtok( NULL, delimiter );
      
      if ( sscanf( par, "%d", &intParam ) != 1 || par == NULL ) {
        printf( "invalid command\n" );
        continue;
      }
      
      printf( "add %s\n", par);
      
      for ( int i = 0; i < tCount; i++ ) {
        if ( tour->list[ i ]->id == intParam ) {
          inList = true;
        
          for ( int j = i; j < tCount - 1; j++ ) {
            tour->list[ j ] = tour->list[ j + 1 ];
          }
          tCount--;
          printf( "\n" );
          continue;    
        }
      }

      if ( !inList ) {
        printf( "invalid command\n\n" );
        continue;
      }   
    } 
    
    // TOUR
    else if (strcmp("tour\0", cmd) == 0 ) {
      par = strtok( NULL, delimiter );
      if ( par != NULL ) {
      printf( "invalid command\n\n" );
        printf( "\ncmd> " );
        continue;
      }
  
      // Print command and tour header
      printf( "%s\n", cmd );
      printf( "%4s %-30s %-30s %8s\n", "ID", "Name", "Country", "Dist");
  
      double totDist = 0;
      for ( int i = 0; i < tCount; i++ ) {
        if ( i > 0 ) {        
          totDist += distance( tour->list[ i - 1 ], tour->list[ i ] );
        }
        printf( "%4d %-30s %-30s %8.1f\n", tour->list[ i ]->id, tour->list[ i ]->name, 
                tour->list[ i ]->country, totDist );
      }
      printf("\n");
    } 
        
    // NEAREST
    else if ( strcmp( "nearest", cmd ) == 0) {
      int intParam = 0;
      par = strtok( NULL, delimiter );
      if ( sscanf( cmd, "%d", &intParam) < 0 || par == NULL || tCount < 1 ) {
        printf( "invalid command\n\n" );
        printf( "\ncmd> " );
        continue;
      }

      upperNear = intParam;
      loca = tour->list[ tCount - 1 ];
      listLocations( map, compNearest, testInTour );
    } else {
      printf( "invalid command\n\n" );
      printf( "\ncmd> " );
      continue;
    }
    
    free( cmd );
      
  } while ( cmd != NULL );
  
  free( cmd );
  freeMap( map );
  freeMap( tour );
  
  return EXIT_SUCCESS;
}
