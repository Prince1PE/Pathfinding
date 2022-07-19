#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <wchar.h>
#include <stdbool.h>

int countlines(char *filename)
{                                
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

int countColumns(char *filename)
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

bool scanDirectory(char filename[100])
{
    DIR *d;
    struct dirent *dir;
    if ((strchr(filename, '/') != NULL) && (strchr(filename, '.') != NULL))
    {
        wprintf(L"You can't use '/' or '.' in your filename because of linux");
        return false;
    }
    
    d = opendir("./examples");
    bool found = false;
    if (d) 
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(filename, dir->d_name) == 0)
            {
                wprintf(L"That file already exists\n");
                return 0;
            }
        }
        closedir(d);
        
        return 1;
    }
    else
    {
        wprintf(L"Unable to open file\n");
        return 0;
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

// int secCheck(char* filename)
// {
//     FILE *fp = fopen(filename, "r");
//     if(fp != NULL)
//     {
//         fseek(fp, 0, SEEK_END);
//         int size = ftell(fp);
//         if(size == 0)
//         {
//             return 1;
//         }
//     }
//     else
//     {
//         return 1;
//     }
//     return 0;
// }