#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "buffer.h"

int main()
{
  // Make an empty buffer.
  Buffer *buffer = makeBuffer();

  // Add a byte to the buffer.
  appendByte( buffer, 0x57 );

  // Check each of its bits.
  assert( getBit( buffer, 0 ) == 0);
  assert( getBit( buffer, 1 ) != 0 );
  assert( getBit( buffer, 2 ) == 0 );
  assert( getBit( buffer, 3 ) != 0 );
  assert( getBit( buffer, 4 ) == 0 );
  assert( getBit( buffer, 5 ) != 0 );
  assert( getBit( buffer, 6 ) != 0 );
  assert( getBit( buffer, 7 ) != 0 );

  // Free the buffer.
  freeBuffer( buffer );

  /////////////////////////////////////////////////////

  // Make another bit buffer.
  buffer = makeBuffer();

  // Try adding a couple of bytes.
  appendByte( buffer, 0x2F );
  appendByte( buffer, 0xB8 );
  
  // Check each of its bits.
  assert( getBit( buffer, 0 ) == 0);
  assert( getBit( buffer, 1 ) == 0 );
  assert( getBit( buffer, 2 ) != 0 );
  assert( getBit( buffer, 3 ) == 0 );
  assert( getBit( buffer, 4 ) != 0 );
  assert( getBit( buffer, 5 ) != 0 );
  assert( getBit( buffer, 6 ) != 0 );
  assert( getBit( buffer, 7 ) != 0 );
  
  assert( getBit( buffer, 8 ) != 0);
  assert( getBit( buffer, 9 ) == 0 );
  assert( getBit( buffer, 10 ) != 0 );
  assert( getBit( buffer, 11 ) != 0 );
  assert( getBit( buffer, 12 ) != 0 );
  assert( getBit( buffer, 13 ) == 0 );
  assert( getBit( buffer, 14 ) == 0 );
  assert( getBit( buffer, 15 ) == 0 );

  freeBuffer( buffer );

  /////////////////////////////////////////////////////

  // Try out the setBit() function.
  buffer = makeBuffer();

  // Add a couple of bytes, one full of 0 bits and the other full of
  // 1 bits.
  appendByte( buffer, 0x00 );
  appendByte( buffer, 0xff );

  // Rewrite all the bits.
  setBit( buffer, 0, 1 );
  setBit( buffer, 1, 1 );
  setBit( buffer, 2, 1 );
  // setBit( buffer, 3, 0 ); This should stay set to 0
  setBit( buffer, 4, 0 );
  setBit( buffer, 5, 1 );
  setBit( buffer, 6, 1 );
  // setBit( buffer, 7, 0 ); Same here.

  setBit( buffer, 8, 1 );
  setBit( buffer, 9, 0 );
  // setBit( buffer, 10, 1 );  This should stay set to 1
  setBit( buffer, 11, 0 );
  // setBit( buffer, 10, 1 );  Same here
  setBit( buffer, 12, 1 );
  setBit( buffer, 13, 0 );
  setBit( buffer, 14, 0 );
  setBit( buffer, 15, 1 );

  // Make sure we got the right bits.
  assert( getBit( buffer, 0 ) != 0);
  assert( getBit( buffer, 1 ) != 0 );
  assert( getBit( buffer, 2 ) != 0 );
  assert( getBit( buffer, 3 ) == 0 );
  assert( getBit( buffer, 4 ) == 0 );
  assert( getBit( buffer, 5 ) != 0 );
  assert( getBit( buffer, 6 ) != 0 );
  assert( getBit( buffer, 7 ) == 0 );
  
  assert( getBit( buffer, 8 ) != 0);
  assert( getBit( buffer, 9 ) == 0 );
  assert( getBit( buffer, 10 ) != 0 );
  assert( getBit( buffer, 11 ) == 0 );
  assert( getBit( buffer, 12 ) != 0 );
  assert( getBit( buffer, 13 ) == 0 );
  assert( getBit( buffer, 14 ) == 0 );
  assert( getBit( buffer, 15 ) != 0 );
  
  freeBuffer( buffer );
  
  /////////////////////////////////////////////////////

  // A sequence of bits to use for some of the remaining tests (Here,
  // we're just using a string to make it easy to get to each bit.  This
  // isn't how the Buffer is supposed to store bits.)
  char bits[] = "01101001" "01011010" "10001100" "10010101"
    "01010001" "01111111" "10111000" "00111000";
  int n = strlen( bits );

  // Make a bit buffer with room for 8 bytes.
  buffer = makeBuffer();
  for ( int i = 0; i < n / 8; i++ )
    appendByte( buffer, 0 );

  // Set all the bits according to the array above.
  for ( int i = 0; i < n; i++ ) {
    setBit( buffer, i, bits[ i ] == '1' );
  }

  // Check to make sure they're right.
  for ( int i = 0; i < n; i++ ) {
    if ( bits[ i ] == '0' )
      assert( getBit( buffer, i ) == 0 );
    else
      assert( getBit( buffer, i ) != 0 );
  }

  // Try saving the contents of the buffer to a file.
  saveBuffer( buffer, "output.bin" );

  freeBuffer( buffer );

  // Make sure the contents of the file look right.
  FILE *fp = fopen( "output.bin", "rb" );

  // Make sure we could open the file (did it got created).
  assert( fp );

  // Try to read up to 100 bytes from the file.
  unsigned char data[ 100 ];
  // Make sure the file is the right size (8 bytes)
  assert( fread( data, sizeof( unsigned char ), 100, fp ) == 8 );
  fclose( fp );

  // Make sure the contents of the file are right.
  // This is the same sequence of bits as the bits array, but here it's
  // actually in binary rather than as a string of 0 and 1 characters.
  unsigned char rawBytes[] = { 0x69, 0x5A, 0x8C, 0x95, 0x51, 0x7F, 0xB8, 0x38 };
  for ( int i = 0; i < sizeof( rawBytes ); i++ )
    assert( rawBytes[ i ] == data[ i ] );

  /////////////////////////////////////////////////////

  // Try out loading a bit buffer from a file.
  buffer = loadBuffer( "output.bin" );

  // Check the number of bits in the buffer, and check each bit.
  for ( int i = 0; i < n; i++ ) {
    if ( bits[ i ] == '0' )
      assert( getBit( buffer, i ) == 0 );
    else
      assert( getBit( buffer, i ) == 1 );
  }

  freeBuffer( buffer );
  
  return EXIT_SUCCESS;
}
