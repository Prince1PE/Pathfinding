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


int main()
{
    setlocale(LC_CTYPE, "");
    int height, width;
    width = height = 50;

	clear();
	makeGrid(height, width);
    printGrid(height, width);
    refresh1(height, width);
    gotoxy(1,500);
	return 0;

}
