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
static char par[ MAX_NAME_LEN ];
/** The last index of the tour list */
static int tCount;

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
int *compareLoc( void const *va, void const *vb )
{
  Location *aLoc = *( ( Location ** ) va);
  Location *bLoc = *( ( Location ** ) vb);

  if ( strcmp( aLoc->name, bLoc->name ) == 0 ) {
    return strcmp( aLoc->country, bLoc->country);
  }

/*Compares two locations to the final tour location to find which location is nearest.

  @param *va the first location in the map.
  @param *vb the second location in the map.
  @return the lowest of the two locations.
*/
int *testNearest( void const *va, void const *vb )
{
  Location *aLoc = *( ( Location ** ) va);
  Location *bLoc = *( ( Location ** ) vb);
  
  double a = distance( loca, aLoc );
  double b = distance( loca, bLoc );

  if ( a < b ) {
    return -1;
  }
  if ( a > b ) {
    return 1;
  }
}

/*Simple helper function that will always return true.

  @param *loc is the location being tested.
*/
bool testTrue( Locations const *loc )
{
  return true;
}

/*

*/
bool testMatch( Locations const *loc )
{
  int ch;
  char word[ MAX_NAME_LEN ];
  char temp[ MAX_NAME_LEN ];
  
  for ( int i = 0; i < strlen(par); i++) {
    ch = par[i];
    word[ i ] = toLower( ch );
    temp[ i ] = toLower( ch );
  }
  
  if ( strcmp( word, temp ) == 0 ) {
    return true;
  }
  return false;
}

/*

*/
bool testInTour( Map *map, void const *vb )
{
  Location *loc = *( ( Location ** ) vb);

  for ( int i = 0; i < map->count; i++ ) {
    if ( compareLoc( map->list[ i ], tour->list[ j ] ) == 0) {
      return true;
    }
  }
  return false;
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

/*The getCommand() function is another helper function that handles determining which
  command was received by the user. By using "strcmp", if a match is found, the
  corresponding char is returned.
   
  @param *command is the command received in the terminal.
  @return the corresponding letter to the matched command. If no match is found, 'z' is
           returned.
*/
static char getCommand( char *command ) {
  if (strcmp("list\0", command) == 0 ) {
    return 'a';
  } else if (strcmp("nearest", command) == 0 ) {
    return 'b';
  } else if (strcmp("add", command) == 0) {
    return 'c';
  } else if (strcmp("remove", command) == 0) {
    return 'd';
  } else if (strcmp("tour\n", command) == 0) {
    return 'e';
  } else if (strcmp("quit\n", command) == 0) {
    return 'f';
  } else {
    return 'z';
  }
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
    allFiles[ i - 1 ] = ( char * ) malloc( size * sizeof( char ) + 1 );
    strcpy( allFiles[ i - 1 ], argv[i] );
  }

  Map *map = makeMap();
  Map *tour = makeMap();
  
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
    if (strlen( cmd ) > MAX_CMD + MAX_NAME_LEN + 1) {
      invalidCommand();
      printf( "cmd> " );
    }
    char delimiter[] = " \n"; 
    char *cmd2 = strtok( cmd, delimiter );
    
    int cmds[ 2 ] = {getCommand( cmd ), getCommand( cmd2 )};
    int newID = 0;
   
    switch ( cmds[ i ] ) {
      // list
      case 'a':                        
        cmd2 = strtok( NULL, delimiter );
        int len = strlen(cmd2);
        
        if ( cmd2 == NULL ) {
          printf( "add %s\n", cmd );
          listLocations( map, compareID, test );
          break;
        }
        if ( len < 30 ) {
          printf( "%s %s", cmd, cmd2 );
          printf( "%4s %-30s %-30s %5.1lf %6.1lf\n", "ID", "Name", "Country", "Lat", "Lon");
          for ( int i = 0; i < map->count; i++ ) {
            int *newCountry;
            for ( int i = 0; i < len; i++ ) {
              newCountry[ i ] = toLower( map->list[ i ]->country );
            }  
            if ( newCountry != NULL ) {
              memcpy( tour->list[ i ], map->list[ i ], sizeof( Location ) );
            }
          }
          
          for ( int j = 0; j < map->count; j++ ) {
            char *newLoc = toLower( map->list[ j ]->name );
            if ( newLoc != NULL ) {
              memcpy( tour->list[ j ], map->list[ j ], sizeof( Location ) );
            }
          }
          for ( int k = 0; k < map->count; k++ ) {
            Location *temp = map->list[ k ];
            listLocations( *map, *compareName( cmd, void const *vb ), *testListPlus( *temp ) );
          }
        } else {
          invalidCommand();
        }
        break;
      
      // nearest
      case 'b':                        
        cmd2 = strtok( Null, delimiter );
        testInTour( map-list, tour-list[ i ] );
        for ( int i = 0; i < cmd2; i++ ) {
          testInTour( map->list, tour->list[ i ] );
        }
        if ( id < 0 || tCount == 0 || cmd2 == NULL || (sscanf( cmd2, "%d", &id) != 1 )) {
          invalidCommand();
          break;
        }
        
        // Create a temp tour
        Map *temp = makeMap();
        temp->capacity = map->capacity;
        temp->count = map->count;
        temp->list = ( Location *) realloc( map->list, sizeof( Location *) * temp->capacity );

        loca = tour-list[ tCount ];
        
        
        for ( int i = 0; i < tCount, i++ ) {
          if ( !isInTour( map, tour->list[ i ] ) ) {
            memcpy( temp->list[ temp->count++ ], map->list[ i ], sizeof( Location ) );
          }
          if ( ( temp->count == ( cmd2 - 1 ) ||  
                (cmd2 > map->count && i == map->count ) {
            break;
          }
        }
        
        int dist1[cmd2];
        int dist2[cmd2];
        int d = 0;
//         int len = sizeof( dist ) / sizeof( int )[]
        for ( int i = 0; i < temp->count; i++ ) {
          d = distance( temp->list[ i ], tour->list[ tCount ] );
          dist1[ i ] = d;
          dist2[ i ] = d;
        }
        qsort( dist1, cmd2, sizeof( int ), compareID );
 
        listLocations( temp, compareDistance(tour->list[ tCount ], ), test );
        break;
      
      // add
      case 'c':                        
        cmd2 = strtok( Null, delimiter );
        if ( sscanf( cmd2, "%d", &newID ) != 1 || cmd2 == NULL || 
             !( id > 0 && id < map->count + 1 ) ) {
          invalidCommand();
          break;
        }  
        for ( int i = 0; i < map->count; i++ ) {
          if ( tCount >= tour->capacity) {
            tour->capacity *= 2;
            tour = ( Location **) realloc( tour, sizeof( Location *) * tour->capacity );
          }
          if ( tour->list[ i ]->id == newID ) {
            memcpy( tour->list[ tCount++ ], map->list[ i ], sizeof( Location ) );
            break;
          } 

        }
        printf( "add %s\n", cmd );
        break;    
        
      // remove
      case 'd':
        cmd2 = strtok( Null, delimiter );
        if ( sscanf( cmd2, "%d", &newID ) != 1 || cmd2 == NULL ) {
          invalidCommand();
          break;
        }
        
        bool isValCmd = false;
        for ( int i = 0; i < tCount; i++ ) {
          if ( tour->list[ i ]->id == newID ) {
            isValCmd = true;
            memcpy( tour->list[ i ], tour->list[ i + 1 ], sizeof( Location ) );
            tour->list[ tCount - 1 ] = NULL;
            tCount--;
            break;
          }
        }
        if ( !isValCmd ) {
          invalidCommand();
          break;
        } 
        break;
      
      // tour
      case 'e':
        cmd2 = strtok( Null, delimiter );
        if ( cmd2 != NULL ) {
          invalidCommand();
        }
        
        printf( "%s\n", cmd );
        printf( "%4s %-30s %-30s %8s\n", "ID", "Name", "Country", "Lat", "Lon");
        
        double totDist = 0;
        for ( int = 0; i < tCount; i++ ) {
          printf( "%4d %-30s %-30s %8.1f\n", tour[i]->id, tour[i]->name, 
                  tour[i]->country, totDist );
          totDist += distance( tour->list[ i ], tour->list[ i + 1 ] );
        }
        break;
      
      // quit
      case 'f':
        freeMap( map );
        freeMap( tour );
        free( cmd );
        return EXIT_SUCCESS;   
      
      // Base case
      default:
        invalidCommand();
        break;     
    }
  } while ( cmd != NULL );
  
  freeMap( map );
  freeMap( tour );
  free( cmd );
}

// int n = sizeof(list)/sizeof(Location*);
// qsort( list, n, sizeof( Location * ), strcmp());