/** Maximum output line length. */
#define OUTPUT_LIMIT 80
/** Maximum lines reported in list */
#define MAX_FILE_LINES 1000

extern const int idx;
static const int lineNum[ MAX_FILE_LINES ];
static const char matchLine[ MAX_FILE_LINES ][ OUTPUT_LIMIT ];
extern const char matchList[ MAX_FILE_LINES ];

void addLine( int lno, char const line[] );
void printList( bool numberFlag );