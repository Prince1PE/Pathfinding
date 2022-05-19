#include "Grid.h"

//TODO
//Allow program to be run via commands
//Add in something more complicated
//Add a timer  
//Export Map

int Play(int height, int width)
{
    bool help = true;   //Used for the help comand
    bool loop = true;   //Used to keep looping through the code
    char quit;          //Used for the quit command
    int x = width;
    int y = height;
    height += 2;    //takes into account, the top, bottom, left & right walls
    width += 2;
    struct Node ranArray[height][width];    //Makes an array of nodes
    node.type = upperHalfBlock; //Sets the default node charecter
    int colour = 8;             //Sets the default colour to white
    setlocale(LC_CTYPE, "");    //Allows you to enter unicode charecters

    int keystroke;
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt); //storing terminal settings in oldt
    newt = oldt; //copying oldt to newt
    newt.c_lflag &= ~(ICANON | ECHO); //Turning off canoninal input bit and echo bit
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    makeGrid(height, width, ranArray);
    
    system("clear");
    printGrid(height, width, ranArray);
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
            printGrid(height, width, ranArray);
            printf("(%i,%i) -> (%i,%i) - %i", valx, valy ,ranArray[valx][valy].parentNode[0], ranArray[valx][valy].parentNode[1], ranArray[valx][valy].distance);
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
            printGrid(height, width, ranArray);
            gotoxy(x, y);
        }    
        else if (keystroke == 'h')//Shows help menu
        {
            if(help)
            {
                clear();
                printf("Type space to enter/remove a block\n");
                printf("Type / to enter your command prompt, simply enter backspace to exit\n");
                printf("Type q to quit the program\n");
                printf("Use WASD to move\n\n");
                printf("\n\n Click h to exit");
                help = false;
            }
            else
            {
                help = true;
                clear();
                printGrid(height, width, ranArray);
            }
        }        
        else if (keystroke == '/')  //Ignore this, im going to truy and make this work later
        {
            char *buffer = (char *)malloc(100);
            char* words;
            clear();
            printGrid(height, width, ranArray);
            printf("\n\n/");
            char command[100];
            char c;
        while ((c = getchar()) != '\n' && c != EOF && c != 127)
            {
                printf("%c", c);
                strncat(command, &c, 1);
            }      
            clear();
            printGrid(height, width, ranArray);
            printf("(%s)", command);
            if(c == 127)
            {
                continue;
            }

            else if (strstr(buffer, "use"))
            {
                char* words;
                words = strtok(buffer, " ");
                if (strcmp(words, "use"))
                {
                    printf("Invalid Input1\n");
                }
                words = strtok(NULL, " ");
                if (words == NULL)
                {
                    printf("Invalid Input2\n");
                }
                else if (strlen(words) > 1)
                {
                    printf("Invalid input3\n");
                }
                else if (strcmp(words, "bruteforce") == 0)
                {
                    mapAdjacent(height, width, ranArray, startNodeX, startNodeY, exitNodeX, exitNodeY);
                    traceBack(height, width, ranArray, exitNodeX, exitNodeY, startNodeX, startNodeY);
                    clear();
                    printGrid(height, width, ranArray);
                    makeGrid(height, width, ranArray);
                    gotoxy(x, y);
                }
                else{
                    printf("Invalid Input4\n");
                }
            
            }

            else
            {
                printf("That command doesn't exist");
            }
            free(buffer);
        }
        else if (keystroke == 'e') //Places an entry node
        {
            replaceGridChars(valx, valy, enterSymbol, height, width, ranArray);
            startNodeX = valx;
            startNodeY = valy;
            clear();
            printGrid(height, width, ranArray);
            gotoxy(x, y);
        }
        else if (keystroke == 'r')  //Places a return node
        {
            replaceGridChars(valx, valy, exitSymbol, height, width, ranArray);
            exitNodeX = valx;
            exitNodeY = valy;
            clear();
            printGrid(height, width, ranArray);
            gotoxy(x, y);
        }
        else if (keystroke == 'm')//Runs bruteforce method
        {   //This should be ran using the command line
            if(checkCondition(height, width, ranArray, enterSymbol, exitSymbol))
            {
                double timeTaken = mapAdjacent(height, width, ranArray, startNodeX, startNodeY, exitNodeX, exitNodeY);
                if(timeTaken)
                {
                    traceBack(height, width, ranArray, exitNodeX, exitNodeY, startNodeX, startNodeY);
                    clear();
                    printGrid(height, width, ranArray);
                    wprintf(L"%s Optimal Path Found!!!\n", changeColours(3));
                    wprintf(L"This took %f seconds\n", timeTaken);
                }
                else
                {
                    clear();
                    printGrid(height, width, ranArray);
                    wprintf(L"%s PATH NOT FOUND", changeColours(2));
                }
                makeGrid(height, width, ranArray);
            }
            else
            {
                clear();
                printGrid(height, width, ranArray);
                wprintf(L"%s Enter an exit & entry node\n", changeColours(4));
            }
            gotoxy(x, y);
        }
        else if (keystroke == 'i')  //HERE IS THE PROBLEM
        {
            char* readfile = "./examples/maze2.txt";
            height = countlines(readfile);
            width = countrows(readfile);
            x = width - 2;
            y = height - 2;
            // struct Node ranArray[height][width];
            // makeGrid(height, width, ranArray);
            importGrid(height, width, ranArray, readfile);
            clear();
            printGrid(height, width, ranArray);
            gotoxy(x,y);
        }
        else if(keystroke == 'o') //Output file
        {
            char* writefile = "./examples/maze2.txt";
            writeGrid(height, width, ranArray, writefile);
            clear();
            printGrid(height, width, ranArray);
            wprintf(L"%s File has been saved to: %s\n", changeColours(4), writefile);
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
                    printGrid(height, width, ranArray);
                    break;
                }
                else
                {
                printf("\nThat isn't a valid input\n");
                }
            }
        }
    }
   
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
