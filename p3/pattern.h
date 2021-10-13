#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const char line[];
static const char pat[];
static const bool flags[];

bool validPattern( char const pat[] );
bool matchPattern( char const pat[], char const line[] );