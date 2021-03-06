#ifndef GRID
#define GRID


#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "classes/node.h"
#include "Algorithms/bruteforce.h"
#include "Algorithms/astar.h"
#include "Algorithms/dfsPathfinding.h"
// #include "Algorithms/bfsPathfinding.h"
#include "MazeGeneration/dfsMazeGeneration.h"
#include "MazeGeneration/kruskals.h"
#include "FileIO.h"

//Defining a bunch of unicode Charecters
wchar_t upperHalfBlock = 0x2580;    // ▀
wchar_t dot = 0x2022;
wchar_t rightHalfBlock = 0x2590;    // ▐
wchar_t leftHalfBlock = 0x258C;     // ▌
wchar_t lowerHalfBlock = 0x2584;    // ▄
wchar_t underscore = '_';
wchar_t whiteBlock = 0x2586;        // ⊞
wchar_t enterSymbol = 0x2386;       // ⎆
wchar_t exitSymbol = 0x23CE;        // ⏎

#define gotoxy(x,y) wprintf(L"\033[%d;%dH", (y), (x)) //macro to move cursor
#define clear() wprintf(L"\e[1;1H\e[2J")


//Used to make sure there is no repeats of return or enter charecters
int replaceGridChars(int placeX, int placeY, wchar_t placeChar, int height, int width) 
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(ranArray[i][j].type != placeChar)
            {
                continue;
            }
            else
            {
                ranArray[i][j].type = '_';
                ranArray[placeX][placeY].type = placeChar;
                return 0;
            }
        }
    }
    ranArray[placeX][placeY].type = placeChar;
    return 0;
}

//Allows the user to change the colours
const char* changeColours(int colour)
{
    
    switch (colour)
    {
    case 1:
        return "\033[1;30m";   //Changes to black
    case 2:
        return "\033[1;31m";   //Changes to red
    case 3:
        return "\033[1;32m";   //Changes to green
    case 4:
        return "\033[1;33m";   //Changes to yellow
    case 5:
        return "\033[1;34m";   //Changes to blue
    case 6:
        return "\033[1;35m";   //Changes to purple
    case 7:
        return "\033[1;36m";   //Changes to cyan
    case 8:
        return "\033[1;37m";   //Changes to white
    default:
        return "";
    }
}

void refresh(int height, int width)
{
   for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (ranArray[i][j].dirty == true)
            {
                gotoxy(i * 2, j + 1);
                wprintf(L"%s%lc", changeColours(ranArray[i][j].colour), ranArray[i][j].type);
                ranArray[i][j].dirty = false;
            }
        }
    }
}

void printGrid(int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            wprintf(L"%s", changeColours(ranArray[i][j].colour));
            wprintf(L"%lc", ranArray[i][j].type);

            if (j == width - 2)
            {
                continue;
            }

            else if ((ranArray[i][j].type == upperHalfBlock ||ranArray[i][j].type == lowerHalfBlock) && j < width - 3) 
            { 
                wprintf(L"%lc", ranArray[i][j].type);
            }

            else if ((i > 0 && j > 0) && (i < height - 1) && (j < width - 1))
            {
                wprintf(L"\033[0;37m");
                wprintf(L"|");
            }
        }
        wprintf(L"\n");
    }
}



void traceBack(int height, int width, int exitNodeX, int exitNodeY, int startNodeX, int startNodeY, bool visual)
{
    int backX = exitNodeX;
    int backY = exitNodeY;
    int tempX, tempY;

    while(ranArray[backX][backY].type != enterSymbol)
    {
        ranArray[backX][backY].colour = 4;
        ranArray[backX][backY].type = dot;
        ranArray[exitNodeX][exitNodeY].type = exitSymbol;
        ranArray[exitNodeX][exitNodeY].colour = 8;
        tempX = ranArray[backX][backY].parentNode[0];   //Probably inneficient
        tempY = ranArray[backX][backY].parentNode[1];
        backX = tempX;
        backY = tempY;
        if(visual)
        {
            usleep(100000);
            clear();
            printGrid(height, width);
        }
        else
        {
            refresh(height, width);
        }
    }
    clear();
    printGrid(height, width);
}

void makeGrid(int height, int width)
{
    ranArray = (struct Node**)malloc(height * sizeof(struct Node*));
    for(int i = 0; i < height; i++){ranArray[i] = (struct Node*) malloc(width * sizeof(struct Node));}

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ranArray[i][j].colour = 8;
            ranArray[i][j].visited = true;
            ranArray[i][j].parentNode[0] = 0;
            ranArray[i][j].parentNode[1] = 0;
            if(i == 0)
            {
                ranArray[i][j].type = lowerHalfBlock;
            }    //The top row is the upper half blocks

            else if(i == height - 1)
            {
                ranArray[i][j].type = upperHalfBlock;
            } //The bottom row is lower half blocks
            else if(j == 0)
            {
                ranArray[i][j].type = leftHalfBlock;
            }    //The left row is left half
            else if(j == width - 1)
            {
                ranArray[i][j].type = rightHalfBlock;
            }   //The right row is right hlaf
            else
            {
                ranArray[i][j].type = underscore;
                ranArray[i][j].visited = false;
                ranArray[i][j].distance = -1;
            }
        }
    }
}

void freeGrid(int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        free(ranArray[i]);
    }
    free(ranArray);
}

bool checkCondition(int height, int width)    //Checks for entry and exit nodes within the program
{
    int check = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (ranArray[i][j].type == enterSymbol || ranArray[i][j].type == exitSymbol)
            {
                check++;
            }
        }
    }
    if (check < 2)
    {
        return false;   
    }
    else
    {
        return true;
    }
}

void importGrid(int height, int width, char* filename)
{
    FILE *fp = fopen(filename, "r");
    char buffer[500];
    char* token;
    for (int i = 0; i < height; i++)
    {
        fgets(buffer, 500, (FILE*) fp);
        token = strtok(buffer, ",");
        for (int j = 0; j < width; j++)
        {
            ranArray[i][j].colour = 8;
            ranArray[i][j].visited = true;
            ranArray[i][j].parentNode[0] = 0;
            ranArray[i][j].parentNode[1] = 0;
            if(i == 0)
            {
                ranArray[i][j].type = lowerHalfBlock;
            }    //The top row is the upper half blocks

            else if(i == height - 1)
            {
                ranArray[i][j].type = upperHalfBlock;
            } //The bottom row is lower half blocks
            else if(j == 0)
            {
                ranArray[i][j].type = leftHalfBlock;
            }    //The left row is left half
            else if(j == width - 1)
            {
                ranArray[i][j].type = rightHalfBlock;
            }   //The right row is right hlaf
            else
            {
                if(strcmp(token, "1") == 0)
                {
                    ranArray[i][j].type = whiteBlock;
                    ranArray[i][j].visited = true;
                    ranArray[i][j].distance = 999;
                    ranArray[i][j].colour = 8;
                }
                else
                {
                    ranArray[i][j].type = underscore;
                    ranArray[i][j].visited = false;
                    ranArray[i][j].distance = -1;
                }
            }
            token = strtok(NULL, ",");
        }
    }
}

void writeGrid(int height, int width, char filename[100])
{
    char writefile[112] = "./examples/";
    strncat(writefile, filename, 100);
    FILE *fptr = fopen(writefile, "w");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(ranArray[i][j].type == 9094 || ranArray[i][j].type == 9166)
            {
                continue;
            }
            else if(ranArray[i][j].type == 9606)
            {
                fprintf(fptr, "1,");
            }
            else
            {
                fprintf(fptr, "0,");
            }
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);

}

void resetGrid(int height, int width)
{
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            if (ranArray[i][j].type == '_' || ranArray[i][j].type == dot)
            {
                ranArray[i][j].type = '_';
                ranArray[i][j].visited = false;
                ranArray[i][j].distance = -1;
                ranArray[i][j].colour = 8;
            }
            else if(ranArray[i][j].type == exitSymbol)
            {
                ranArray[i][j].visited = false;
                ranArray[i][j].distance = -1;
                
            }
        }
    }
    clear();
    printGrid(height, width);
}

int dfsFunc(int height, int width, bool visual)
{
    int stackSize = height * width;
    int stack[stackSize][2];
    draw(height, width, stackSize, stack);
    
    while(!stackEmpty(stackSize, stack, &top))
    {
        if(mapNeighbours(height, width, stackSize, stack))
        {
            makePath(stackSize, stack);
        }
        else
        {
            ranArray[ranArray[stack[top][0]][stack[top][1]].parentNode[0]]
            [ranArray[stack[top][0]][stack[top][1]].parentNode[1]].type = '_';
            popFromStack(stackSize, stack, &top);
        }
        if(visual)
        {
        usleep(90000);
        clear();
        printGrid(height, width);
        }
    }
    clear();
    printGrid(height, width);
    resetGrid(height, width);

    return 0;
}

void printTime(double timeTaken)
{
    if (timeTaken < 1)
    {
        wprintf(L"This took %g miliseconds\n", timeTaken * 1000);
    }
    else
    {
        wprintf(L"This took %g seconds\n", timeTaken);
    }
    
}
#endif

