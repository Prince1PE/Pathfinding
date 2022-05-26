#ifndef CLASSES
#define CLASSES

//Create the Node class
struct Node
{
    wchar_t type;
    int colour;
    int distance;
    bool visited;
    int parentNode[2];
    bool refreshed;
};

static struct Node** ranArray;
#endif