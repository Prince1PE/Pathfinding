#ifndef CLASSES
#define CLASSES

//Create the Node class
struct Node
{
    wchar_t type;
    int colour;
    int distance;
    bool visited;
    bool dirty;
    int parentNode[2];
};

static struct Node** ranArray;
#endif