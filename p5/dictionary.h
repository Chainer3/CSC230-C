/**
    @file dictionary.c
    @author Stephen Gonsalves (dkgonsal)
    
    The dictionary file creates a dictionary struct and handles all of the functions
    associated with the dictionary. The dictionary file only depends on its own header
    file.
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

/** Base for bits */
#define BASE 2
/** Minimum number of bits for a dictionary index. */
#define MINIMUM_BITS 8
/** Maximum number of bits for a dictionary index. */
#define MAXIMUM_BITS 32
/** Default number of bits to use for each code. */
#define DEFAULT_BITS 10
/** Initial half of the Dictionary */
#define MIN_DICT_SIZE 256

/** Macro for a for-loop */
#define FOR( var, limit ) for ( int var = 0; var < limit; var++ )

/** Dictionary structure */
typedef struct
{
    long dictSize;
    int dictLength;
    char **wordList;
    int *wordLen;
} Dictionary;

/* Creates the Dictionary object.
   
   @param bits is the max size of a word in the dictionary.
   @return the constructed dictionary.
*/
Dictionary *makeDictionary( int bits );

/* Frees the memory allocated for the Dictionary object.
   
   @param d is the Dictionary object who's memory is being freed.
*/
void freeDictionary( Dictionary *d );

/* Print out a word consisting of an arbitrary sequence of bytes
   (maybe including some non-ASCII codes and zeros).  It prints
   each byte using two characters, printing a symbol for visible
   characters and a 2-digit hexadecimal value for other bytes.
   
   @param word Array containing the bytes of the word.
   @param len Number of bytes in the word.
*/
void printWord( char *word, int len );

/* Prints each index and word in the dictionary.
   
   @param d is the dictionary that is being printed from.
*/
void reportDictionary( Dictionary *d );

/* Looks up a the first occurrence of a word with the given length in the
   given dictionary.
   
   @param d is the dictionary being searched.
   @param word being searched for in the dictionary.
   @param len is the length of the word to find in the dictionary.
*/
int lookupWord( Dictionary *d, char *word, int len );

/* Adds the given word to the dictionary if there is space.

   @param d is the dictionary being amended.
   @param word is the word to add to the dictionary.
   @param len is the first available index at the end of the dictionary.
*/
void addWord( Dictionary *d, char *word, int len );

#endif