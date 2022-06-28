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

void draw(int height, int width, int stackSize, int stack[stackSize][2], int *top)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ( (i % 2 == 0 || j % 2 == 0 ) && i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                ranArray[i][j].type = whiteBlock;
            }
        }
    }
    int ranX = 0;
    int ranY = 0;
    while(ranArray[ranX][ranY].type != '_')
    {
        ranX = rand()%((height+1)-2) + 1;
        ranY = rand()%((width +1)-2) + 1;
    }
    ranArray[ranX][ranY].type = enterSymbol; 
    ranArray[ranX][ranY].distance = 0;
    push(ranX, ranY, stackSize, stack, top);
}

void shuffle(int *array, size_t n) {    
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

int mapNeighbours(int height, int width, int stackSize, int stack[stackSize][2], int top)  
{
    int x, y, valx, valy, turn;
    int array[4] = {1,2,3,4};
    int nodeX = stack[top][0];
    int nodeY = stack[top][1];
    shuffle(array, 4);
    
        for(int pos = 0; pos < 4; pos++)
        {
            turn = array[pos];
            if(turn == 1)
            {
                x = nodeX;
                y = nodeY - 2;
                if (ranArray[x][y].visited == false && y > 0)//left
                {
                    // mapSurrounding(height, width, counter, x, y, i, j);
                    ranArray[x][y].parentNode[0] = nodeX;
                    ranArray[x][y].parentNode[1] = nodeY - 1;
                    push(x, y, stackSize, stack, &top);
                    ranArray[x][y].visited = true;
                    ranArray[x][y].colour = 2;
                    printf("1\n");
                }
            // printf("-%i, %i\n", ranArray[x][y].parentNode[0], ranArray[x][y].parentNode[1]);
            }
            else if(turn == 2)
            {
                x = nodeX;
                y = nodeY + 2;
                if (ranArray[x][y].visited == false && y < width - 1)//right
                {
                    // mapSurrounding(height, width, counter, x, y, i, j);
                    ranArray[x][y].parentNode[0] = nodeX;
                    ranArray[x][y].parentNode[1] = nodeY + 1;
                    push(x, y, stackSize, stack, &top);
                    ranArray[x][y].visited = true;
                    ranArray[x][y].colour = 2;
                    printf("2\n");
                }
            // printf("-%i, %i\n", ranArray[x][y].parentNode[0], ranArray[x][y].parentNode[1]);
            }
            else if(turn == 3)
            {   
                x = nodeX - 2;
                y = nodeY;
                if (x > 0 && ranArray[x][y].visited == false)//Up
                {
                    // mapSurrounding(height, width, counter, x, y, i, j);
                    ranArray[x][y].parentNode[0] = nodeX - 1;
                    ranArray[x][y].parentNode[1] = nodeY;
                    push(x, y, stackSize, stack, &top);
                    ranArray[x][y].visited = true;
                    ranArray[x][y].colour = 2;
                    printf("3\n");
                }
                // printf("-%i, %i\n", ranArray[x][y].parentNode[0], ranArray[x][y].parentNode[1]);
            }
            else
            {
                x = nodeX + 2;
                y = nodeY;
                if (x < height - 1 && ranArray[x][y].visited == false)//Down
                {
                    // mapSurrounding(height, width, counter, x, y, i, j);
                    ranArray[x][y].parentNode[0] = nodeX + 1;
                    ranArray[x][y].parentNode[1] = nodeY;
                    push(x, y, stackSize, stack, &top);
                    ranArray[x][y].visited = true;
                    ranArray[x][y].colour = 2;
                    printf("4\n");
                }
                // printf("-%i, %i\n", ranArray[x][y].parentNode[0], ranArray[x][y].parentNode[1]);
            }
        
    }
    return top;
}

void makePath(int stackSize, int stack[stackSize][2], int top)
{
    int x = ranArray[stack[top][0]][stack[top][1]].parentNode[0];
    int y = ranArray[stack[top][0]][stack[top][1]].parentNode[1];
    ranArray[x][y].type = '_';
    ranArray[x][y].colour = 6;
    // pop(stackSize, stack, &top);
}

int main()
{
    setlocale(LC_CTYPE, "");
    srand(time(NULL));
    int height = 12;
    int width = 12;
    int top = -1;
    int stackSize = height * width;
    int stack[stackSize][2];
    int element1, element2;
    int entryNodes[2] = {0, 0};
    makeGrid(height, width);
    draw(height, width, stackSize, stack, &top);
    top = mapNeighbours(height, width, stackSize, stack, top);
    printGrid(height, width);
    makePath(stackSize, stack, top);
    printGrid(height, width);

    while(!stackEmpty(stackSize, stack, &top))
    {
        printf("%i, %i\n", stack[top][0], stack[top][1]);
        pop(stackSize, stack, &top);
    }

    // ranArray[ranArray[stack[top][0]][stack[top][1]].parentNode[0]][ranArray[stack[top][0]][stack[top][1]].parentNode[1]].colour = 6;
    
    freeGrid(height, width);

    return 0;
}