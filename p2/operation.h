/** Exit Status represeting 100 for when overflow happens*/
#define EXIT_STATUS 100
/** Exit Status represeting 100 for when dividing by zero is detected*/
#define EXIT_STATUS_ZERO 101

/** Exit status indicating that the program was given invalid input. */
#define FAIL_INPUT 102

long plus( long a, long b );
long minus( long a, long b );
long times( long a, long b );
long divide( long a, long b );