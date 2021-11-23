/**
 * @file input.h
 * @author Stephen Gonsalves (dkgonsal)
 *
 * Header file for input.c that exposes the readLine() function to
 * the ntype and gq files.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/** Initial capacity of the return string */
#define CMD_CAP 10
/** Used to double the capacity of the string */
#define CAP_DOUBLE 2

/* 
 * The readLine() function receives a file stream pointer that it uses to read a single
 * line of text from the input file. If the input reaches EOF, the function 
 *  
 * @param the file stream opened in map.c
 * @return the line of input.
 */
char *readLine( FILE *fp );