#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <typeinfo.h>

#define MALLOC_ARRAY(TYPE, LENGTH) (TYPE*) malloc(sizeof(TYPE) * LENGTH)
#define MALLOC_PTR(TYPE) (TYPE*) malloc(sizeof(TYPE))

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

struct slnode
{
	void* pointer;
	slnode* next;
	slnode* prev;
};

slnode* NewSLNode(void* pointer, slnode* prev, slnode* next)
{
	slnode* node = MALLOC_PTR(slnode);
	node->pointer = pointer;
	node->next = next;
	node->prev = prev;
	return node;
}

void FreeSLNode(slnode* node)
{
	if(node)
	{
		free(node);
		node = nullptr;
	}
}

//--------------
struct List
{
	char * type;
	slnode* first;
	slnode* last;
	uint count;
}

#define NewList(TYPE)\
List* RestrictedNewList()\
{\
	List* list = MALLOC_PTR(List);\
	list->type = typeid(TYPE).name();\
	list->first = list->last = nullptr;\
	list->count = 0;\
}\

#endif
