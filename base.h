#ifndef BASE_H
#define BASE_H

#define nullptr 0x0

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

inline void Cons_MovCursor(ushort x, ushort y)
{
    printf("\x1b[%i, %iH", y, x);
}
//Moves the console cursor to the specified coordinates
#define C_MC(x, y) Cons_MovCursor(x, y)

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

typedef struct TagRGB
{
    byte r, g, b;
} RGB;

typedef struct TagConsCell
{
    RGB foreground;
    RGB background;
    char character;
} ConsCell, CC;

typedef struct TagConsBuffer
{
    ushort w, h;
    CC** buffer;
} ConsBuffer, CB;

//RGB
RGB* NewRGB(byte r, byte g, byte b)
{
    RGB* rgb = MALLOC_PTR(RGB);
    rgb->r = r;
    rgb->g = g;
    rgb->b = b;
    return rgb;
}

inline RGB SetRGB(byte r, byte g, byte b)
{
    return {r, g, b};
}

inline void FreeRGB(RGB* rgb)
{
    if(rgb)
        free(rgb);
    rgb = nullptr;
}

//Console Cell
CC* NewConsCell(char character, RGB fore, RGB back)
{
    CC* cc = MALLOC_PTR(CC);
    cc->background = back;
    cc->foreground = fore;
    cc->character = character;
    return cc;
}

void FreeConsCell(CC* cc)
{
    if(cc)
    {
        free(cc);
        cc = nullptr;
    }
}

//Console Buffer
CB* NewConsBuffer(ushort x, ushort y)
{
    CB* cb = MALLOC_PTR(CB);
    uint m = x * y;
    cb->buffer = MALLOC_ARRAY(CC*, m);
    for(uint i = 0; i < m; i++)
        cb->buffer[i] = NewConsCell(' ', {255, 255, 255}, {0, 0, 0});
    cb->w = x;
    cb->h = y;
}

void FreeConsBuffer(CB* cb)
{
    if(cb)
    {
        uint m = cb->w * cb->h;
        for(uint i = 0; i < m; i++)
            FreeConsCell(cb->buffer[i]);
        free(cb);
        cb = nullptr;
    }
}

inline ConsCell* ConsBuffer_GetCell(CB* cb, ushort x, ushort y)
{
    if(cb)
        return cb->buffer[y * cb->w + x];
    return nullptr;
}
//Gets the cell of a buffer.
#define CB_GC(cb, x, y) ConsBuffer_GetCell(cb, x, y)

BOOL ConsBuffer_Print(CB* cb, ushort x, ushort y)
{
    if(cb)
    {
        for(uint i = 0; i < cb->h; i++)
        {
            for(uint j = 0; j < cb->w; j++)
            {
                uint index = i * cb->w + x;
                CC* cc = cb->buffer[index];
                CS_OBC(cc->background.r, cc->background.g, cc->background.b);
                CS_OFC(cc->foreground.r, cc->foreground.g, cc->foreground.b);
                C_OC(cc->character);
            }
            C_MC(x, y + i);
        }
        return TRUE;
    }
    return FALSE;
}
//prints the buffer to the screen
#define BC_P(cb, x, y) ConsBuffer_Print(cb, x, y)


typedef struct TagListNode
{
    void* pointer;
    TagListNode* prev, * next;
} LN, ListNode;

typedef struct TagListIterator
{
    TagListNode* node;
} LI, ListIterator;

typedef struct TagList
{
    LN* start;
    LN* end;
    uint count;
} List;


//List Node
LN* NewListNode(void* ptr, LN* prev, LN* next)
{
    LN* ln = MALLOC_PTR(LN);
    ln->next = next;
    ln->prev = prev;
    ln->pointer = ptr;
    return ln;
}

inline void FreeListNode(LN* ln)
{
    if(ln)
    {
        free(ln);
        ln = nullptr;
    }
}

//List Iterator
inline LI* NewListIt(ListNode* node)
{
    LI* li = MALLOC_PTR(LI);
    li->node = node;
    return li;
}

inline LI SetListIt(ListNode* node)
{
    return {node};
}

inline void FreeListIt(LI* li)
{
    if(li)
    {
        free(li);
        li = nullptr;
    }
}

inline BOOL ListIt_GoNext(LI* li)
{
    if(li)
    {
        if(!li->node)
            return FALSE;
        else if(li->node->next)
        {
            li->node = li->node->next;
            return TRUE;
        }
    }
    return FALSE;
}
// Iterates to the next node.
#define LI_GN(li) ListIt_GoNext(li)

inline BOOL ListIt_GoPrev(LI* li)
{
    if(li)
    {
        if(!li->node)
            return FALSE;
        else if(li->node->prev)
        {
            li->node = li->node->prev;
            return TRUE;
        }
    }
    return FALSE;
}
// Iterates to the previous node.
#define LI_Gp(li) ListIt_GoPrev(li)

//if 0, li = nullptr;
//if 1, next & prev = nullptr;
//if 2, next ^ prev = nullptr;
//if 3, next & prev != nullptr;
#define LI_I_FAIL 0
#define LI_I_S_NE 1 
#define LI_I_S_OE 2
#define LI_I_S_ME 3
byte ListIt_Insert(List* list, LI* li, void* ptr)
{
    if(li && list)
    {
        if(!li->node)
            return LI_I_FAIL;
        
        LN* node = li->node;
        if(node->next && node->prev) //occurs whenever the node is in the middle of the list.
        {
            LN* subnode = node->next;
            node->next = NewListNode(ptr, node, subnode);
            subnode->prev = node->next;
            list->count++;
            return LI_I_S_ME;
        }
        else if(node->next || node->prev) //occurs when the node is at the end or the front of the list.
        {
            if(node->next && !node->prev) //front
            {
                LN* subnode = node->next;
                node->next = NewListNode(ptr, node, subnode);
                subnode->prev = node->next;
            }
            else if(!node->next && node->prev) //back
            {
                node->next = NewListNode(ptr, node, nullptr);
                list->end = node->next;
            }
            list->count++;
            return LI_I_S_OE;
        }
        else if(!node->next && !node->prev) //occurs when the list contains only 1 node.
        {
            node->next = NewListNode(ptr, node, nullptr);
            list->end = node->next;
            list->count++;
            return LI_I_S_OE;
        }
    }
    return LI_I_FAIL;
}
//inserts a value inside a list.
#define LI_I(list, li, ptr) ListIt_Insert(list, li, ptr)

void ListIt_Get(LI* li, void ** ptr)
{
    if(li)
        *ptr = li->node->pointer;
}
//With a pointer, it retrieves the value of the iterator.
#define LI_G(li, ptr) ListIt_Get(li, (void**) ptr)

//List
List* NewList()
{
    List* list = MALLOC_PTR(List);
    list->count = 0;
    list->end = list->start = nullptr;
    return list;    
}

void List_PushBack(List* list, void* ptr)
{
    if(list)
    {
        if(list->start)
            list->end = list->end->next = NewListNode(ptr, list->end, nullptr);
        else
            list->end = list->start = NewListNode(ptr, nullptr, nullptr);
        list->count++;
    }
}
//Adds an element at the end of the list
#define L_PB(list, ptr) List_PushBack(list, (void*)ptr)

void List_PushFront(List* list, void* ptr)
{
    if(list)
    {
        if(list->start)
            list->start = list->start->prev = NewListNode(ptr, nullptr, list->start);
        else 
            list->end = list->start = NewListNode(ptr, nullptr, nullptr);
        list->count++;
    }
}
//Adds an element at the beginning of the list
#define L_PF(list, ptr) List_PushFront(list, (void*)ptr)

void List_PopBack(List* list)
{
    if(list)
    {
        if(list->end)
        {
            if(list->start == list->end)
            {
                FreeListNode(list->end);
                list->end = nullptr;
                list->start = nullptr;
            }
            else
            {
                LN* subnode = list->end;
                list->end = list->end->prev;
                FreeListNode(subnode);
                list->end->next = nullptr;
            }
            list->count--;
        }
    }
}
//removes an element from the list
#define L_POB(list) List_PopBack(list)

void List_PopFront(List* list)
{
    if(list)
    {
        if(list->start)
        {
            if(list->start == list->end)
            {
                FreeListNode(list->end);
                list->end = nullptr;
                list->start = nullptr;
            }
            else
            {
                LN* subnode = list->start;
                list->start = list->start->next;
                FreeListNode(subnode);
                list->start->prev = nullptr;
            }
            list->count--;
        }
    }
}
//removes an element from the list
#define L_POF(list) List_PopFront(list)

LI List_MakeIterator(List* list)
{
    if(list)
        return SetListIt(list->start);
    return {nullptr};
}
//Creates an iterator of the list. To use inside functions!
#define L_MI(list) List_MakeIterator(list)

#endif
