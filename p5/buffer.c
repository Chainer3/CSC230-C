/**
   @file buffer.c
   @author Stephen Gonsalves (dkgonsal)

   The buffer file creates a Buffer structure with a data field, capacity field
   and a length field. Functions within the file allow input files to be read and
   stored in the buffer's data field, as well as written from its data field into 
   a binary file. The buffer can also be cleared and memory freed from within this
   file.
*/

#include "buffer.h"

/* Creates the Buffer structure for utilization in the remaining functions.

   @return the newly created buffer structure.
*/
Buffer *makeBuffer()
{
    Buffer *newBuffer = malloc( sizeof( Buffer ) );
    newBuffer->data = ( char * ) malloc( sizeof( char ) * BBITS);
    newBuffer->cap = BBITS;
    newBuffer->len = 0;

    return newBuffer;
}

/* Frees the memory being utilized to store the buffer and its fields.

   @param buffer is the buffer who's memory is being freed. 
*/
void freeBuffer( Buffer *buffer )
{
  free( buffer->data );
  free( buffer );
}

/* Appends a byte of input to the end of the buffer's data field
  
   @param buffer is the structure who's data field is being appended to.
   @param byteVal is a character value ('0' or '1') being appended to the buffer's 
          data field.
*/
void appendByte ( Buffer *buffer, char byteVal )
{
  CHECK_CAP( char, buffer, INC_CAP );
  buffer->data[ buffer->len ] = byteVal;
  buffer->len++;
}

/* Gets the bit from the byte at the provided index that will be amended.
   
   @param buffer who's data field is being checked for the bit.
   @param idx is the location of the bit being checked.
   @return true if the bit is 1. Otherwise, returns false.
*/
bool getBit( Buffer const *buffer, int idx )
{
  int byteIdx = FIND_BYTE( idx, BBITS );
  int bitIdx = FIND_BIT( idx, BBITS );

  // return the value at this index in data field
  return ( buffer->data[ byteIdx ] & ( 1 << bitIdx ) ) ? 1 : 0;
}

/* Sets the bit in data at the received index to 1 or 0 based on the boolean
   parameter.
   
   @param buffer who's data is being set/cleared.
   @param idx is the bit in the byte that will be set/cleared.
   @param bitVal sets the bit to 1 if true. Otherwise, clears it.
*/
void setBit( Buffer const *buffer, int idx, bool bitVal )
{
  // get the byte and bit indexes
  int byteIdx = FIND_BYTE( idx, BBITS );
  int bitIdx = FIND_BIT( idx, BBITS );
  
  // set/clear the bit using a mask with shift operation
  if ( bitVal ) {
    buffer->data[ byteIdx ] = buffer->data[ byteIdx ] | ( 0x01 << bitIdx );
  } else {
    buffer->data[ byteIdx ] = buffer->data[ byteIdx ] & ~( 0x01 << bitIdx );
  }
}

/* Reads from a file into the buffer's data field.
   
   @param filename of the file being passed load into the buffer.
   @return the buffer that is created from the input file.
*/
Buffer *loadBuffer( char const *filename )
{
  // open the filestream
  FILE *fp = fopen( filename, "rb" );

  // handle invalid file
  if ( !fp ) {
    STREAM_ERROR( filename );
  }

  // initialize buffer
  Buffer *buffer = makeBuffer();
    
  if ( fseek( fp, 0, SEEK_END ) == -1 ) {
    STREAM_ERROR( filename );
  }
  
  double fileLen = ftell( fp );

  if ( fseek( fp, 0, SEEK_SET ) == -1 ) {
    STREAM_ERROR( filename );
  }
    
  buffer->data = ( char * ) realloc( buffer->data, fileLen * sizeof( char ) );
  buffer->cap = fileLen;
  buffer->len = fileLen;

  // read file into data field
  fread( buffer->data, sizeof( unsigned char ), fileLen, fp );
    
  // close the filestream and return
  fclose( fp );
  return buffer;
}

/* Saves the buffer to an output file for loading later when needed.
   
   @param buffer is the buffer who's data is being saved to a file.
   @param filename is the file the buffer's data is being saved to.
*/
void saveBuffer( Buffer *buffer, char const *filename )
{
  // open the filestream
  FILE *fp = fopen( filename, "wb");

  // handle an invalid file
  if ( !fp ) {
    STREAM_ERROR( filename );
  }

  // write contents of buffer into file
  fwrite( buffer->data, sizeof( char ), buffer->len, fp );

  // close the filestream.
  fclose( fp );
}