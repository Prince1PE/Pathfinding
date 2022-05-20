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

int main()
{
    int height = 53
    struct Node* ranArray[height];
    char* filename = "./examples/bigmaze.txt";
    printf("%i * %i\n", countlines(filename), countrows(filename));
    return 0;
}