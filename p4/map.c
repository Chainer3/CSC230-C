/**
   @file map.c
   @author Stephen Gonsalves (dkgonsal) w/ excerpts from Ex. 14 (Dr. Sturgill)
   
   The map file
 */

#include <math.h>
#include "map.h"
#include "input.h"

/** Multiplier for converting degrees to radians */
#define DEG_TO_RAD ( M_PI / 180 )
/** Radius of the earth in miles. */
#define EARTH_RADIUS 3959.0


/* Calculates the distance between two locations and returns it as a double value.

  @author Dr. David Sturgill
  @param *a is the first location.
  @param *b is the second location.
  @return the distance between the two locations.
*/
double distance( Location const *a, Location const *b )
{
  // Coordinates of Location a
  double aLat = a->latitude;
  double aLon = a->longitude;
  
  // Coordinates of Location b
  double bLat = b->latitude;
  double bLon = b->longitude;
  
  
  if ( (aLat == bLat) && (aLon == bLon) ) {
    return 0;
  }

  
  // OK, pretend the center of the earth is at the origin, turn these
  // two locations into vectors pointing from the origin.
  // This could be simplified.
  double v1[] = { cos( aLon * DEG_TO_RAD ) * cos( aLat * DEG_TO_RAD ),
                  sin( aLon * DEG_TO_RAD ) * cos( aLat * DEG_TO_RAD ),
                  sin( aLat * DEG_TO_RAD ) };

  double v2[] = { cos( bLon * DEG_TO_RAD ) * cos( bLat * DEG_TO_RAD ),
                  sin( bLon * DEG_TO_RAD ) * cos( bLon * DEG_TO_RAD ),
                  sin( bLat * DEG_TO_RAD ) };

  // Dot product these two vectors.
  double dp = 0.0;
  int n = sizeof( v1 ) / sizeof( v1[ 0 ] );
  for ( int i = 0; i < n; i++ ) {
    dp += v1[ i ] * v2[ i ];
  }
  // Compute the angle between the vectors based on the dot product.
  double angle = acos( dp );

  // Return distance based on the radius of the earth.
  return EARTH_RADIUS * angle;
}

/* Creates the map structure with a nested list structure to hold all of the
   locations in the map.
   
   @return a newly created map structure.
*/
Map *makeMap() {
  // Create the map struct
  Map *currentMap = (Map *) malloc( sizeof(Map) );

  // Map's list of locations
  Location **locList = ( Location **) malloc( INIT_CAPACITY * sizeof( Location* ));
  
  currentMap->list = locList;
  currentMap->capacity = INIT_CAPACITY;
  currentMap->count = 0;
  return currentMap;
}

/* The freeMap() function frees up the allocated memory being utilized by the
   map parameter.
  
   @param *map is the map struct that is taking up memory
*/
void freeMap( Map *map )
{
  for ( int i = 0; i < map->capacity; i++ ) {
    free( map->list[ i ] );
  }
  free( map );
  map = NULL;
}

/* The readLocations() function receives a file pointer and map as it's parameters. It's
   job is to read a valid file and create a Location structure out of each line of
   text in the file.

   @param filename is the file to be read for Location creation.
   @param map the each location will be stored in.
*/
void readLocations( char const *filename, Map *map )
{
  // Open the given file.
  FILE *fp = fopen( filename, "r" );
  if ( !fp ) {
    fprintf( stderr, "Can't open file: %s\n", filename );
    exit( 1 ); 
  }
  
  char *line;
  Location *loc = ( Location *) malloc( sizeof(Location) );
    
  line = readLine( fp );
  while ( line ) { 
    if ( sscanf( line, "%[^\t] %[^\t] %lf%lf", loc->name, loc->country, &loc->latitude, 
         &loc->longitude) != 4 ) {
      free( loc );
      free( line );
      fprintf( stderr, "Invalid location file: %s\n", filename );
      exit( 1 );
    }
    
    bool isDuplicate = false;
    for ( int i = 0; i < map->count; i++ ) {
      if ( ( strcmp( map->list[i]->name, loc->name ) == 0 ) &&
            ( strcmp( map->list[i]->country, loc->country ) == 0 ) ) {
        if ( ( map->list[i]->latitude != loc->latitude ) && 
             ( map->list[i]->longitude != loc->longitude ) ) {
          free( loc );
          free( line );
          fclose( fp );
          fprintf( stderr, "%s\n", "Inconsistent location" );
          exit( 1 );
        } else {
          isDuplicate = true;
          break;
        }
      }
    }
    
    // Start over if the location is a duplicate
    if ( isDuplicate ) {
      free( loc );
      free( line );
      continue;
    }
    
    if ( map->count >= map->capacity ) {
      map->capacity *= CAP_RESIZE;
      map->list = ( Location **) realloc( map->list, sizeof( Location *) * map->capacity );
    }
    
    loc->id = map->count + 1;
    map->list[ map->count++ ] = loc;
  }
  free( line );
  free( loc );
  fclose( fp );
}

/* The listLocations() function receives a map, a compare function and a test as its
   parameters. This function utilizes qsort() to sort the list by the determined field
   and prints the results if the test parameter returns true.

   @param map is the map contents to be sorted/printed.
   @param *compare is the compare function for sorting.
   @param *test is the test used to determine if the map list should be printed.
*/
void listLocations( Map *map, int (*compare)( void const *va, void const *vb ),
                    bool (*test)( Location const *loc ) )
{
  qsort( map->list, map->count, sizeof(Location *), compare);
  printf( "%4s %-30s %-30s %5s %6s\n", "ID", "Name", "Country", "Lat", "Lon");

  for ( int i = 0; i < map->count; i++ ) {
    if ( test( map->list[ i ] ) ) {
      printf( "%4d %-30s %-30s %5.1f %6.1f\n", map->list[ i ]->id, map->list[ i ]->name,
            map->list[ i ]->country, map->list[ i ]->latitude, map->list[ i ]->longitude); 
    }
  }
  printf( "\n" );
  
}

