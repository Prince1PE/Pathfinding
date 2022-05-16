//Create the Node class
struct Node
{
    wchar_t type;
    int colour;
    int distance;
    bool visited;
    int parentNode[2];
};

void mapSurrounding(int height, int width, struct Node ranArray[height][width],int counter, int x, int y, int i, int j)
    {
        ranArray[x][y].visited = true;
        ranArray[x][y].distance = counter;
        ranArray[x][y].parentNode[0] = i;
        ranArray[x][y].parentNode[1] = j;
    }

void bruteForce(int height, int width, struct Node ranArray[height][width],int startNodeX, int startNodeY, int counter)  
{
    int x, y, valx, valy;
  for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            ranArray[startNodeX][startNodeY].colour = 8;
            if (ranArray[i][j].distance == counter - 1)
            {
                ranArray[i][j].colour = 2;
                x = i;
                y = j - 1;
                if (ranArray[x][y].visited == false)//left
                {
                    mapSurrounding(height, width, ranArray, counter, x, y, i, j);
                }
                x = i;
                y = j + 1;
                if (ranArray[x][y].visited == false)//right
                {
                    mapSurrounding(height, width, ranArray, counter, x, y, i, j);
                }
                x = i - 1;
                y = j;
                if (ranArray[x][y].visited == false)//Up
                {
                    mapSurrounding(height, width, ranArray, counter, x, y, i, j);
                }
                x = i + 1;
                y = j;
                if (ranArray[x][y].visited == false)//Down
                {
                    mapSurrounding(height, width, ranArray, counter, x, y, i, j);
                }
            }
        }
    }
}