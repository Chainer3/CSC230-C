/**
    @file dictionary.c
    @author Stephen Gonsalves (dkgonsal)
    
    The dictionary file creates a dictionary struct and handles all of the functions
    associated with the dictionary. The dictionary file only depends on its own header
    file.
*/

#include "dictionary.h"

Dictionary *makeDictionary( int bits )
{
  Dictionary *dictionary = ( Dictionary * ) malloc( sizeof( Dictionary ) );

  long size = pow( BASE, bits );

  // Fill the base dictionary
  dictionary->dictSize = size;
  dictionary->dictLength = MIN_DICT_SIZE;
  dictionary->wordList = ( char ** ) malloc( size * sizeof( char * ) );
  dictionary->wordLen = ( int * ) malloc( size * sizeof( int ));

  for ( int j = 0; j < MIN_DICT_SIZE; j++ ) {
    dictionary->wordList[ j ] = ( char * ) malloc( sizeof( char ) );
    dictionary->wordLen[ j ] = 1;
    dictionary->wordList[ j ][ 0 ] = ( char ) j;
  }

  return dictionary;
}

void freeDictionary( Dictionary *d )
{
  FOR( i, d->dictLength )
    free( d->wordList[ i ] );

  free( d->wordList );
  free( d->wordLen );
  free( d );
}

void printWord( char *word, int len )
{
  FOR( i, len )
    if ( word[ i ] > ' ' && word[ i ] <= '~' ) {
      printf( " %c", word[ i ] );
    } else {
      printf( "%02X", ( unsigned char ) word[ i ] );
    }
}

void reportDictionary( Dictionary *d )
{
  for ( int i = MIN_DICT_SIZE; i < d->dictLength; i++ ) {
    printf( "%4d ", i );
    printWord( d->wordList[ i ], d->wordLen[ i ] );
    printf( "\n" );
  }
}

int lookupWord( Dictionary *d, char *word, int len )
{
  FOR( i, d->dictLength ) {
    if ( d->wordLen[ i ] == len ) {
      if ( memcmp( d->wordList[ i ], word, len ) == 0 ) {
        int dictPick = i;
        return dictPick;
      }
    }
  }
  return -1;
}

void addWord( Dictionary *d, char *word, int len )
{
  if ( d->dictSize == d->dictLength ) {
    return;
  }
  
  d->wordList[ d->dictLength ] = ( char * ) malloc( len *  sizeof( char ) );

  FOR( i, len ) {
    d->wordList[ d->dictLength ][ i ] = word[ i ];
  }
  
  d->wordLen[ d->dictLength ] = len;
  d->dictLength++;
}