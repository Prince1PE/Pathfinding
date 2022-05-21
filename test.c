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
#include "Grid.h"


int main()
{
    int height;
    int width;
    
    setlocale(LC_CTYPE, "");    //Allows you to enter unicode charecters

    height = 10;
    width = 10;
    makeGrid(height, width);
    printGrid(height, width);
    freeGrid(height, width);

    height = 50;
    width = 50;
    makeGrid(height, width);
    printGrid(height, width);
    freeGrid(height, width);


    height = 20;
    width = 20;
    makeGrid(height, width);
    printGrid(height, width);
    freeGrid(height, width);


    return 0;
}