#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

# define MAX_LOC_LEN 30
# define OUTPUT_LEN 79
# define INIT_CAPACITY 5

typedef struct
{
    int id;
    char name[ MAX_LOC_LEN + 1 ];
    char country[ MAX_LOC_LEN + 1 ];
    double latitude, longitude;
} Location;

typedef struct
{
    Location **list;
    int count, capacity;
} Map;

double distance( Location const *a, Location const *b );
Map *makeMap();
void freeMap( Map *map );
void readLocations( char const *filename, Map *map );
void listLocations( Map *map, int (*compare)( void const *va, void const *vb ),
                    bool (*test)( Location const *loc ) );