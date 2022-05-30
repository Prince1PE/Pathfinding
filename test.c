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

// #define clear() wprintf(L"\e[1;1H\e[2J")
// #define gotoxy(x,y) wprintf(L"\033[%d;%dH", (y), (x)) //macro to move cursor
#define mouse() printf("\e[?1003h\e[?1015h\e[?1006h", (mousePos))


int main()
{

    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt); //storing terminal settings in oldt
    newt = oldt; //copying oldt to newt
    newt.c_lflag &= ~(ICANON | ECHO); //Turning off canoninal input bit and echo bit
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    char* mousePos;
    int pid = fork();
    if (pid == 0)
    {
        mouse();
        while (fread(mousePos, 25, 999, stdin))
        {
            if (mouse )
            {
                /* code */
            }
            
        }
        
        
    }
    else
    {
        sleep(5);
        printf("\e[?1000l");
    }
    return 0;  // make sure your main returns int

}
