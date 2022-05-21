#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include "class.h"



int main(void) {
  DIR *d;
  struct dirent *dir;
  d = opendir("./examples");
  char* filename = "smile1.txt";
  bool found = false;
  
  if (d) 
  {
    while ((dir = readdir(d)) != NULL)
    {
        if (strcmp(filename, dir->d_name) == 0)
        {
            printf("That file already exists\n");
            found = true;
            break;
        }
    }
    closedir(d);
    if (found ==false)
    {
        printf("You can use that file\n");
    }
    
  }
  return(0);
}