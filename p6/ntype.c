/**
 *  @file ntype.c
 *  @author Stephen Gonsalves (dkgonsal)
 *
 *  The ntype file's purpose is to create the correct type of node for the
 *  queue and fill that node's fields with the correct function pointers. If
 *  a node cannot be created it will return NULL.
 */

#include "ntype.h"
#include "queue.h"

/*
 * This is the print function for an IntNode. It will receive 
 *  an int parameter and print it.
 *  
 *  @param val is the int value to print
 */
static void printInt( struct NodeStruct const *n )
{
  int *ptr = ( int * ) n->val;
  printf( "%d\n", *ptr );
}

/*
 *  This is the print function for a RealNode. It will receive 
 *  a double parameter and print it.
 *  
 *  @param val is the double value to print
 */
static void printReal( struct NodeStruct const *n )
{
  double *ptr = n->val;
  double val = *ptr;
  printf( "%.03lf\n", val );
}

/*
 *  This is the print function for a StringNode. It will receive 
 *  a generic parameter and print it.
 *  
 *  @param val is the string value to print
 */
static void printStr( struct NodeStruct const *n )
{
  char *ptr = n->val;
  printf( "%s\n", ptr );
}

/*  
 *  Determines if two nodes are equivalent by comparing where their
 *  print fields point to.
 * 
 *  @param a is the first node used for comparison.
 *  @param b is the second node used for comparison.
 *  @return true if the nodes are duplicates. Otherwise, returns false.
 */ 
static bool equalsInt( struct NodeStruct const *a,struct NodeStruct const *b ) 
{
  if ( a->print == b->print ) {
    int *ptrA = a->val;
    int *ptrB = b->val;
    int valA = *ptrA; 
    int valB = *ptrB; 

    if ( valA == valB ) {
      return true;
    } else {
      return false;
    }
  }

  return false;
}

/*  
 *  Determines if two nodes are equivalent by comparing where their
 *  print fields point to.
 * 
 *  @param a is the first node used for comparison.
 *  @param b is the second node used for comparison.
 *  @return true if the nodes are duplicates. Otherwise, returns false.
 */ 
static bool equalsReal( struct NodeStruct const *a, struct NodeStruct const *b ) 
{
  if ( a->print == b->print ) {
    double *ptrA = a->val;
    double *ptrB = b->val;
    double valA = *ptrA; 
    double valB = *ptrB;     
    if ( valA == valB ) {
      return true;
    } else {
      return false;
    }
  }

  return false;
}

/*  
 *  Determines if two StringNodes are equivalent by comparing their
 *  strings and where their print fields point to.
 * 
 *  @param a is the first node used for comparison.
 *  @param b is the second node used for comparison.
 *  @return true if the nodes are duplicates. Otherwise, returns false.
 */ 
static bool equalsString( struct NodeStruct const *a, struct NodeStruct const *b ) 
{
  if ( a->print == b->print ) {
    char *ptrA = a->val;
    char *ptrB = b->val;
    if ( strcmp( ptrA, ptrB ) == 0 ) {
      return true;
    } else {
      return false;
    }
  }

  return false;
}

/*  
 *  Frees the memory allocated to a Node.
 * 
 *  @param n is the IntNode whose memory is being freed.
 */
static void destroy( Node *n )
{
  free( n->val );
  free( n );
}

/*  
 *  Constructs an integer node with the given string.
 * 
 *  @param init is the string to be stored in the node's val field.
 *  @return NULL if the node could not be created. Otherwise, returns
 *          the newly created IntNode.
 */
Node *makeIntNode( char const *init )
{
  int elem;
  char c;
  int test = sscanf( init, "%d%c", &elem, &c );

  if ( test != 1 || init[ 0 ] == '"') { 
    return NULL;
  }

  Node *intNode = ( Node * ) malloc( sizeof( Node ) );
  int *val = ( int * ) malloc( sizeof( int ) );
  *val = elem;
  intNode->print = printInt;
  intNode->equals = equalsInt;
  intNode->destroy = destroy;
  intNode->next = NULL;
  intNode->val = val;

  return intNode;
}

/*  
 *  Constructs a real node with the given string.
 * 
 *  @param init is the double value to be stored in the node's val field.
 *  @return NULL if the node could not be created. Otherwise, returns
 *          the newly created RealNode.
 */
Node *makeRealNode( char const *init )
{
  double elem = 0;
  char c = NULL;
  
  if ( init[ 0 ] == '"' ) {
    return NULL;
  }

  if ( sscanf( init, "%lf%c", &elem, &c ) == 1 ) {
    Node *realNode = ( Node * ) malloc( sizeof( Node ) );
    double *val = ( double * ) malloc( sizeof( double ) );
    *val = elem;

    realNode->print = printReal;
    realNode->equals = equalsReal;
    realNode->destroy = destroy;
    realNode->next = NULL;
    realNode->val = val;
    return realNode;
  }

  return NULL;
}

/*  
 *  Constructs a string node with the given string.
 * 
 *  @param init is the string to be stored in the node's val field.
 *  @return NULL if the node could not be created. Otherwise, returns
 *          the newly created StringNode.
 */
Node *makeStringNode( char const *init )
{  
  int strLength = strlen( init );
  if ( init[ 0 ] != '"' || init[ strLength - 1 ] != '"' ) {
    return NULL;
  }

  // Allocate a string with a small, initial capacity.
  int capacity = strLength;
  char *elem = ( char * ) malloc( capacity * sizeof( char ) + 1 );

  for ( int i = 1; i < strLength - 1; i++ ) {
    elem[ i - 1 ] = init[ i ];
  }
  elem[ strLength - RM_END_QUOTE ] = '\0';  

  Node *n = ( Node * ) malloc( sizeof( Node ) );
  char *val = ( char * ) malloc( sizeof( char ) );
  val = elem;
  n->print = printStr;
  n->equals = equalsString;
  n->destroy = destroy;
  n->next = NULL;
  n->val = val;

  return n;
}