/**
   @file deflate.c
   @author Stephen Gonsalves (dkgonsal)

   The deflate file compresses the words in the dictionary into hexadecimal entries 
   that are written into a file using the fwrite() function.
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

/* The LZW compression algorithm implemented as a helper function.

   @param d the dictionary being used for word writing/searching.
   @param inBuffer the buffer being used for compression.
   @param bits number of bits indicated by argument.
   @return the buffer to the main function.
*/
Buffer *deflate( Dictionary *d, Buffer *inBuffer, int bits )
{  
  Buffer *outBuffer = makeBuffer();
  int max = 1, loc = 0, inc = 0, len = 0;

  for ( int i = 0; i < inBuffer->len; i += inc ) {
    int maxLength = max;

    if ( inBuffer->len <  i + maxLength ) {
      maxLength = inBuffer->len - i;
    }
    int dictIndex = lookupWord( d, inBuffer->data + i, maxLength );

    while ( dictIndex == -1 ) {
      dictIndex = lookupWord( d, inBuffer->data + i, --maxLength );
    }
    while ( outBuffer->len * BBITS - loc < bits ) {
      appendByte( outBuffer, ( int ) 0); //0x00 not working
    }

    for ( int j = 0; j < bits; j++ ) {
      setBit( outBuffer, loc++, dictIndex & ( 0x01 << ( bits - 1 - j )));
    }

    len = d->wordLen[ dictIndex ];
    int newLen = len + 1;
    inc = newLen - 1;
    max = ( newLen > max ) ? newLen : max;
    char *newWord = ( char * ) malloc( sizeof( char ) * newLen );
        
    if ( i < inBuffer->len - 1 ) {
      memcpy( newWord, d->wordList[ dictIndex ], len );
      newWord[ len ] = inBuffer->data[ i + len ];
      addWord( d, newWord, maxLength + 1);
    }

    free( newWord );
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
    USAGE_ERROR( "deflate" );
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
        USAGE_ERROR( "deflate" );
      }   
    } else if ( strcmp( "-d", argv[ i ] ) == 0 ) {
      printDict = true;
      continue;
    } else {
        USAGE_ERROR( "deflate" );
    }
  }
  
  d = makeDictionary( bitArg );
  Buffer *inBuffer = loadBuffer( argv[ inFile ] );
  Buffer *outBuffer = makeBuffer();

  outBuffer = deflate( d, inBuffer, bitArg );
  freeBuffer( inBuffer );

  saveBuffer( outBuffer, argv[ outFile ] );
  freeBuffer( outBuffer );

  if ( printDict ) {
    reportDictionary( d );
  }

  freeDictionary( d );
  return ( EXIT_SUCCESS );
}