/**
 *  @file queue.h
 *  @author Stephen Gonsalves (dkgonsal)
 *  
 *  Header file for queue, including definitions of Node and Queue structs.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
// 
// #define FOR_EACH_LOOP( Node, q ) { for ( int i = 0; i ) }

/** Node containing an arbitrary value. */
typedef struct NodeStruct {
  /** Pointer to a function that prints the value in this node.
      @param n Pointer to the node containing the value to print. */
  void (*print)( struct NodeStruct const *n );

  /** Compare the value in the two given nodes, returning true
      if it's considered equivalent.
      @param a Pointer to the left-hand node to compare (the one
      containing this compare function)
      @param b Pointer to the right-hand node to compare.
      @return pointer to a new queue. */
  bool (*equals)( struct NodeStruct const *a,
                  struct NodeStruct const *b );

  /** Pointer to a function that frees memory for this node and the
      value it contains.
      @param n Pointer to the node containing the value to print. */
  void (*destroy)( struct NodeStruct *n );
  
  /** Pointer to the next node on the queue. */
  struct NodeStruct *next;
  
  /** Pointer to the value contained in this node. */
  void *val;
} Node;

/** Representation of a queue of generic values. */
typedef struct {
  /** Pointer to the first node in the queue. */
  Node *head;
  
  /** Address of the null pointer at the end of this queue, either
      pointing to the head pointer or pointing to the next pointer
      inside the last node. */
  Node **tail;
} Queue;

/*  Creates a new queue with an empty head pointer and a pointer
 *  to a tail pointer.
 * 
 *  @return the newly created queue.
 */
Queue *makeQueue();

/*  Adds a node to the back of the queue.
 *
 *  @param q is the queue the node is being added to.
 *  @param n is the node being added to the queue.
 */
void enqueue(Queue *q, Node *n);

/*  Removes the head node from the queue and re-assigns the
 *  next node as the head.
 *
 *  @param q is the queue whose head node is being removed.
 *  @return the node that was removed. 
 */
Node *dequeue(Queue *q);

/*  Removes the requested node from its position in the queue
 *  and places it at the front of the queue returns true. If
 *  the node is not found in the queue, false is returned.
 * 
 *  @param q is the queue being amended.
 *  @param example is the node being requested from the queue
 *         for promotion.
 */
bool promote(Queue *q, Node const *example );

/*  Frees the memory allocated for the queue.
 * 
 *  @param q is the queue being freed.
 */
void freeQueue(Queue *q);


#endif
