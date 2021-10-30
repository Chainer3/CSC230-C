#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/** Max length of a location name */
# define MAX_NAME_LEN 32
/** Max output length */
# define OUTPUT_LEN 79
/** Initial map capacity */
# define INIT_CAPACITY 5
/** Max length of a command */
# define MAX_CMD_LEN 7
/** Resize the capacity of the map */
# define CAP_RESIZE 2
/** Multiplier for converting degrees to radians */
#define DEG_TO_RAD ( M_PI / 180 )
/** Radius of the earth in miles. */
#define EARTH_RADIUS 3959.0
/** Maximum range of latitude */
#define MAX_LAT 90
/** Maximum range of longitude */
#define MAX_LON 180

typedef struct
{
    int id;
    char name[ MAX_NAME_LEN + 1 ];
    char country[ MAX_NAME_LEN + 1 ];
    double latitude, longitude;
} Location;

typedef struct
{
    Location **list;
    int count;
    int capacity;
} Map;

/* Calculates the distance between two locations and returns it as a double value.

  @author Dr. David Sturgill
  @param *a is the first location.
  @param *b is the second location.
  @return the distance between the two locations.
*/
double distance( Location const *a, Location const *b );

/* Creates the map structure with a nested list structure to hold all of the
   locations in the map.
   
   @return a newly created map structure.
*/
Map *makeMap();

/* The freeMap() function frees up the allocated memory being utilized by the
   map parameter.
  
  @param *map is the map struct that is taking up memory
*/
void freeMap( Map *map );

/* The readLocations() function receives a file pointer and map as it's parameters. It's
   job is to read a valid file and create a Location structure out of each line of
   text in the file.

   @param filename is the file to be read for Location creation.
   @param map the each location will be stored in.
*/
void readLocations( char const *filename, Map *map );

/* The listLocations() function receives a map, a compare function and a test as its
   parameters. This function utilizes qsort() to sort the list by the determined field
   and prints the results if the test parameter returns true.

   @param map is the map contents to be sorted/printed.
   @param *compare is the compare function for sorting.
   @param *test is the test used to determine if the map list should be printed.
*/
void listLocations( Map *map, int (*compare)( void const *va, void const *vb ),
                    bool (*test)( Location const *loc ) );