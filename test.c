#include "Grid.h"
#include "classes/node.h"
#include "classes/queue.h"
#include "Algorithms/dfsPathfinding.h"

int main()
{
    int height = 10;
    int width = 10;

    setlocale(LC_CTYPE, "");
    makeGrid(height, width);
    int entryNodeX = 4;
    int entryNodeY = 3;
    int exitNodeX = 7;
    int exitNodeY = 8;
    int stacksize = height * width;
    int stack[stacksize][2];
    int counte = 1;
    int currentCovered = 0;
    ranArray[entryNodeX][entryNodeY].type = enterSymbol;
    ranArray[exitNodeX][exitNodeY].type = exitSymbol;
    int pastCovered;
    
    pushToStack(entryNodeX, entryNodeY, stacksize, stack, &top);
    // printf("%i, %i", stack[top][0], stack[top][1]);
    dfsSearch(height, width, entryNodeX, entryNodeY, exitNodeX,exitNodeY ,0, stacksize, stack, top);
}