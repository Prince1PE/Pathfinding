#include "Grid.h"


void mapAdjacent(int height, int width, struct Node ranArray[height][width],int startNodeX, int startNodeY, int exitNodeX, int exitNodeY)
{
    int counter = 1;
    int x,y;
    clear();
    int valx, valy;

    
    ranArray[startNodeX][startNodeY].visited = true;
    ranArray[startNodeX][startNodeY].distance = 0;
    while((
            (ranArray[1][1].visited == false) && 
            (ranArray[height - 2][width - 2].visited == false) && 
            (ranArray[1][width - 2].visited == false) && 
            (ranArray[height - 2][1].visited == false)) 
            || ranArray[exitNodeX][exitNodeY].visited == false)
    {
        Node CachedGrid = ranArray;
        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 1; j < width - 1; j++)
            {
                ranArray[startNodeX][startNodeY].colour = 8;
                if (ranArray[i][j].distance == counter - 1)
                {
                    // ranArray[i][j].type = underscore;
                    
                    ranArray[i][j].colour = 2;
                    x = i;
                    y = j - 1;
                    if (ranArray[x][y].visited == false)
                    {
                        ranArray[x][y].visited = true;
                        ranArray[x][y].distance = counter;
                        ranArray[x][y].parentNode[0] = i;
                        ranArray[x][y].parentNode[1] = j;
                    }
                    x = i;
                    y = j + 1;
                    if (ranArray[x][y].visited == false)
                    {
                        ranArray[x][y].visited = true;
                        ranArray[x][y].distance = counter;
                        ranArray[x][y].parentNode[0] = i;
                        ranArray[x][y].parentNode[1] = j;
                    }
                    x = i - 1;
                    y = j;
                    if (ranArray[x][y].visited == false)
                    {
                        ranArray[x][y].visited = true;
                        ranArray[x][y].distance = counter;
                        ranArray[x][y].parentNode[0] = i;
                        ranArray[x][y].parentNode[1] = j;
                    }
                    x = i + 1;
                    y = j;
                    if (ranArray[x][y].visited == false)
                    {
                        ranArray[x][y].visited = true;
                        ranArray[x][y].distance = counter;
                        ranArray[x][y].parentNode[0] = i;
                        ranArray[x][y].parentNode[1] = j;
                    }
                }
            }
        }
        counter ++;
        clear();
        printGrid(height, width, ranArray);
        usleep(150000);
    }
}

void traceBack(int height, int width, struct Node ranArray[height][width], int exitNodeX, int exitNodeY, int startNodeX, int startNodeY)
{
    int backX = exitNodeX;
    int backY = exitNodeY;
    int tempX, tempY;

    while(ranArray[backX][backY].distance != 0)
    {
        ranArray[backX][backY].colour = 4;
        ranArray[backX][backY].type = dot;
        ranArray[exitNodeX][exitNodeY].type = exitSymbol;
        ranArray[exitNodeX][exitNodeY].colour = 8;
        tempX = ranArray[backX][backY].parentNode[0];
        tempY = ranArray[backX][backY].parentNode[1];
        backX = tempX;
        backY = tempY;
        usleep(150000);
        clear();
        printGrid(height, width, ranArray);
    }
}
