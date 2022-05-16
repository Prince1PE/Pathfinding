#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bruteforce.h"


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

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x)) //macro to move cursor
#define clear() system("clear")

//Create the Node class
// struct Node
// {
//     wchar_t type;
//     int colour;
//     int distance;
//     bool visited;
//     int parentNode[2];
// };

struct Node node;

int replaceGridChars(int placeX, int placeY, wchar_t placeChar, int height, int width, struct Node ranArray[height][width])
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

void printGrid(int height, int width,struct Node ranArray[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%s", changeColours(ranArray[i][j].colour));
            wprintf(L"%lc", ranArray[i][j].type); //This is all it should take

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
                printf("\033[0;37m");
                printf("|");
            }
        }
        printf("\n");
    }
}

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
            bruteForce(height, width, ranArray, startNodeX, startNodeY, counter);
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

void makeGrid(int height, int width, struct Node ranArray[height][width])
{
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