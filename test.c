#include "Grid.h"

int S = 1;
int E = 2;
int HORIZONTAL = 1;
int VERTICAL = 2;

int choose_orientation(int height, int width)
{
    if(height > width){return VERTICAL;}
    else if(width > height){return HORIZONTAL;}
    else 
    {
        return rand() % 2 == 0 ? HORIZONTAL : VERTICAL;
    }
}

int divide(int x, int y, int height, int width, int orientation)
{
    if(width < 2 || height < 2)
    {
        return 1;
    }
    bool horizontal = orientation == HORIZONTAL;
    int wx = x + (horizontal ? 0 : rand() % (width - 2));
    int wy = y + (horizontal ? rand() % (height - 2): 0);

    int px = wx + (horizontal ? (rand() % width - 1) + 1: 0);
    int py = wy + (horizontal ? 0 : (rand() % height - 1) + 1);

    int dx = horizontal ? 1 : 0;
    int dy = horizontal ? 0 : 1;

    int length = horizontal ? width : height;

    int dir = horizontal ? S : E;
    for (int i = 0; i < length ; i++)
    {      
        if((wx != px || wy != py) 
        && ranArray[wy][wx].type == '_'
        && (    
                wx > 0 && wx < width - 1 && 
                wy > 0 && wy < height - 1)
        )
        {ranArray[wy][wx].type = whiteBlock;}
        wx += dx;
        wy += dy;
    }

    // int nx, ny, w, h;

    // nx = x;
    // ny = y;
    // horizontal ? (w = wy - y + 1) : (h = wx - x + 1);
    // divide(nx, ny, h, w, choose_orientation(h, w));
    return 0;
}

void divide2(int height, int width)
 
int main()
{
    int height, width;
    srand(time(NULL));
    setlocale(LC_CTYPE, "");    //Allows you to enter unicode charecters
    height = 10;
    width = 10;
    makeGrid(height, width);
    divide(0, 0, height, width, choose_orientation(height, width));
    printGrid(height, width);
    
    freeGrid(height, width);
    return 0;
}