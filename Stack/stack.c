#include <stdio.h>
#include <stdlib.h>
#define maxsize 1024
typedef int datatype;


typedef struct Stack
{
    datatype elements[maxsize];
    int Top;
} ;
