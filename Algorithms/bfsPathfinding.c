#include "../classes/queue.h"
#include "../classes/node.h"
#include "../Grid.h"

int bfsSearch(queue* q, int currentCovered)  
{
    int x,y;
    queuedElement *head = (queuedElement*)q->front;
    int i = head->data[0];
    int j = head->data[1];
    ranArray[i][j].colour = 2;
    bool checked = false;
    x = i + 1;
    y = j;
    if (ranArray[x][y].visited == false)//Up
    {
        enqueue(q, x, y);
        setNode(0, x, y, i, j);
        currentCovered++;
    }
    x = i;
    y = j - 1;
    if (ranArray[x][y].visited == false)//left
    {
        enqueue(q, x, y);
        setNode(0, x, y, i, j);
        currentCovered++;
    }
    x = i;
    y = j + 1;
    if (ranArray[x][y].visited == false)//right
    {
        enqueue(q, x, y);
        setNode(0, x, y, i, j);
        currentCovered++;
    }
    x = i - 1;
    y = j;
    if (ranArray[x][y].visited == false)//Down
    {
        enqueue(q, x, y);
        setNode(0, x, y, i, j);
        currentCovered++;
    }
    dequeue(q);
    return currentCovered;
}


int main()
{
    int height = 10;
    int width = 10;
    int MAX = height * width;
    setlocale(LC_CTYPE, "");
    makeGrid(height, width);
    int currentCovered, pastCovered;
    int counter = 1;
    int startNodeX = 5;
    int startNodeY = 7;
    int exitNodeX = 1;
    int exitNodeY = 1;
    ranArray[startNodeX][startNodeY].visited = true;
    ranArray[startNodeX][startNodeY].distance = 0;
    ranArray[startNodeX][startNodeY].type = enterSymbol;
    ranArray[exitNodeX][exitNodeY].type = exitSymbol;

    ranArray[1][2].visited = true;
    ranArray[1][2].type = whiteBlock;
    ranArray[2][1].visited = true;
    ranArray[2][1].type = whiteBlock;

    queue *q;
    q = malloc(sizeof(queue));
    initialize(q);
    enqueue(q, startNodeX, startNodeY);
    queuedElement *head = q->front;
    
    while(ranArray[exitNodeX][exitNodeY].visited == false)
    {
        bfsSearch(q, currentCovered);
        clear();
        // usleep(100000);
        sleep(1);
        printGrid(height, width);
        wprintf(L"\n%i, %i\n", head->data[0], head->data[1]);
        
    }
    if (ranArray[exitNodeX][exitNodeY].visited)
    {
        traceBack(height, width, exitNodeX, exitNodeY, startNodeX, startNodeY, 1);
    }
    
    freeGrid(height, width);
    return 0;

}