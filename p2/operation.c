/*
   @file operation.c
   #author Stephen Gonsalves (dkgonsal)
   
   The operation.c program handles the math functions received through
   input.
 */

#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

int total = 0;

long plus( long a, long b) {
  total = a;
  return a + b;
}

long minus( long a, long b) {
  total = a;
  return a - b;
}

long times( long a, long b) {
  total = a;
  return a * b;
}

long divide( long a, long b) {
  total = a;
  return a / b;
}