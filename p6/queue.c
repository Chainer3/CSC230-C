/**
 *  @file queue.c
 *   @author Stephen Gonsalves (dkgonsal)
 *   
 *   The dictionary file creates a dictionary struct and handles all of the functions
 *   associated with the dictionary. The dictionary file only depends on its own header
 *   file.
 */

#include "queue.h"


/*  
 *  Creates a new queue with an empty head pointer and a pointer
 *  to a tail pointer.
 * 
 *  @return the newly created queue.
 */
Queue *makeQueue()
{
  Queue *q = ( Queue * ) malloc( sizeof( Queue ) );
  q->head = NULL;
  q->tail = &q->head;
  return q;
}

/*  
 *  Adds a node to the back of the queue.
 *
 *  @param q is the queue the node is being added to.
 *  @param n is the node being added to the queue.
 */
void enqueue( Queue *q, Node *n )
{
  *(q->tail) = n;
  q->tail = &( ( *(q->tail) )->next);
}

/*  
 *  Removes the head node from the queue and re-assigns the
 *  next node as the head.
 *
 *  @param q is the queue whose head node is being removed.
 *  @return the node that was removed. 
 */ 
Node *dequeue( Queue *q )
{
  if ( q->head != NULL ) {

    // create dulicatae head node to return
    Node *retNode = q->head;
    q->head = q->head->next;
    retNode->next = NULL;

    if ( !q->head ) {
      q->tail = &( q->head );
    }

    // free temp node memory and return duplicate
    return retNode;
  }

  return NULL;
}

/*  
 *  Removes the requested node from its position in the queue
 *  and places it at the front of the queue returns true. If
 *  the node is not found in the queue, false is returned.
 * 
 *  @param q is the queue being amended.
 *  @param example is the node being requested from the queue
 *         for promotion.
 *  @return true if the node was found and promoted. Otherwise, 
 *          returns false.
 */
bool promote( Queue *q, Node const *example )
{
  if ( q->head == NULL ) {
    return false;
  }

  Node *cur = q->head;
  Node *prev;
  bool found = false;

  if ( cur->equals( cur, example ) ) {
     return true;
  }

  // create temp head node from current head
  while ( cur->next != NULL ) {
    prev = cur;
    cur = cur->next;

    if ( cur->equals( cur, example ) ) {
      found = true;
      break;
    }
  }

  if ( found ) {
    if ( cur->next == NULL ) {     // If found node is at the end
      prev->next = NULL;
      q->tail = &prev->next;
      cur->next = q->head;
      q->head = cur;

      return true;
    } else if ( q->head->equals( q->head, cur ) ){
      return true;
    } else {
      prev->next = cur->next;
      cur->next = q->head;
      q->head = cur;
      return true;
    }
  }

  return false;
}

/*  
 *  Frees the memory allocated for the queue.
 * 
 *  @param q is the queue being freed.
 */
void freeQueue( Queue *q )
{
  while ( q->head != NULL ) {
    Node *temp = q->head->next;
    free( q->head );
    q->head = temp;
    free( temp );
  }
    free( q );
}