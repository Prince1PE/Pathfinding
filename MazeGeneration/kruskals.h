#include <stdio.h>
#include "../Grid.h"

wchar_t underscore;

void shuffle2D(int maxEdges, int edges[maxEdges][2], int counter)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int usec = tv.tv_usec;
    srand48(usec);

    for (int i=0; i<counter; i++)
    {
        int r = (int) (drand48()*(i+1));
        for (int j = 0; j < 2; j++)
        {
            int temp =  edges[i][j];
            edges[i][j] =  edges[r][j];
            edges[r][j] = temp;
        }
    }
}

int makeEdges(int height, int width, int maxEdges ,int edges[maxEdges][2])
{
    int counter = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ( (i % 2 == 0 || j % 2 == 0 ) && //for every second column and row
                  i > 0 && i < height - 1 && //   Apart from the top and bottom border
                  j > 0 && j < width - 1 &&     //Apart from the left and right border
                  (ranArray[i][j].type == '_'))// and if its and underscore
            {
                ranArray[i][j].type = whiteBlock;   //Set it to a block
                ranArray[i][j].visited = true;
                ranArray[i][j].distance = 999;
                if(i % 2 == 0 ^ j % 2 == 0 && i != height - 2 && j != width - 2)
                {
                    edges[counter][0] = i;
                    edges[counter][1] = j;
                    ranArray[i][j].distance = -1;
                    counter++;
                }
                if(i % 2 == 1)
                {
                    ranArray[i][j].dirty = true;    //Dirty nodes, are ones that have a free space diagonally on each side
                }
            }
        }
    }
    return counter;
}    

void joinPath(int maxEdges, int edges[maxEdges][2], int counter, int height, int width, bool visual)
{
    shuffle2D(maxEdges, edges, counter);
    for(int i = 0; i < counter; i++)
    {
        int posX = edges[i][0];
        int posY = edges[i][1];
        // ranArray[posX][posY].colour = 3;
        int node1X, node1Y, node2X, node2Y;
        if (ranArray[posX][posY].dirty == true)
        {
            node1X = node2X = posX;
            node1Y = posY + 1;
            node2Y = posY - 1;
        }
        else
        {
            node1Y = node2Y = posY;
            node1X = posX + 1;
            node2X = posX - 1;
        }
        ranArray[node1X][node1Y].parentNode[0] = posX;
        ranArray[node2X][node2Y].parentNode[1] = posY;
        if (ranArray[node1X][node1Y].distance == - 1 && ranArray[node2X][node2Y].distance == -1)
        {
            ranArray[node1X][node1Y].distance = i;
            ranArray[node2X][node2Y].distance = i;
            ranArray[posX][posY].distance = i;
            ranArray[posX][posY].type = underscore;
            ranArray[posX][posY].visited = false;
        }
        else if(ranArray[node1X][node1Y].distance == - 1 || ranArray[node2X][node2Y].distance == -1)
        {
            if (ranArray[node1X][node1Y].distance == -1)
            {
                ranArray[node1X][node1Y].distance = ranArray[node2X][node2Y].distance;

            }
            else
            {
                ranArray[node2X][node2Y].distance = ranArray[node1X][node1Y].distance;
            }
            ranArray[posX][posY].distance = ranArray[node1X][node1Y].distance;
            ranArray[posX][posY].type = underscore;
            ranArray[posX][posY].visited = false;
        }
        else if(ranArray[node1X][node1Y].distance != ranArray[node2X][node2Y].distance)
        {
            int value, value2;
            if(ranArray[node1X][node1Y].distance > ranArray[node2X][node2Y].distance)
            {
                value = ranArray[node2X][node2Y].distance;
                value2 = ranArray[node1X][node1Y].distance;
                ranArray[node1X][node1Y].distance = ranArray[node2X][node2Y].distance;
            }
            else
            {
                value = ranArray[node1X][node1Y].distance;
                value2 = ranArray[node2X][node2Y].distance;
                ranArray[node2X][node2Y].distance = ranArray[node1X][node1Y].distance;
            }
            ranArray[posX][posY].distance = ranArray[node1X][node1Y].distance;
            ranArray[posX][posY].type = underscore;
            ranArray[posX][posY].visited = false;
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (ranArray[i][j].distance == value2)
                    {
                        ranArray[i][j].distance = value;
                    }
                    
                }
            }
        }
        else if(ranArray[node1X][node1Y].distance == ranArray[node2X][node2Y].distance)
        {
            continue;
        }
        if (visual)
        {
            clear();
            usleep(100000);
            printGrid(height, width);
        }
        
    }
}
