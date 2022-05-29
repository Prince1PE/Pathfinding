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

#define clear() wprintf(L"\e[1;1H\e[2J")
#define gotoxy(x,y) wprintf(L"\033[%d;%dH", (y), (x)) //macro to move cursor


int main()
{
    system("wmctrl -F -r :ACTIVE: -b add,fullscreen");// Sets the terminal to fullscreen
    sleep(2);
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
    system("wmctrl -F -r :ACTIVE: -b remove,fullscreen");//Gets rid of the fullscreen
    return 0;  // make sure your main returns int

}
