/** Maximum output line length. */
#define OUTPUT_LIMIT 80
/** Maximum lines reported in list */
#define MAX_FILE_LINES 999
/** Maximum output line length. */
#define MAX_NUMS_LINE_LEN 75

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int idx;
extern int lineNum[ MAX_FILE_LINES ];
extern char matchList[ MAX_FILE_LINES ][ OUTPUT_LIMIT ];
extern char matchListNums[ MAX_FILE_LINES ][ MAX_NUMS_LINE_LEN + 1 ];

void addLine( int, char const [] );
void printList( bool numberFlag );