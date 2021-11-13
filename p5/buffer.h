#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/** Number of bits in a byte. */
#define BBITS 8
/** Initial capacity of buffer data field */
#define INIT_CAP 8
/** Increase capacity of buffer data field */
#define INC_CAP 5


/** Macro for file read error */
#define STREAM_ERROR( filename ) { perror( filename ); exit( 1 ); }
/**  */
#define CHECK_CAP( char, buffer, INC_CAP ) { if ( buffer->len >= buffer->cap ) { buffer->cap *= INC_CAP; buffer->data = ( char* ) realloc( buffer->data, buffer->cap ); } }
/**  */
#define FIND_BYTE( idx, BBITS ) idx / BBITS;
/**  */
#define FIND_BIT( idx, BBITS ) BBITS - 1 - idx % BBITS;
/**  */
#define USAGE_ERROR( x ) { fprintf( stderr, "usage: %s [-d] [-b bits] infile outfile\n", x ); exit( 1 ); }


/** Representation of a resizable array of bytes, with functions to
    make it easy to access individual bits. */
typedef struct {
  /** Resizable array of bytes stored in this buffer. */
  char *data;
  /** Number of bytes currently stored in the data array. */
  int len;
  /** Capacity of the data array, measured in bytes. */
  int cap;
} Buffer;

/* Creates the Buffer structure for utilization in the remaining functions.

   @return the newly created buffer structure.
*/
Buffer *makeBuffer();

/* Frees the memory being utilized to store the buffer and its fields.

   @param buffer is the buffer who's memory is being freed. 
*/
void freeBuffer( Buffer *buffer );

/* Appends a byte of input to the end of the buffer's data field
  
   @param buffer is the structure who's data field is being appended to.
   @param byteVal is a character value ('0' or '1') being appended to the buffer's 
          data field.
*/
void appendByte ( Buffer *buffer, char byteVal );

/* Gets the bit that will be amended.
   
   @param buffer who's data field is being checked for the bit.
   @param idx is the location of the bit being checked.
   @return true if the bit is 1. Otherwise, returns false.
*/
bool getBit( Buffer const *buffer, int idx );

/* Sets the bit in data at the received index to 1 or 0 based on the boolean
   parameter.
   
   @param buffer who's data is being set/cleared.
   @param idx is the bit in the byte that will be set/cleared.
   @param bitVal sets the bit to 1 if true. Otherwise, clears it.
*/
void setBit( Buffer const *buffer, int idx, bool bitVal );

/* Reads from a file into the buffer's data field.
   
   @param filename of the file being passed load into the buffer.
   @return the buffer that is created from the input file.
*/
Buffer *loadBuffer( char const *filename );

/* Saves the buffer to an output file for loading later when needed.
   
   @param buffer is the buffer who's data is being saved to a file.
   @param filename is the file the buffer's data is being saved to.
*/
void saveBuffer( Buffer *buffer, char const *filename );

#endif