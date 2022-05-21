#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "class.h"

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

void makeGrid(int height, int width, struct Node** ranArray[1])
{
    ranArray[0] = (struct Node**)malloc(height * sizeof(struct Node*));
    for(int i = 0; i < height; i++){ranArray[0][i] = (struct Node*) malloc(width * sizeof(struct Node));}

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ranArray[0][i][j].colour = 8;
            ranArray[0][i][j].visited = true;
            ranArray[0][i][j].parentNode[0] = 0;
            ranArray[0][i][j].parentNode[1] = 0;
            if(i == 0)
            {
                ranArray[0][i][j].type = lowerHalfBlock;
            }    //The top row is the upper half blocks

            else if(i == height - 1)
            {
                ranArray[0][i][j].type = upperHalfBlock;
            } //The bottom row is lower half blocks
            else if(j == 0)
            {
                ranArray[0][i][j].type = leftHalfBlock;
            }    //The left row is left half
            else if(j == width - 1)
            {
                ranArray[0][i][j].type = rightHalfBlock;
            }   //The right row is right hlaf
            else
            {
                ranArray[0][i][j].type = underscore;
                ranArray[0][i][j].visited = false;
                ranArray[0][i][j].distance = -1;
            }
        }
    }
}

void freeGrid(int height, int width, struct Node** ranArray[1])
{
    for (int i = 0; i < height; i++)
    {
        free(ranArray[0][i]);
    }
    free(ranArray[0]);
}

void printGrid(int height, int width,struct Node** ranArray[1])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            wprintf(L"%lc", ranArray[0][i][j].type);

            if (j == width - 2)
            {
                continue;
            }

            else if ((ranArray[0][i][j].type == upperHalfBlock ||ranArray[0][i][j].type == lowerHalfBlock) && j < width - 3) 
            { 
                wprintf(L"%lc", ranArray[0][i][j].type);
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

int main()
{
    int height;
    int width;
    struct Node **ranArray[1];
    setlocale(LC_CTYPE, "");    //Allows you to enter unicode charecters

    height = 10;
    width = 10;
    makeGrid(height, width, ranArray);
    printGrid(height, width, ranArray);
    freeGrid(height, width, ranArray);

    height = 50;
    width = 50;
    makeGrid(height, width, ranArray);
    printGrid(height, width, ranArray);
    freeGrid(height, width, ranArray);


    height = 20;
    width = 20;
    makeGrid(height, width, ranArray);
    printGrid(height, width, ranArray);
    freeGrid(height, width, ranArray);


    return 0;
}