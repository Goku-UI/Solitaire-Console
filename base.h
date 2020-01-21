#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <typeinfo.h>
//add the linux equivalent here

#define CHAR_SIZE 1
#define MALLOC_ARRAY(TYPE, LENGTH) (TYPE*) malloc(sizeof(TYPE) * LENGTH)
#define MALLOC_PTR(TYPE) (TYPE*) malloc(sizeof(TYPE))

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

inline void InitRandom()
{
    srand(time(NULL));
}

inline int GetRandomNumber(int min, int max)
{
    return (rand() % (max - min)) + min;
}

