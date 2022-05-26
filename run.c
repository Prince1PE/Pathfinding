#include "Grid.h"
#include <sys/time.h>
//TODO
//Add in something more complicated
//Add a timer  
//Use GotoXy, instead of refreshing screen
//Fix command line

static struct Node **ranArray;

int Play(int height, int width)
{
    bool help = true;   //Used for the help comand
    bool loop = true;   //Used to keep looping through the code
    char quit;          //Used for the quit command
    int x = width;
    int y = height;
    height += 2;    //takes into account, the top, bottom, left & right walls
    width += 2;
    srand(time(NULL));
    // struct Node **ranArray;    //Makes an array of nodes

    // node.type = upperHalfBlock; //Sets the default node charecter
    int colour = 8;             //Sets the default colour to white
    setlocale(LC_CTYPE, "");    //Allows you to enter unicode charecters

    int keystroke;
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt); //storing terminal settings in oldt
    newt = oldt; //copying oldt to newt
    newt.c_lflag &= ~(ICANON | ECHO); //Turning off canoninal input bit and echo bit
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    makeGrid(height, width);
    
    system("clear");
    printGrid(height, width);
    gotoxy(x, y);
    int startNodeX, startNodeY, exitNodeX, exitNodeY;
    int valx, valy;

    while (loop)
    {
        valx = y - 1; //Dont question it
        valy = x / 2;
        keystroke = getchar();
        if (keystroke == 'w')//Move up
        {
            if (y == 2)
            {
                y ++;
                gotoxy(x,y);
            }
           
            y --;
            gotoxy(x,y);
        }
        else if (keystroke == 'a')//Move left
        {
            if (x == 2)
            {
                x +=2;
                gotoxy(x,y);
            }
           
            x -= 2;
            gotoxy(x,y);
        }
        else if (keystroke == 's')//Move Down
        {
            if (y == height - 1)
            {
                y --;
                gotoxy(x,y);
            }
           
            y ++;
            gotoxy(x,y);
        }
        else if (keystroke == 'd')//Move Right
        {
            if (x >= (width * 2) - 4)
            {
                x -=2;
                gotoxy(x,y);

            }
            x += 2;
            gotoxy(x,y);
        }
        else if (keystroke == 'g')  //Troubleshooting key
        {
            clear();
            printGrid(height, width);
            wprintf(L"(%i,%i) -> (%i,%i) - %i", valx, valy ,ranArray[valx][valy].parentNode[0], ranArray[valx][valy].parentNode[1], ranArray[valx][valy].distance);
            wprintf(L"X:%i Y:%i\n", x, y);
            gotoxy(x, y);
        }    
        else if (keystroke == ' ')//Places Block
        {
            if (ranArray[valx][valy].type == '_')
            {
                ranArray[valx][valy].type = whiteBlock;
                ranArray[valx][valy].visited = true;
                ranArray[valx][valy].distance = 999;
                ranArray[valx][valy].colour = colour;
                clear();
            }

            else
            {
                ranArray[valx][valy].colour = 8;
                ranArray[valx][valy].type = '_';
                ranArray[valx][valy].visited = false;
                ranArray[valx][valy].distance = -1;
                clear();
            }
            printGrid(height, width);
            gotoxy(x, y);
        }    
        else if (keystroke == 'h')//Shows help menu
        {
            if(help)
            {
                clear();
                wprintf(L"Type space to enter/remove a block\n");
                wprintf(L"Type / to enter your command prompt, simply enter backspace to exit\n");
                wprintf(L"Type q to quit the program\n");
                wprintf(L"Use WASD to move\n\n");
                wprintf(L"\n\n Click h to exit");
                help = false;
            }
            else
            {
                help = true;
                clear();
                printGrid(height, width);
            }
        }        
        else if (keystroke == '/')  //Ignore this, im going to truy and make this work later
        {
            char buffer[100];
            memset(buffer, '\x00', 100);
            char* word;
            int counter = 0;
            char* command[20];
            clear();
            printGrid(height, width);
            wprintf(L"\n\n/");
            char c;

            while ((c = getchar()) != '\n' && c != EOF && strlen(buffer) != 100)
                {
                    if (c == 127)
                    {
                        buffer[strlen(buffer) - 1] = '\0';
                        clear();
                        printGrid(height, width);
                        wprintf(L"\n\n/%s", buffer);
                    }
                    else
                    {
                        wprintf(L"%c", c);
                        strncat(buffer, &c, 1);
                    }
                }      
            clear();
            printGrid(height, width);
            if(strlen(buffer) == 0)
            {
                continue;
            }
            
            word = strtok(buffer, " ");
            command[0] = word;
        

            while(word != NULL)
            {
                command[counter] = word;
                counter++;
                word = strtok(NULL, " ");
            }

            

            if(strlen(buffer) == 100)
            {
                wprintf(L"Stop trying to break the program >:( \n");
            }
            
            else if (!strcmp(command[0], "use"))
            {
                if (strcmp(command[1], "bruteforce") == 0)
                {
                    if(checkCondition(height, width, enterSymbol, exitSymbol))
                        {
                            struct timeval start, stop;
                            double time_taken = 0;
                            gettimeofday(&start, NULL);
                            if(mapAdjacent(height, width, startNodeX, startNodeY, exitNodeX, exitNodeY))
                            {
                                traceBack(height, width, exitNodeX, exitNodeY, startNodeX, startNodeY);
                                clear();
                                printGrid(height, width);
                                gettimeofday(&stop, NULL);
                                time_taken = (double) (stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
                                wprintf(L"%s Optimal Path Found!!!\n", changeColours(3));
                                wprintf(L"This took %f seconds\n", time_taken);
                            }
                            else
                            {
                                clear();
                                printGrid(height, width);
                                wprintf(L"%s PATH NOT FOUND", changeColours(2));
                            }
                                freeGrid(height, width);
                                makeGrid(height, width);
                        }
                    else
                    {
                        clear();
                        printGrid(height, width);
                        wprintf(L"%s Enter an exit & entry node\n", changeColours(4));
                    }
                    gotoxy(x, y);
                    }
                else
                {
                    clear();
                    printGrid(height, width);
                    wprintf(L"%sUnkown command\n", changeColours(4));
                }
            }
            
            else if (!strcmp(command[0], "clear"))
            {
                makeGrid(height, width);
                clear();
                printGrid(height, width);
                wprintf(L"%s Grid Cleared", changeColours(5));
            }
            
            else if (!strcmp(command[0], "resize"))
            {
                int resizeValueX, resizeValueY;
                resizeValueX = atoi(command[1]);
                if (resizeValueX && strlen(command[1]) > 0 && resizeValueX < 60)
                {
                    freeGrid(height, width);
                    resizeValueY = atoi(command[2]);
                    height = resizeValueX + 2;
                    if(resizeValueY && strlen(command[2]) > 0 && resizeValueX < 104)
                    {
                        width = resizeValueY + 2;
                    }
                    makeGrid(height, width);
                    clear();
                    printGrid(height, width);
                    gotoxy(x,y);
                }
                else
                {
                    wprintf(L"%sInvalid input\n", changeColours(4));
                }
            }
            
            else if (!strcmp(command[0], "export"))
            {
                clear();
                printGrid(height, width);
                if (command[1] == NULL)
                {
                    wprintf(L"Enter a filename\n");
                }
                else
                {
                    char filename[100];
                    strcpy(filename, command[1]); //This is safe because command[1] can never exceed 100 charecters
                    strncat(filename, ".txt", 5);
                    if(scanDirectory(filename))
                    {
                        writeGrid(height, width, filename);
                        clear();
                        printGrid(height, width);
                        wprintf(L"%s File has been saved to: examples/%s", changeColours(4), filename);
                    }
                }
            }
            
            else if (!strcmp(command[0], "random"))
            {
                freeGrid(height, width);
                makeGrid(height, width);
                for (int i = 1; i < height - 1; i++)
                {
                    for (int j = 1; j < width - 1; j++)
                    {
                        if ((rand() % 3) == 1)
                        {
                            ranArray[i][j].type = whiteBlock;
                            ranArray[i][j].visited = true;
                            ranArray[i][j].distance = 999;
                        }
                        
                    }
                }

                clear();
                printGrid(height, width);
                
            }

            else if (!strcmp(command[0], "import"))
            {
                clear();
                DIR *d = opendir("./examples");
                struct dirent *dir;
                if(strlen(command[1]) == 0)
                {
                    wprintf(L"Test1\n");
                    clear();
                    listDirectory("./examples");
                }

                else
                {
                    bool found = false;
                    if (d)
                    {
                        while((dir = readdir(d)) != NULL)
                        {
                            if (!strcmp(command[1], dir->d_name))
                            {
                                freeGrid(height, width);
                                char readfile[120] = "./examples";
                                strcat(readfile, command[1]);
                                height = countlines(readfile) - 1;
                                width = countrows(readfile);
                                makeGrid(height, width);
                                importGrid(height, width, readfile);
                                x = width - 2;
                                y = height - 2;
                                clear();
                                printGrid(height, width);
                                wprintf(L"%s File has been successfully imorted", changeColours(4));
                                gotoxy(x,y);
                            }
                            
                        }
                    }
                    else
                    {
                            wprintf(L"File not found\n");
                    }
                }
            
            }

            else
            {
                clear();
                printGrid(height, width);
                wprintf(L"%sUnknown command\n", changeColours(4));
            }
           
            // wprintf(L"\n(%s)\n",buffer);
            memset(buffer, 0 , 100);
        }
        else if (keystroke == 'e') //Places an entry node
        {
            replaceGridChars(valx, valy, enterSymbol, height, width);
            startNodeX = valx;
            startNodeY = valy;
            clear();
            printGrid(height, width);
            gotoxy(x, y);
        }
        else if (keystroke == 'r')  //Places a return node
        {
            replaceGridChars(valx, valy, exitSymbol, height, width);
            exitNodeX = valx;
            exitNodeY = valy;
            clear();
            printGrid(height, width);
            gotoxy(x, y);
        }
        else if (keystroke == 'i')
        {
            char* readfile = "./examples/bigmaze.txt";
            freeGrid(height, width);
            height = countlines(readfile) - 1;
            width = countrows(readfile);
            makeGrid(height, width);
            importGrid(height, width, readfile);
            x = width - 2;
            y = height - 2;
            clear();
            printGrid(height, width);
            wprintf(L"%s File has been successfully imorted", changeColours(4));
            gotoxy(x,y);
        }


        
        else if (keystroke == 'q') //Quits the program
        {
             while(true)
            {
                clear();
                wprintf(L"%s", changeColours(8));
                wprintf(L"Are you sure you want to stop? ('y/n')");
                scanf("%c", &quit);
                if (quit == 'y' || quit == 'Y')
                {
                    system("clear");
                    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
                    system("wmctrl -F -r :ACTIVE: -b remove,fullscreen");//Gets rid of the fullscreen
                    system("wmctrl -r :ACTIVE: -b toggle,maximized_vert,maximized_horz");//Maxamise to make sure the pattern is kept
                    return 0;
                }
                else if (quit == 'n' || quit == 'N')
                {
                    clear();
                    printGrid(height, width);
                    break;
                }
                else
                {
                printf("\nThat isn't a valid input\n");
                }
            }
        }
    }
    freeGrid(height, width);
}


int main(int argc, char* argv[])    //Takes command line input
{
    int x = 10; //Sets default to 50 by 100
    int y = 10;

    

    if (argc == 2)  //If the user entered 1 argument
    {
        x = atoi(argv[1]);  //convert it to an integer
    }


    else if( argc == 3 ) {
        x = atoi(argv[1]);
        y = atoi(argv[2]);
    }
    else if( argc > 3 ) {   
        printf("Too many arguments supplied.\n");
        return -1;
    }

    if (x < 5 || y < 5) //Makes sure there values entered are higher than 5
    {
        printf("You need to put values higher than 5\n");
        return -1;
    }
    else if(x > 60 || y > 104)  //Stops you from enterring too high of a value
    {
        printf("The values you have enterred are too high\n");
        return -1;
    }
    system("wmctrl -F -r :ACTIVE: -b add,fullscreen");// Sets the terminal to fullscreen
    Play(x, y);
    return 0;
}
