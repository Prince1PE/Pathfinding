#include "../classes/queue.h"
#include "../classes/node.h"
#include "../Grid.h"

void bfsSearch(queue* q)  
{
    int x,y;
    queuedElement *head = (queuedElement*)q->front;
    int i = head->data[0];
    int j = head->data[1];
    ranArray[i][j].colour = 2;

    x = i + 1;
    y = j;
    if (ranArray[x][y].visited == false)//Up
    {
        enqueue(q, x, y);
        setNode(0, x, y, i, j);
    }
    x = i;
    y = j - 1;
    if (ranArray[x][y].visited == false)//left
    {
        enqueue(q, x, y);
        setNode(0, x, y, i, j);
    }
    x = i;
    y = j + 1;
    if (ranArray[x][y].visited == false)//right
    {
        enqueue(q, x, y);
        setNode(0, x, y, i, j);
    }
    x = i - 1;
    y = j;
    if (ranArray[x][y].visited == false)//Down
    {
        enqueue(q, x, y);
        setNode(0, x, y, i, j);
    }
    dequeue(q);  
}


// int main()
// {
    // int height = 10;
    // int width = 10;
    // int MAX = height * width;
    // setlocale(LC_CTYPE, "");
    // makeGrid(height, width);
    // int counter = 1;
    // int startNodeX = 5;
    // int startNodeY = 7;
    // int exitNodeX = 3;
    // int exitNodeY = 4;
    // int currentCovered, pastCovered;
    // ranArray[startNodeX][startNodeY].visited = true;
    // ranArray[startNodeX][startNodeY].distance = 0;
    // ranArray[startNodeX][startNodeY].type = enterSymbol;
    // ranArray[exitNodeX][exitNodeY].type = exitSymbol;
//     queue *q;
//     q = malloc(sizeof(queue));
//     initialize(q);
//     enqueue(q, startNodeX, startNodeY);
    
//     while(!isempty(q) && ranArray[exitNodeX][exitNodeY].visited == false)
//     {
//         bfsSearch(q);
//         usleep(100000);
//         printGrid(height, width);
//         clear();
//     }
//     if (ranArray[exitNodeX][exitNodeY].visited)
//     {
//         traceBack(height, width, exitNodeX, exitNodeY, startNodeX, startNodeY, 1);
//     }
    
//     freeGrid(height, width);
//     return 0;

// }