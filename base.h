#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short ushort;
typedef char BOOL;

inline void InitRandom()
{
    srand(time(NULL));
}

inline int GetRandomNumber(int min, int max)
{
    return (rand() % (max - min)) + min;
}

#define MALLOC_PTR(type) (type*) malloc(sizeof(type));
#define MALLOC_ARRAY(type, count) (type*) malloc(sizeof(type) * count)
#define TRUE 1
#define FALSE 0

inline void ConsMovCursor(ushort x, ushort y)
{
    printf("\x1b[%i, %iH", y, x);
}
//Moves the console cursor to the specified coordinates
#define C_MC(x, y) Cons_MoveCursor(x, y)

inline void ConsSet_OutputForegroundColor(byte r, byte g, byte b)
{
    printf("\x1b[38;2;%i;%i;%im", r, g, b);
}
//sets the foreground color
#define CS_OFC(r, g, b) ConsSet_OutputForegroundColor(r, g, b)

inline void ConsSet_OutputBackgroundColor(byte r, byte g, byte b)
{
    printf("\x1b[48;2;%i;%i;%im", r, g, b);
}
//sets the foreground color
#define CS_OBC(r, g, b) ConsSet_OutputBackgroundColor(r, g, b)

inline void Cons_OutChar(char c) 
{
    putchar(c);
}
// Outputs a character
#define C_OC(c) Cons_OutChar(c)

inline void Cons_OutNewLine()
{
    putchar('\n');
}
// Outputs a newline
#define C_ONL() Cons_OutNewLine()

void Cons_OutInt(int i)
{
    char * buffer = MALLOC_ARRAY(char, 11);
    itoa(i, buffer, 10);
    fputs(buffer, stdout);
    free(buffer);
}
// Outputs a number.
#define C_OI(i) Cons_OutInt(i)

inline void Cons_OutStr(const char * str, BOOL newline)
{
    if(str && newline)
        puts(str);
    else if(str && !newline)
        fputs(str, stdout);
}
// Outputs a string
#define C_OS(str, newline) Cons_OutStr(str, newline)

void Cons_OutFloat(float f)
{
    int i = (int) f;
    f -= i;

    //outputs the > 0 part
    char * buffer = MALLOC_ARRAY(char, 11);
    itoa(i, buffer, 10);
    fputs(buffer, stdout);
    putchar('.');

    for(int i = 0; i < 10; i++)
    {
        f *= 10;
        char c = (char) f;
        f -= c;
        c += 48;
        buffer[i] = c;
    }

    buffer[10] = NULL;

    fputs(buffer, stdout);
    free(buffer);
}
// Outputs a float.
#define C_OF(f) Cons_OutFloat(f)

#endif
