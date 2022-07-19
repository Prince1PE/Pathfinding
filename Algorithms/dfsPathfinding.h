#ifndef dfsPath
#define dfsPath
#include <stdio.h>
#include <stdlib.h>
#include "../Grid.h"
#include "../classes/stack.h"



int dfsSearch(int height, int width, int startNodeX, int startNodeY, int exitNodeX, int exitNodeY, int stackSize, int stack[stackSize][2], int top)  
{
    int x, y, valx, valy;
    ranArray[startNodeX][startNodeY].colour = 8;
    wchar_t enterSymbol = 0x2386;       // ⎆
    // int num = checkCount;
    int i = stack[top][0];
    int j = stack[top][1];
    ranArray[i][j].visited = true;
    ranArray[i][j].colour = 3;
    popFromStack(stackSize, stack, &top);
    x = i + 1;
    y = j;
    if (ranArray[x][y].visited == false)//Up
    {
        pushToStack(x, y, stackSize, stack, &top);
        setNode(0, x, y, i, j);
        ranArray[x][y].visited = false;
        // checkCount++;
    }
    x = i;
    y = j - 1;
    if (ranArray[x][y].visited == false)//left
    {
        pushToStack(x, y, stackSize, stack, &top);
        setNode(0, x, y, i, j);
        ranArray[x][y].visited = false;
        // checkCount++;
    }
    x = i;
    y = j + 1;
    if (ranArray[x][y].visited == false)//right
    {
        pushToStack(x, y, stackSize, stack, &top);
        setNode(0, x, y, i, j);  
        ranArray[x][y].visited = false;  
        // checkCount++;
    }
    x = i - 1;
    y = j;
    if (ranArray[x][y].visited == false)//Down
    {
        pushToStack(x, y, stackSize, stack, &top);
        setNode(0, x, y, i, j);
        ranArray[x][y].visited = false;
        // checkCount++;
    }
    if(!stackEmpty(stackSize, stack, &top) && ranArray[exitNodeX][exitNodeY].visited == false)
    {
        usleep(100000);
        clear();
        printGrid(height,width);
        dfsSearch(height, width, startNodeX, startNodeY, exitNodeX,exitNodeY, stackSize, stack, top);
    }
    return 0;
    
}
#endif