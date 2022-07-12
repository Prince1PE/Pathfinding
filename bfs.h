#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Grid.h"
#include "class.h"

static int top = -1;    

void draw(int height, int width, int stackSize, int stack[stackSize][2])
{
    wchar_t whiteBlock = 0x2586;    
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
            }
        }
    }
    int ranX = 0;
    int ranY = 0;
    while(ranArray[ranX][ranY].type != '_')     //Chooses a random location on the grid to start
    {
        ranX = rand()%((height+1)-2) + 1;
        ranY = rand()%((width +1)-2) + 1;
    }
    push(ranX, ranY, stackSize, stack, &top);
}

void shuffle(int *array, size_t n) {    //Shuffles the array
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int usec = tv.tv_usec;
    srand48(usec);

    if (n > 1) {
        size_t i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48()*(i+1));
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

bool mapNeighbours(int height, int width, int stackSize, int stack[stackSize][2])  
{
    int x, y, valx, valy, turn;
    int array[4] = {1,2,3,4};
    int nodeX = stack[top][0];
    int nodeY = stack[top][1];
    bool mapped = false;//This checks to see whther or not to start mapping a different section of the grid
    shuffle(array, 4);

    for(int pos = 0; pos < 4; pos++)//Iterates through the array
        {
            turn = array[pos];

            x = nodeX;
            y = nodeY - 2;
            if (ranArray[x][y].visited == false && y > 0 && turn == 1)//left
            {
                ranArray[x][y].parentNode[0] = nodeX;// The parent node being the wall between the two spaces
                ranArray[x][y].parentNode[1] = nodeY - 1;
                push(x, y, stackSize, stack, &top); 
                ranArray[x][y].visited = true;
                mapped = true;
            }

            x = nodeX;
            y = nodeY + 2;
            if (ranArray[x][y].visited == false && y < width - 1 && turn == 2)//right
            {
                ranArray[x][y].parentNode[0] = nodeX;
                ranArray[x][y].parentNode[1] = nodeY + 1;
                push(x, y, stackSize, stack, &top);
                ranArray[x][y].visited = true;
                mapped = true;
            }
            
            x = nodeX - 2;
            y = nodeY;
            if (x > 0 && ranArray[x][y].visited == false && turn == 3)//Up
            {
                ranArray[x][y].parentNode[0] = nodeX - 1;
                ranArray[x][y].parentNode[1] = nodeY;
                push(x, y, stackSize, stack, &top);
                ranArray[x][y].visited = true;
                mapped = true;
                }
            
            x = nodeX + 2;
            y = nodeY;
            if (x < height - 1 && ranArray[x][y].visited == false && turn == 4)//Down
            {
                ranArray[x][y].parentNode[0] = nodeX + 1;
                ranArray[x][y].parentNode[1] = nodeY;
                push(x, y, stackSize, stack, &top);
                ranArray[x][y].visited = true;
                mapped = true;
            }
    }
    return mapped;
}

void makePath(int stackSize, int stack[stackSize][2])//this essneitally just changes one of the empty spaces to blocks
{
    int x = ranArray[stack[top][0]][stack[top][1]].parentNode[0];
    int y = ranArray[stack[top][0]][stack[top][1]].parentNode[1];
    ranArray[x][y].type = '_';
}

