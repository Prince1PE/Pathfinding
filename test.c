#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Grid.h"
#include "class.h"

#define clear() wprintf(L"\e[1;1H\e[2J")
#define gotoxy(x,y) wprintf(L"\033[%d;%dH", (y), (x)) //macro to move cursor

void refresh1(int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (ranArray[i][j].type == '_')
            {
                gotoxy(i * 2, j + 1);
                wprintf(L"%s%lc", changeColours(4), ranArray[i][j].type);
            }
            else
            {
                gotoxy(i,j);
                wprintf(L"%lc", ranArray[i][j].type);
            }
        }
    }
}

int listDirectory(char* filename)
{
    DIR *d = opendir(filename);
    struct dirent *dir;

    if (d)
    {
        wprintf(L"*------------------------------------*\n");
        while((dir = readdir(d)) != NULL)
        {
            if (strstr(dir->d_name, ".txt"))
            {
                wprintf(L"◉  %s\n", dir->d_name);
            }
        }
        wprintf(L"*------------------------------------*\n");
    }
    else
    {
            wprintf(L"File not found\n");
            return 1;
    }
    closedir(d);
    return 0;
}


int main()
{
    setlocale(LC_CTYPE, "");
    int height, width;
    width = height = 50;
    listDirectory("./examples");
	return 0;

}
