#ifndef dfsPath
#define dfsPath
#include <stdio.h>
#include <stdlib.h>
#include "../Grid.h"
#include "../classes/stack.h"

int ifred(int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (ranArray[i][j].colour == 2)
            {
                return 1;
            }
        }
    }
    return 0;
}


int dfsSearch(int height, int width, int startNodeX, int startNodeY, int exitNodeX, int exitNodeY, int stackSize, int stack[stackSize][2], int top, bool visual)  
{
    int x, y;
    ranArray[startNodeX][startNodeY].colour = 8;
    wchar_t enterSymbol = 0x2386;       // ⎆
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
    }
    x = i;
    y = j - 1;
    if (ranArray[x][y].visited == false)//left
    {
        pushToStack(x, y, stackSize, stack, &top);
        setNode(0, x, y, i, j);
        ranArray[x][y].visited = false;
    }
    x = i;
    y = j + 1;
    if (ranArray[x][y].visited == false)//right
    {
        pushToStack(x, y, stackSize, stack, &top);
        setNode(0, x, y, i, j);  
        ranArray[x][y].visited = false;  
    }
    x = i - 1;
    y = j;
    if (ranArray[x][y].visited == false)//Down
    {
        pushToStack(x, y, stackSize, stack, &top);
        setNode(0, x, y, i, j);
        ranArray[x][y].visited = false;
    }
    // int pastCovered;
    if(!stackEmpty(stackSize, stack, &top) && ranArray[exitNodeX][exitNodeY].visited == false && ifred(height, width))
    {
        if(visual)
        {
            usleep(100000);
            clear();
            printGrid(height,width);
        }
        dfsSearch(height, width, startNodeX, startNodeY, exitNodeX,exitNodeY, stackSize, stack, top, visual);
    }
    return 0;
    
}
#endif