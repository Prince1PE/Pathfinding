#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>


#define gotoxy(x,y) wprintf(L"\033[%d;%dH", (y), (x)) //macro to move cursor

int main()
{
    double x = 5.120000;
    printf("%g\n", x);
    return 0;
}