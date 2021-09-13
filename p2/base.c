#include "base.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "operation.h"

// This preprocessor syntax makes it so we can override the value of BASE with
// a compiler option.  For some desired base, n, we can compile with: -DBASE=n
// Don't change these three lines of preprocessor directives.
#ifndef BASE
/** Base this program uses for input and output. */
#define BASE 7

int skipSpace()
{

}

long readValue()
{

}

void writeValue( long val )
{

}
