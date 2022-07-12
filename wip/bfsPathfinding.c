#include <stdio.h>
#include <stdlib.h>
#include "Grid.h"
#include "class.h"

int bfs(int height, int width,int startNodeX, int startNodeY, int counter, int checkCount, int stackSize, int stack[stackSize][2])  
{
    int x, y, valx, valy;
    ranArray[startNodeX][startNodeY].colour = 8;
    
    int i = stack[top][0];
    int j = stack[top][1];
    pop(stackSize, stack, &top);
        
    ranArray[i][j].colour = 2;

    x = i - 1;
    y = j;
    if (ranArray[x][y].visited == false)//Up
    {
        push(x, y, stackSize, stack, &top);
        setNode(counter, x, y, i, j);
        return checkCount;
    }
    x = i;
    y = j - 1;
    if (ranArray[x][y].visited == false)//left
    {
        push(x, y, stackSize, stack, &top);
        setNode(counter, x, y, i, j);
        return checkCount;
    }
    x = i;
    y = j + 1;
    if (ranArray[x][y].visited == false)//right
    {
        push(x, y, stackSize, stack, &top);
        setNode(counter, x, y, i, j);                   
        return checkCount;
    }
    x = i + 1;
    y = j;
    if (ranArray[x][y].visited == false)//Down
    {
        push(x, y, stackSize, stack, &top);
        setNode(counter, x, y, i, j);
        return checkCount;
    }
    
    return checkCount;
}

int main()
{
    int height = 10;
    int width = 10;
    int counter = 1;
    int startNodeX = 5;
    int startNodeY = 3;
    int stackSize = height * width;
    int stack[stackSize][2], checkcount;

    setlocale(LC_CTYPE, "");

    makeGrid(height, width);
    int x, y;
    int currentCovered = 0;
    int pastCovered = -1;
    push(startNodeX, startNodeY, stackSize, stack, &top);
    while(true)
    {
        
        if(currentCovered == pastCovered)
        {
            wprintf(L"FINISHED\n");
            break;
        }
        else
        {
            pastCovered = currentCovered;
        }
        currentCovered = bfs(height, width, startNodeX, startNodeY, counter, checkcount, stackSize, stack);
        printGrid(height, width);
    }
    return 0;

}
