#include "Grid.h"
#include <sys/time.h>
#include <sys/ioctl.h>

//TODO
//Add other maze generation algorithms
//Add other pathfinding algorithms
//Find a better way of counting lines in a file
//Check to see if imported files are suitable
//Add a watermark or something

//Impliment bfs
//Impliment dfs

static struct Node **ranArray;  //https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/amp/ --Makes an array of nodes
int screen_height, screen_width;

int Play(int height, int width)
{
    bool help = true;   //Used for the help comand
    bool loop = true;   //Used to keep looping through the code
    char quit;          //Used for the quit command
    int x = 4;
    int y = 4;
    height += 2;    //takes into account, the top, bottom, left & right walls
    width += 2;
    srand(time(NULL));

    int colour = 8;             //Sets the default colour to white
    setlocale(LC_CTYPE, "");    //Allows you to enter unicode charecters

    int keystroke;
    static struct termios oldt, newt;   // Initialises old and new terminal settings
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
    bool visual = true;

    while (loop)
    {
        valx = y - 1; //Dont question it
        valy = x / 2;
        keystroke = getchar();
        if (keystroke == 'w' || keystroke == 'W')//Move up
        {
            if (y == 2)
            {
                y ++;
                gotoxy(x,y);
            }
            y --;
            gotoxy(x,y);
        }
        else if (keystroke == 'a' || keystroke == 'A')//Move left
        {
            if (x == 2)
            {
                x +=2;
                gotoxy(x,y);
            }
            x -= 2;
            gotoxy(x,y);
        }
        else if (keystroke == 's' || keystroke == 'S')//Move Down
        {
            if (y == height - 1)
            {
                y --;
                gotoxy(x,y);
            }
           
            y ++;
            gotoxy(x,y);
        }
        else if (keystroke == 'd' || keystroke == 'D')//Move Right
        {
            if (x >= (width * 2) - 4)
            {
                x -=2;
                gotoxy(x,y);

            }
            x += 2;
            gotoxy(x,y);
        }
        else if (keystroke == 'g' || keystroke == 'G')  //Troubleshooting key
        {
            continue;
            clear();
            printGrid(height, width);
            wprintf(L"(%i,%i) -> (%i,%i) - %i", valx, valy ,ranArray[valx][valy].parentNode[0], ranArray[valx][valy].parentNode[1], ranArray[valx][valy].distance);
            wprintf(L"X:%i Y:%i\n", x, y);
            gotoxy(x, y);
        }    
        else if (keystroke == ' ')//Places Block
        {
            if (ranArray[valx][valy].type == underscore)
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
                ranArray[valx][valy].type = underscore;
                ranArray[valx][valy].visited = false;
                ranArray[valx][valy].distance = -1;
                clear();
            }
            printGrid(height, width);
            gotoxy(x, y);
        }    
        else if (keystroke == 'h' || keystroke == 'H')//Shows help menu
        {
            if(help)
            {
                clear();
                wprintf(L"Type space to enter/remove a block\n");
                wprintf(L"Type / to enter your command prompt, simply enter backspace to exit\n");
                wprintf(L"Type q to quit the program\n");
                wprintf(L"Use WASD to move\n\n");
                
                wprintf(L"The following commands can be accessed using the '/' command\n");
                wprintf(L"➢ use --This takes the argument of the algorithm you want to run\n");
                wprintf(L"      -bruteforce --This runs the bruteforce method\n");
                wprintf(L"➢ clear --This clears the screen\n");
                wprintf(L"➢ resize --This can take 2 arguments, height and width in order to resize the grid\n");
                wprintf(L"➢ export --This takes one filename as an argument, don't enter a file extension");
                wprintf(L"➢ random -- This can take one argument, a value between 1,99 which is used as a percentage for the grid\n");
                wprintf(L"➢ import -- This can take one argument, a file name to import, to list files, just don't type a file name\n");
                wprintf(L"➢ visual -- This toggles between speed and visual\n");
                wprintf(L"➢ Generate -- This allows you to generate a map\n");
                wprintf(L"      -bfs --Use Breath First Search in order to make a map\n");

                wprintf(L"\n\n Click h to exit this menu");
                help = false;
            }
            else
            {
                help = true;
                clear();
                printGrid(height, width);
            }
        }        
        else if (keystroke == '/')  
        {
            char buffer[120];
            memset(buffer, '\x00', 100);    //Fills the buffer with NULL charecters
            char* word;                     // This would be each individual word
            int counter = 0;                //This is the amount of words enterred by the suer
            char* command[20];              //This is the array of words splited by spaces
            clear();
            printGrid(height, width);
            wprintf(L"\n\n/");
            char c;                         //Charecters enterred by the user

            while ((c = getchar()) != '\n' && c != EOF && strlen(buffer) != 100)
                {
                    if (c == 127)
                    {
                        buffer[strlen(buffer) - 1] = '\0';
                        clear();
                        printGrid(height, width);
                        wprintf(L"\n\n/%s", buffer);
                    }
                    else if(c == 27)
                    {
                        clear();
                        printGrid(height, width);
                        break;
                    }
                    else
                    {
                        wprintf(L"%c", c);
                        strncat(buffer, &c, 1);
                    }
                }      
            clear();
            printGrid(height, width);
            if(strlen(buffer) == 0 || c == 27)
            {
                gotoxy(x,y);
                continue;
            }

            if(strlen(buffer) == 100)
            {
                wprintf(L"Stop trying to break the program >:( \n");
                memset(buffer, 0 , 100);
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

            
            
            if (!strcmp(command[0], "use"))
            {
                if(counter > 2)
                {
                    wprintf(L"This command only takes 1 argument 'bruteforce {algorithm}'\n");
                    continue;
                }
                if (!strcmp(command[1], "bruteforce"))
                {
                    if(checkCondition(height, width, enterSymbol, exitSymbol))
                        {
                            struct timeval start, stop;
                            double time_taken = 0;
                            gettimeofday(&start, NULL);
                            if(mapAdjacent(height, width, startNodeX, startNodeY, exitNodeX, exitNodeY, visual))
                            {
                                traceBack(height, width, exitNodeX, exitNodeY, startNodeX, startNodeY, visual);
                                clear();
                                printGrid(height, width);
                                gettimeofday(&stop, NULL);
                                time_taken = (double) (stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
                                wprintf(L"%s Optimal Path Found!!!\n", changeColours(3));
                                printTime(time_taken);
                            }
                            else
                            {
                                clear();
                                printGrid(height, width);
                                wprintf(L"%s PATH NOT FOUND", changeColours(2));
                            }
                                // freeGrid(height, width);
                                // makeGrid(height, width);
                                getchar();
                                resetGrid(height, width);
                        }
                    else
                    {
                        clear();
                        printGrid(height, width);
                        wprintf(L"%s Enter an exit & entry node\n", changeColours(4));
                    }
                    gotoxy(x, y);
                    }
                
                else if(!strcmp(command[1], "astar"))
                {
                    struct timeval start, stop;
                    double time_taken = 0;
                    gettimeofday(&start, NULL);
                    if(Astar(startNodeX, startNodeY, exitNodeX, exitNodeY, height, width, visual))
                    {
                        clear();
                        printGrid(height, width);
                        wprintf(L"Path Not found\n");
                        
                    }
                    else
                    {
                        traceBack(height, width, exitNodeX, exitNodeY, startNodeX, startNodeY, visual);
                        gettimeofday(&stop, NULL);
                        time_taken = (double) (stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
                        clear();
                        printGrid(height, width);
                        wprintf(L"%s Optimal Path Found!!!\n", changeColours(3));
                        printTime(time_taken);
                    }
                    getchar();
                    resetGrid(height, width);
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
                if(counter > 1)
                {
                    wprintf(L"This command takes no arguments\n");
                    sleep(1);
                }
                makeGrid(height, width);
                clear();
                printGrid(height, width);
                wprintf(L"%s Grid Cleared", changeColours(5));
            }
            
            else if (!strcmp(command[0], "resize"))
            {
                if(counter > 3)
                {
                    wprintf(L"This command only takes 2 arguments 'resize {height} {width}'");
                    continue;
                }
                int resizeValueX, resizeValueY;
                resizeValueX = atoi(command[1]);
                if (counter > 1 && resizeValueX < screen_height && resizeValueX > 9)
                {
                    freeGrid(height, width);
                    resizeValueY = atoi(command[2]);
                    height = resizeValueX + 2;
                    if(counter > 2 && resizeValueY < screen_width && resizeValueY > 9)
                    {
                        width = resizeValueY + 2;
                    }
                    makeGrid(height, width);
                    clear();
                    printGrid(height, width);
                    
                }
                else
                {
                    wprintf(L"%sInvalid input\nYou're display will allow a max height of %i and max width of %i\nMinimum input is 10 * 10", changeColours(4), screen_height - 1, screen_width - 1);
                }
                x = 4;
                y = 4;
                gotoxy(x,y);
            }
            
            else if (!strcmp(command[0], "export"))
            {
                if(counter != 2)
                {
                    wprintf(L"This command takes a filename as a singular argument");
                    continue;
                }
                clear();
                printGrid(height, width);
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
            
            else if (!strcmp(command[0], "random"))
            {
                if (counter > 2)
                {
                    wprintf(L"This command only takes 1 argument\n");
                    continue;
                }
                
                freeGrid(height, width);
                makeGrid(height, width);
                int ranValue = 50;
                int digit;
                if(counter > 1)
                {
                    digit = atoi(command[1]);
                    if (digit < 1 || digit > 99)
                    {
                        wprintf(L"Please enter a percentage between 1 & 99");
                        continue;
                    }
                    else
                    {
                        ranValue = digit;
                    }
                }
                for (int i = 1; i < height - 1; i++)
                {
                    for (int j = 1; j < width - 1; j++)
                    {
                        if ((rand() % 100) < ranValue)
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
                int fileHeight, fileWidth;
                if (counter > 2)
                {
                    wprintf(L"This command only takes 1 argument");
                }
                
                DIR *d = opendir("./examples");
                struct dirent *dir;
                
                if(counter == 1)
                {
                    clear();
                    if (d)
                    {
                        wprintf(L"Type '/import', followed by one of the following file names\n");
                        wprintf(L"*-----------------------------------------------------------------*\n");
                        while((dir = readdir(d)) != NULL)
                        {
                            if(strstr(dir->d_name, ".txt"))
                            {
                                wprintf(L"◉ %s\n", dir->d_name);
                            }
                        }
                         wprintf(L"*-----------------------------------------------------------------*\n");
                    }
                    else
                    {
                            wprintf(L"File not found\n");
                    }
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
                                char readfile[120] = "./examples/";
                                strcat(readfile, command[1]);
                                fileHeight = countlines(readfile) - 1;
                                fileWidth = countColumns(readfile);
                                if(fileHeight < screen_height || fileWidth < screen_width)
                                {
                                    wprintf(L"You're screen isn't big enough for this file\n");
                                    wprintf(L"%i,%i\n", fileHeight, fileWidth);
                                    found = true;
                                    break;
                                }
                                else
                                {
                                    height = fileHeight;
                                    width = fileWidth;
                                    freeGrid(height, width);
                                    makeGrid(height, width);
                                    importGrid(height, width, readfile);
                                    wprintf(L"%s\n", readfile);
                                    x = width - 2;
                                    y = height - 2;
                                    clear();
                                    printGrid(height, width);
                                    wprintf(L"%s File has been successfully imported", changeColours(4));
                                    gotoxy(x,y);
                                    found = true;
                                }
                            }
                        }
                    }
                    else
                    {
                            wprintf(L"File not found\n");
                    }
                    if (found == false)
                    {
                        wprintf(L"Invalid file name\n");
                    }
                    
                }
                
            }

            else if (!strcmp(command[0], "visual"))
            {
                if (counter > 1)
                {
                    wprintf(L"This command takes no arguments\n");
                    continue;
                }
                visual = !visual;
                if (visual)
                {
                    wprintf(L"%sOptamised for Appearence", changeColours(5));
                }
                else
                {
                    wprintf(L"%sOptamised for speed", changeColours(5));
                }
            }
            
            else if (!strcmp(command[0], "generate"))
            {
                if (!strcmp(command[1], "bfs"))
                {
                    clear();
                    bfsFunc(height, width, visual);
                }
                else
                {
                    wprintf(L"That Algorithm isn't found, try typing bfs\n");
                }
            }
            
            else
            {
                clear();
                printGrid(height, width);
                wprintf(L"%sUnknown command\n", changeColours(4));
            }
           
            // wprintf(L"\n(%s)\n",buffer);
            gotoxy(x,y);
            memset(buffer, 0 , 100);
        }
        
        else if (keystroke == 'm')
        {
            continue;
            // queue *q;
            // q = malloc(sizeof(queue));
            // initialize(q);
            // breadthFirstSearch(height, width, startNodeX, startNodeY, 1);
        }
        else if (keystroke == 'e' || keystroke == 'E') //Places an entry node
        {
            replaceGridChars(valx, valy, enterSymbol, height, width);
            startNodeX = valx;
            startNodeY = valy;
            clear();
            printGrid(height, width);
            gotoxy(x, y);
        }
        else if (keystroke == 'r' || keystroke == 'R')  //Places a return node
        {
            replaceGridChars(valx, valy, exitSymbol, height, width);
            exitNodeX = valx;
            exitNodeY = valy;
            clear();
            printGrid(height, width);
            gotoxy(x, y);
        }        
        else if (keystroke == 'q' || keystroke == 'Q' ) //Quits the program
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
                    freeGrid(height, width);
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
    return 0;
}

int main(int argc, char* argv[])    //Takes command line input
{
    int x = 10; //Sets default values
    int y = 10;
    system("wmctrl -F -r :ACTIVE: -b add,fullscreen");// Sets the terminal to fullscreen
    usleep(50000);
    struct winsize window;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
    screen_height = window.ws_row - 10;
    screen_width = (window.ws_col / 2) - 3;


    if (argc == 2)  //If the user entered 1 argument
    {
        if(!strcmp(argv[1], "MAX_HEIGHT"))
        {
            x = screen_height;
        }
        else
        {
            x = atoi(argv[1]);  //convert it to an integer
        }
    }


    else if( argc == 3 ) 
    {
        if(!strcmp(argv[1], "MAX_HEIGHT"))
        {
            x = screen_height;
        }
        else
        {
            x = atoi(argv[1]);  //convert it to an integer
        }

        if(!strcmp(argv[2], "MAX_WIDTH"))
        {
            y = screen_width;
        }
        else
        {
            y = atoi(argv[2]);  //convert it to an integer
        }
    }
    else if( argc > 3 ) {   
        printf("Too many arguments supplied.\n");
        system("wmctrl -F -r :ACTIVE: -b remove,fullscreen");//Gets rid of the fullscreen
        return -1;
    }

    if (x < 5 || y < 5) //Makes sure there values entered are higher than 5
    {                   //This should also capture other invalid inputs
        printf("You need to put values higher than 5\n");
        system("wmctrl -F -r :ACTIVE: -b remove,fullscreen");//Gets rid of the fullscreen
        return -1;
    }
    else if(x > screen_height || y > screen_width)  //Stops you from enterring too high of a value
    {
        printf("The values you have enterred are too high, %i, %i\n", screen_height, screen_width);
        system("wmctrl -F -r :ACTIVE: -b remove,fullscreen");//Gets rid of the fullscreen        
        return -1;
    }
    // system("wmctrl -F -r :ACTIVE: -b add,fullscreen");// Sets the terminal to fullscreen
    Play(x, y);
    return 0;
}
