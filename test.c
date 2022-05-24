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


int main()
{
    printf("1,2,3\n4,5,6\n7,8,9\n");
    gotoxy(1,1);
    printf("%s", changeColours(2));
}