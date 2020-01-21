#ifndef C_LIST_HEADER
#define C_LIST_HEADER

// ListNode
// Contains the data and links to other nodes in a list.
struct ListNode
{
    void* pointer;
    ListNode* prev, * next;
};

ListNode* NewListNode(void* pointer, ListNode* prev, ListNode* next)
{
    ListNode* node = MALLOC_PTR(ListNode);
    node->next = next;
    node->prev = prev;
    node->pointer = pointer;
    return node;
}

void FreeListNode(ListNode* node)
{
    if(node)
    {
        free(node);
        node = nullptr;
    }
}

//A ListIterator is a ListNode, but disguised. (To differentiate a Node and an Iterator)
typedef ListNode ListIterator;

bool ListIt_Next(ListIterator* it)
{
    if(it)
    {
        if(it->next)
        {
            it = it->next;
            return true;
        }
    }
    return false;
}

bool ListIt_Prev(ListIterator* it)
{
    if(it)
    {
        if(it->prev)
        {
            it = it->prev;
            return true;
        }
    }
    return false;
}

//A "#define" tag is used here to facilitate the conversion from void* to a certain type.
#define ListIt_Data(type, iterator) (type) iterator->pointer

//A list is a useful data structure.
struct List
{
    ListNode* first, * last;
    uint count;
};

List* NewList()
{
    List* list = MALLOC_PTR(List);
    list->count = 0;
    list->first = list->last = nullptr;
    return list;
}

//Note: "ptr" stands for "pointer"
void List_pushBack(List* list, void* ptr)
{
    if(list)
    {
        
    }
}
void List_pushFront(List* list, void* ptr)
{

}
void List_insert(List* list, ListIterator* it, void* ptr)
{

}
void List_remove(List* list, ListIterator* it)
{

}
void List_popBack()
{

}

void List_popFront()
{
    
}

void FreeList(List* list)
{
    if(list)
    {
        if(list->first)
        {

        }
    }
}
#endif
