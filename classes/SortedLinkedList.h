#include <stdio.h>
#include <stdlib.h>

/* structure declaration */
typedef struct  OrderedList {
                      struct OrderedList *link;
                      int nodeCost;
                      int x;
                      int y;

        } OrderedList;
 
void insert_sll(OrderedList **linkp, const int nodeCost, int x, int y)
{
    OrderedList *current = 0;
    OrderedList *newnode = 0;
 
    /* Let's create an ordered singly linked list */
    while ((current = *linkp) != NULL && current->nodeCost < nodeCost)
        linkp = &current->link;
 
    /* Let's allocate memory to newnode */
    newnode = (OrderedList *)malloc(sizeof(OrderedList));
    
    /* If memory allocated to newnode unsuccessfully */
    if (newnode == NULL) {
        wprintf(L"Not sufficient Memory!\n");
        exit(EXIT_FAILURE);
    }
 
    /* write in value in value field of newnode */
    newnode->nodeCost = nodeCost;
    
    /* insert newnode in the list */
    /* between current and previous */
    newnode->link = current;
    newnode->x = x;
    newnode->y = y;
    *linkp = newnode;
}

bool isEmpty_sll(OrderedList **linkp)
{
    OrderedList *current = *linkp;
    if (current == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void pop_sll(OrderedList **linkp)
{
    struct OrderedList *temp = *linkp;
    *linkp = temp->link;
    free(temp);
    return;
}
static OrderedList *root = 0;
OrderedList **p2r = &root;

