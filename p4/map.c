/**
   @file map.c
   @author Stephen Gonsalves (dkgonsal) w/ excerpts from Ex. 14 (Dr. Sturgill)
   
   The map file
 */

#include "map.h"
#include "input.h"
#include <math.h>

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
  double aLat = a->lat;
  double aLon = a->lon;
  
  // Coordinates of Location b
  double bLat = b->lat;
  double bLon = b->lon;

  
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
  
  // Compute the angle between the vectors based on the dot product.
  double angle = acos( dp );

  // Return distance based on the radius of the earth.
  return EARTH_RADIUS * angle;
}

/* 
*/
Map *makeMap() {
  Map *currentMap = (Map *) malloc( sizeof(Map) );

  // Map's list of locations
  Location **locList = ( Location **) malloc( INIT_CAPACITY * sizeof( Location* ));
  
  currentMap->list = locList;
  currentMap->capacity = INIT_CAPACITY;
  curentMap->count = 0;
  return currentMap;
}

/* The freeMap() function frees up the allocated memory being utilized by the
   map parameter.
  
  @param *map is the map struct that is taking up memory
*/
void freeMap( Map *map )
{
  for ( int i = 0; i < map->capacity; i++ ) {
    Location *n = map->list[ i ]->list;
    free( map->list );
    map->list = n;
  }
  free( map );
  map = NULL;
}

/*

  @param filename
  @param map
*/
void readLocations( char const *filename, Map *map )
{
  // Open the given file.
  FILE *fp = fopen( filename, "r" );
  if ( !fp ) {
    fprintf( stderr, "Can't open file: %s\n", filename );
    exit( 1 ); 
  }
  
  Location *loc = ( Location *) malloc( sizeof(Location) );
  char newName[MAX_NAME_LEN];
  char newCountry[MAX_NAME_LEN];
  double newLat[5];
  double newLon[6];
    
  while ( location = readLine( fp ) ) { 
   
    if ( sscanf( location, "%[^\t] %[^\t] %lf%lf", newName, newCountry, &newLat, &newLon) != 4 ) {
      fprintf( stderr, "Invalid location file: %s\n", filename );
      exit( 1 );
    }
    
    bool isDuplicate = false;
    for ( int i = 0; i < map->count; i++ ) {
      if ( (strcmp(map->list[i]->name, newName) == 0 &&
            strcmp( map->list[i]->country, newCountry) == 0) &&
            (map->list[i]->lat != newLat && map->list[i]->lon != newLon) ) {
        fprintf( stderr, "Inconsistent location" );
        exit(1);
      } else if ((strcmp(map->list[i], newName) == 0 && 
                  strcmp( map->list[i]->country, newCountry) == 0)) &&
                  (map->list[i]->lat == newLat && map->list[i]->lon == newLon) ) {
        isDuplicate = true
        break;
      }
    }
    
    // Start over if the location is a duplicate
    if ( isDuplicate ) {
      free( loc );
      continue;
    }
    
    loc.id = map->++count;
    strcpy( loc.name, newName);
    strcpy( loc.country, newCountry);
    loc.lat = newLat;
    loc.lon = newLon;
    if ( map->count >= map->capacity ) {
      map->capacity *= 2;
      map->list = ( Location **) realloc( map->list, sizeof( Location *) * map->capacity );
    }
    
    map->list[ map->count - 1 ] = loc;
}

/*

  @param map
  @param (*compare)( void const *va, void const *vb )
  @param (*test)( Location const *loc )
*/
void listLocations( Map *map, int (*compare)( void const *va, void const *vb ),
                    bool (*test)( Location const *loc ) )
{
  qsort( map->list, map->count, sizeof(Location *), compare);
  printf( "%4s %-30s %-30s %5.1lf %6.1lf\n", "ID", "Name", "Country", "Lat", "Lon");

  for (int i = 0; i < map->count; i++ ) {
    if ( test( map->list[ i ] ) ) {
      printf( "%4s %-30s %-30s %5.1lf %6.1lf\n", map->list[ i ]->id, map->list[ i ]->name,
            map->list[ i ]->country, map->list[ i ]->latitude, map->list[ i ]->longitude); 
    }
  }
}

