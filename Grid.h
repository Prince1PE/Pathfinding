#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bruteforce.h"
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

#define gotoxy(x,y) wprintf(L"\033[%d;%dH", (y), (x)) //macro to move cursor
#define clear() wprintf(L"\e[1;1H\e[2J")


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
            wprintf(L"%s", changeColours(ranArray[i][j].colour));
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
                wprintf(L"\033[0;37m");
                wprintf(L"|");
            }
        }
        wprintf(L"\n");
    }
}

double mapAdjacent(int height, int width, struct Node ranArray[height][width],int startNodeX, int startNodeY, int exitNodeX, int exitNodeY)
{
    int counter = 1;
    int x,y;
    clear();
    int valx, valy;
    int currentCovered, pastCovered;
    
    ranArray[startNodeX][startNodeY].visited = true;
    ranArray[startNodeX][startNodeY].distance = 0;

    
    clock_t begin = clock();
    while((
            (ranArray[1][1].visited == false) && 
            (ranArray[height - 2][width - 2].visited == false) && 
            (ranArray[1][width - 2].visited == false) && 
            (ranArray[height - 2][1].visited == false)) 
            || ranArray[exitNodeX][exitNodeY].visited == false)
        {
            currentCovered = bruteForce(height, width, ranArray, startNodeX, startNodeY, counter, currentCovered);
            if (currentCovered == pastCovered)
            {
                return 0;
            }
            else{pastCovered = currentCovered;}
            counter ++;
            clear();
            printGrid(height, width, ranArray);
            usleep(150000);
        }
        clock_t end = clock();
        double time_taken = (double) ((end - begin) / 1000);
        return time_taken; 
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

bool checkCondition(int height, int width, struct Node ranArray[height][width], wchar_t entryNode, wchar_t exitNode)
{
    int check = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (ranArray[i][j].type == entryNode || ranArray[i][j].type == exitNode)
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






void importGrid(int height, int width, struct Node ranArray[height][width], char* filename)
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
                }
                else
                {
                    ranArray[i][j].type = underscore;
                }
                ranArray[i][j].visited = false;
                ranArray[i][j].distance = -1;
            }
            token = strtok(NULL, ",");
        }
    }
}

int countlines(char *filename)
{
  // count the number of lines in the file called filename                                    
  FILE *fp = fopen(filename,"r");
  int ch=0;
  int lines=0;

  if (fp == NULL)
  {
    return 0;
  }

  lines++;
  while(!feof(fp))  //Find alternative: https://stackoverflow.com/questions/5431941/why-is-while-feof-file-always-wrong
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }
  fclose(fp);
  return lines;
}

int countrows(char *filename)
{
    FILE *fp = fopen(filename,"r");
    char buffer[500];
    fgets(buffer, 500, (FILE*) fp);
    int count = 0;
    int elements = 0;
    while (buffer[count] != '\n')
    {
        if (buffer[count] == ',')
        {
            elements++;
            count++;
        }
        else
        {
            count++;
        }
    }
    fclose(fp);
    return elements;
}

void writeGrid(int height, int width, struct Node ranArray[height][width], char*filename)
{
    FILE *fptr = fopen(filename, "w");
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