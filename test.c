#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <limits.h>


#define clear() wprintf(L"\e[1;1H\e[2J")
#define QUEUE_EMPTY INT_MIN

void example(int num, char* files[100])
{
 
}

int main(void) 
{

  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt); //storing terminal settings in oldt
  newt = oldt; //copying oldt to newt
  newt.c_lflag &= ~(ICANON | ECHO); //Turning off canoninal input bit and echo bit
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  clear();

  DIR *d;
  char *files[100];
  struct dirent *dir;
  int count = 1;
  files[0] = ".start";
  d = opendir("./examples");
  if(d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      if(strstr(dir->d_name, ".txt"))
      {
        files[count] = dir->d_name;
        count++;
      }
    }
  }
  else
  {
    printf("That file couldn't be opened\n");
  }  files[count + 1] = ".end";
  for (int i = 0; i < count; i++)
  {
    wprintf(L"%s\n", files[i]);
  }
  
  
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  return 0;
}


/*
    .start[0]
    **********************
    File1 [1]
    **********************
    File2 [2]
    **********************
    File3 [3]
    **********************
    File4 [4]
    **********************
    File5 [5]
    **********************
    File6 [6]
    **********************
    File7 [7]
    **********************
    File8 [8]
    **********************
    File9 [9]
    **********************
    .end  [10]
*/

/*
  1 = [8,9,1,2,3]
  2 = [9,1,2,3,4]
  3 = [1,2,3,4,5]
  4 = [2,3,4,5,6]
  5 = [3,4,5,6,7]
  6 = [4,5,6,7,8]
  7 = [5,6,7,8,9]
  8 = [6,7,8,9,1]
  9 = [7,8,9,1,2]
*/