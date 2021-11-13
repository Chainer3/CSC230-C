/**
   @file inflate.c
   @author Stephen Gonsalves (dkgonsal)

   The inflate file decompresses the words in the compressed file to a readable format 
   for the user.
*/

#include "dictionary.h"
#include "buffer.h"


/** Minimum number of bits in an entry */
#define MIN_BITS 8
/** Maximum number of bits in an entry */
#define MAX_BITS 32
/** Minimum number of command line arguments */
#define MIN_ARGS 3
/** Maximum number of command line arguments */
#define MAX_ARGS 6
/** Indexes for file arguments */
#define FILE_ARGS 2

/* The LZW decompression algorithm implemented as a helper function.

   @param d the dictionary being used for word searching.
   @param b the buffer being used for decompression.
   @param bits number of bits indicated by argument.
   @return the buffer to the main function.
*/
Buffer *inflate( Dictionary *d, Buffer *inBuffer, int bits )
{
  Buffer *outBuffer = makeBuffer();
  unsigned int loc = 0;

  for ( int i = 0; i < inBuffer->len; i++ ) {      
    if ( ( loc + bits ) > ( inBuffer->len * BBITS ) ) {
      break;
    }
    
    unsigned int dictIndex = 0, secondLoc = 0, nextWord = 0;

    for ( int j = 0; j < bits; j++ ) {
      if ( getBit( inBuffer, loc ) ) {
        dictIndex = dictIndex | ( 0x01 << ( bits - 1 - j ) );
      }
      loc++;
    }

    char *currentWord = d->wordList[ dictIndex ];
    
    for ( int k = 0; k < d->wordLen[ dictIndex ]; k++ ) {
      appendByte( outBuffer, currentWord[ k ] );
    }

    if ( i < inBuffer->len - 1 ) {
      secondLoc = loc;
      
      if ( ( secondLoc + bits ) > ( inBuffer->len * BBITS ) ) {
        break;
      }
      

      for ( int k = 0; k < bits; k++ ) {   
        if ( getBit( inBuffer, secondLoc ) ) {
          nextWord = nextWord | ( 0x01 << ( bits - 1 - k ));
        }
        secondLoc++;
      }
      
      // Check for invalid compression in file
      INFLATE_ERROR( nextWord, d );

      char *newWord = d->wordList[ nextWord ];
      int len = d->wordLen[ dictIndex ];
      char *word = ( char * ) malloc( sizeof( char ) * len + 1 );

      memcpy( word, d->wordList[ dictIndex ], len );
      word[ len ] = newWord[ 0 ];
      addWord( d, word, d->wordLen[ dictIndex ] + 1);
      free( word );
    }
  }

  return outBuffer;
}


/* This is the starting point of the deflate program. Using the linked buffer/dictionary
   headers, deflate will read from a valid input file and create a buffer to write
   compressed versions of each new word to a dictionary and ultimately to a valid output
   file. 
    
   @param argc is the number of args received in the terminal.
   @param argv is an array of args received in the terminal.
*/
int main( int argc, char *argv[] )
{ 
  bool printDict = false;
  int bitArg = DEFAULT_BITS;
  Dictionary *d;

  if ( argc < MIN_ARGS || argc > MAX_ARGS ) {
    USAGE_ERROR( "inflate" );
  }

  int inFile = argc - FILE_ARGS;
  int outFile = argc - 1;
  
  for ( int i = 1; i < inFile; i++ ) {
   if ( strcmp( "-b", argv[ i ] ) == 0 ) {
      if ( sscanf( argv[ i + 1 ], "%d", &bitArg ) == 1 && 
           bitArg > MIN_BITS - 1 && bitArg < MAX_BITS + 1 ) {
        i++;
        continue;
      } else {
        USAGE_ERROR( "inflate" );
      }   
    } else if ( strcmp( "-d", argv[ i ] ) == 0 ) {
      printDict = true;
      continue;
    } else {
        USAGE_ERROR( "inflate" );
    }
  }

  d = makeDictionary( bitArg );
  Buffer *inBuffer = loadBuffer( argv[ inFile ] );
  Buffer *outBuffer = makeBuffer();

  outBuffer = inflate( d, inBuffer, bitArg );
  freeBuffer( inBuffer );

  saveBuffer( outBuffer, argv[ outFile ] );
  freeBuffer( outBuffer );
  
  if ( printDict ) {
    reportDictionary( d );
  }

  freeDictionary( d );
  return ( EXIT_SUCCESS );
}