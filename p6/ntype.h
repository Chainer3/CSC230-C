/**
 *  @file ntype.h
 *  @author
 *
 *  Header for ntype exposing functions for creating nodes of various types.
 */

#ifndef NTYPE_H
#define NTYPE_H

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/** Initial capacity of the return string */
#define CAP 10

/** Make a node containing an integer value.
    @param val Integer value to store in this node.
    @return pointer to the new node.
*/
Node *makeIntNode( char const *init );

/** Make a node containing a real number value.
    @param val Double value to store in this node.
    @return pointer to the new node.
*/
Node *makeRealNode( char const *init );

/** Make a node containing an arbitrary string value.
    @param str String value to store in this node.
    @return pointer to the new node.
*/
Node *makeStringNode( char const *init );

#endif
