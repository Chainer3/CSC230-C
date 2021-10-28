/**
   @file tour.c
   @author Stephen Gonsalves (dkgonsal) w/ excerpts from Ex. 14 (Dr. Sturgill)
   
   The tour file houses the main function which is the starting point of the program. The main function
   will receive args from the user and call various functions based on the command received. It can
   build a list of destinations in the tour from an input file, as well as add and remove locations from 
   the tour, all while maintaining the total distance traveled for each destination on the tour.
 */

#include "map.h"
#include <math.h>

/* Print a usage message to standard error and exit unsuccessfully. 
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

/* Helper function that prints the header of the output that is printed to the terminal
   when a valid command is entered.
*/
void printHeader()
{
  printf( "%4s %-30s %-30s %5.1lf %5.1lf\n", "ID", "Name", "Country", "Lat", "Lon");
}

/*

*/
bool isInList( Location **arr, int left, int right, Location* loc ) {

    if ( right >= left ) {
        int middle = left + (right - 1) / 2;

        if ( arr[middle]->id == loc->id )
            return true;

        if ( arr[middle]->id > loc->id )
            return isInList( arr, left, middle - 1, loc );
        if ( arr[middle]->id < loc->id )
            return isInList( arr, middle + 1, right, loc );
    }

    return false;
}
/* The getCommand() function is another helper function that handles determining which
   command was received by the user. By using "strcmp", if a match is found, the
   corresponding char is returned.
   
   @param *command is the command received in the terminal.
   @return the corresponding letter to the matched command. If no match is found, 'z' is
           returned.
*/
char getCommand( char *command ) {
  if (strcmp("list\n", command) == 0 ) {
    return 'a';
  } else if (strcmp("list", command) == 0 ) {
    return 'b';
  } else if (strcmp("nearest", command) == 0 ) {
    return 'c';
  } else if (strcmp("add", command) == 0) {
    return 'd';
  } else if (strcmp("remove", command) == 0) {
    return 'e';
  } else if (strcmp("tour\n", command) == 0) {
    return 'f';
  } else if (strcmp("quit\n", command) == 0) {
    return 'g';
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
  
  // Error if 
  if ( argc < 2 ) {
    usage();
    exit( EXIT_FAILURE );
  }

  Map *map = makeMap();
  Map *tour = makeMap();
  
  for ( int i = 1; i < argc; i++ ) {
    readLocations( argv[ i ], map );
  }

  char *cmd;
  int tCount = 0;
  
  do {
    printf( "cmd> " );
    cmd = readLine( stdin );
    char delimiter[] = " \n";
    //char *cmd2 = strtok( cmd, delimiter );
    char ch = getCommand( cmd ); 
    int newID = 0;
    switch ( ch ) {
      case 'a':                        // list\n
        printf( "%s", cmd );
        printHeader();
        for ( int k = 0; k < map->count; k++ ) {
          printf( "%4d %30s %30s %6s %5s", tour->list[ k ]->id, tour->list[ k ]->name, 
                  tour->list[ k ]->country, tour->list[ k ]->latitude,
                  tour->list[ k ]->longitude);
        }
        break;
      case 'b':                        // list
        cmd = strtok( NULL, delimiter );
        int len = strlen(cmd);
        if ( len < 30 ) {
          printf( "%s", cmd );
          printHeader();
          for ( int i = 0; i < map->count; i++ ) {
            char *newCountry = char *strstr( cmd, map->list[ i ]->country);
            if ( newCountry != NULL ) {
              memcpy( tour->list[ i ], map->list[ i ], sizeof( Location ) );
            }
          }
          for ( int j = 0; j < map->count; j++ ) {
            char *newLoc = char *strstr( cmd, map->list[ j ]->name);
            if ( newLoc != NULL ) {
              memcpy( tour->list[ j ], map->list[ j ], sizeof( Location ) );
            }
          }
          for ( int k = 0; k < map->count; k++ ) {
            printf( "%4d %30s %30s %6s %5s", tour->list[ k ]->id, tour->list[ k ]->name, 
                    tour->list[ k ]->country, tour->list[ k ]->latitude,
                    tour->list[ k ]->longitude);
          }
        } else {
          invalidCommand();
        }
        break;
      case 'c':                        // nearest 
        //qsort( list, n, sizeof( Location * ), strcmp());
          break;
      case 'd':                        // add
        printf( "%s", cmd );
        if ( sscanf( input, "%d", newId ) ) {
           for ( int i = 0; i < map->count; i++ ) {
             if ( map->list[ i ]->id == newID ) {
              if ( tCount >= tour->capacity) {
                tour->capacity *= 2;
                tour->list = ( Location **) realloc( map->list, 
                                                   sizeof( Location *) * tour->capacity );
              }
              memcpy( tour->list[ tCount++ ], map->list[ i ], sizeof( Location ) );
             } else {
               continue;
             }
           }
        } else {
          invalidCommand();
        }
        break;    
      case 'e':                        // remove
        printf( "%s", cmd );
        if ( sscanf( input, "%d", newId ) ) {
           for ( int i = 0; i < tour->count; i++ ) {
             if ( tour->list[ i ]->id == newID ) {
               for ( int j = i; j < map->count; j++ ) {
                 Location *next = tour->list[ j + 1 ];
                 free( tour->list[ j ] );
                 tour->list[ j ] = next;
               }
               tCount--;
             } else {
               continue;
             } 
          }
        } else {
          invalidCommand(); 
        }      
        break;  
      case 'f':                        // tour\n
        
        break;
      case 'g':                        // quit\n
        return EXIT_SUCCESS;
        break;    
      default:
        invalidCommand();
        break;     
    }
  } while ( cmd != NULL );
  
  freeMap( map );
  freeMap( tour );
}

// int n = sizeof(list)/sizeof(Location*);
// qsort( list, n, sizeof( Location * ), strcmp());