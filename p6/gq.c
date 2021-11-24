/**
 *  @file gq.c
 *  @author Stephen Gonsalves (dkgonsal)
 *
 *  This is the top-level file that the user interacts with. It builds and amends
 *  a queue through user commands and quits when the command is entered or when
 *  no input is entered. Nodes may only be of the int, double, and string (char *)
 *  typing to be added to the queue.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "input.h"
#include "queue.h"
#include "ntype.h"

/*  List of all the node creation functions.  This is a chain of responsibility; we
 *  can keep trying these functions until we find one that knows how to parse the
 *  init string.
 */
static Node *(*nodeConstructors[])( char const *init ) = {
  makeIntNode,
  makeRealNode,
  makeStringNode
};

/*  The main function serves as the intermediary between the user and the queue. It 
 *  will accept valid commands and reject empty or invalid commands that the lower
 *  level files cannot parse.
 */
int main()
{
  char *cmd = NULL;
  int qCount = 0;
  int arrLen = sizeof( nodeConstructors )/ sizeof( nodeConstructors[0] ); 
  Queue *q = makeQueue();

  do {
    printf( "cmd> " );
    cmd = readLine( stdin );
    printf( "%s", cmd );

    if ( cmd == NULL ) {
      break;
    }

    char *command = ( char * ) malloc( sizeof( char ) * CMD_CAP );
    char *element = ( char * ) malloc( sizeof( char ) * strlen( cmd ) );
    int pos = 0;

    if ( sscanf( cmd, "%s%n", command, &pos ) != 1 ) {
      free( command );
      free( element );
      break;
    }
    printf( "\n");

    // QUIT
    if ( strcmp( "quit\0", command ) == 0 ) {
      free( command );
      free( element );
      break;
    }

    // ENQUEUE
    else if ( strcmp( "enqueue\0", command ) == 0 ) {
      int length = strlen( cmd );
      int i = 1;
      for ( ; i < length - 1; i++) {
        element[i - 1] = cmd[pos + i];
      }
      element[ i ] = '\0';

      while ( *element == ' ') {
        element++;
      }
      for ( int i = strlen(element) - 1; i > 0; i--) {
        if ( element[i] != ' ')
          break;	
          element[i] = '\0';
      }

      bool built = false;
      Node *n = NULL;
      for ( int i = 0; i < arrLen; i++ ) {
        n = nodeConstructors[ i ]( element );
        if ( n != NULL ) {
          enqueue( q, n );
          built = true;
          qCount++;
          break;
        }
      }
      if ( !built ) {
        printf( "Invalid command\n" );
      }
      printf( "\n" );
      continue;
    }

    // DEQUEUE
    else if ( strcmp( "dequeue\0", command ) == 0 ) {
      if ( q->head == NULL || qCount == 0 ) {
        
        printf( "Invalid command\n\n" );
      } else {
        Node *temp = dequeue( q );
        temp->print( temp );
        printf( "\n"  );
        temp->destroy( temp );
        qCount--;
      }
      continue;
    }

    // PROMOTE
    else if ( strcmp( "promote\0", command ) == 0 ) {
      if ( qCount == 0 ) {
        printf( "Invalid command\n\n" );
        continue;
      }

      int length = strlen( cmd );
      int i = 1;
      for ( ; i < length - 1; i++) {
        element[i - 1] = cmd[pos + i];
      }  
      element[ i ] = '\0';

      while ( *element == ' ') {
        element++;
      }

      for ( int i = strlen(element) - 1; i > 0; i--) {
        if ( element[i] != ' ') {
          break;
        }
        element[i] = '\0';
      }

      bool promoted = false;
      Node *n = NULL;
      for ( int i = 0; i < arrLen; i++ ) {
        n = nodeConstructors[ i ]( element );
        if ( n != NULL ) {
          promoted = promote( q, n );
          if ( promoted ) {
            break;
          }
        }
      }

      if ( !promoted ) {
        printf( "Invalid command\n\n" );
        continue;
      }

      printf( "\n" );
      n->destroy( n );
    }
    
    // LENGTH
    else if ( strcmp( "length\0", command ) == 0 ) {
      printf( "%d\n\n", qCount );
      continue;
    } 

    // Invalid Command
    else {
      printf( "Invalid command\n\n" );
      continue;
    }

    free( command );
    free( element );

  } while( true );

  free( cmd );
  freeQueue( q );

  return EXIT_SUCCESS;
}