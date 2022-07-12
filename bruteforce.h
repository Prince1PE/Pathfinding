#include "class.h"

void setNode(int counter, int x, int y, int i, int j) //Changes the values of the node respectfully
    {
        ranArray[x][y].dirty = true;        //Used for refresh
        ranArray[x][y].distance = counter;
        ranArray[x][y].parentNode[0] = i;
        ranArray[x][y].parentNode[1] = j;
        ranArray[x][y].visited = true;
        ranArray[x][y].colour = 2;
    }

int bruteForce(int height, int width,int startNodeX, int startNodeY, int counter, int checkCount)  
{
    int x, y, valx, valy;
    
    for (int i = 1; i < height - 1; i++)
    {
        ranArray[startNodeX][startNodeY].colour = 8;//If places outside loop, there is a glitch that turns the entry node red for a second
        for (int j = 1; j < width - 1; j++)
        {
            if (ranArray[i][j].distance == counter - 1)
            {
                x = i;
                y = j - 1;
                if (ranArray[x][y].visited == false)//left
                {
                    setNode(counter, x, y, i, j);
                    checkCount++;
                }
                x = i;
                y = j + 1;
                if (ranArray[x][y].visited == false)//right
                {
                    setNode(counter, x, y, i, j);
                    checkCount++;
                }
                x = i - 1;
                y = j;
                if (ranArray[x][y].visited == false)//Up
                {
                    setNode(counter, x, y, i, j);
                    checkCount++;
                }
                x = i + 1;
                y = j;
                if (ranArray[x][y].visited == false)//Down
                {
                    setNode(counter, x, y, i, j);
                    checkCount++;
                }
                // x = i - 1;
                // y = j + 1;
                // if (ranArray[x][y].visited == false)//Up/Right
                // {
                //     setNode(counter, x, y, i, j);
                //     checkCount++;
                // }
                // x = i - 1;
                // y = j + 1;
                // if (ranArray[x][y].visited == false)//Up/Left
                // {
                //     setNode(counter, x, y, i, j);
                //     checkCount++;
                // }
                // x = i + 1;
                // y = j + 1;
                // if (ranArray[x][y].visited == false)//Down/Right
                // {
                //     setNode(counter, x, y, i, j);
                //     checkCount++;
                // }
                // x = i + 1;
                // y = j - 1;
                // if (ranArray[x][y].visited == false)//Down/Left
                // {
                //     setNode(counter, x, y, i, j);
                //     checkCount++;
                // }
            }
        }
    }
    return checkCount;  //Used to see whether or not there is a possible path
}