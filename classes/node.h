#ifndef NODE
#define NODE
#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>

//Create the Node class
struct Node
{
    wchar_t type;
    int colour;
    int distance;
    bool visited;
    int parentNode[2];
    bool dirty;
};

static struct Node** ranArray;


#endif
