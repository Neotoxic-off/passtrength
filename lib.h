#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "unistd.h"

typedef struct global
{
    int length;
    int low;
    int high;
    int special;
    int number;
    int occurrence;
    int strength;
    char *pass;
} general;