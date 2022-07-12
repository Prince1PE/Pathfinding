#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../Grid.h"
#include "../classes/node.h"
#include "../classes/SortedLinkedList.h"

#define clear() wprintf(L"\e[1;1H\e[2J")

void printGrid(int height, int width);
void refresh(int height, int width);

wchar_t whiteBlock;


int nodeCost(int ValX, int ValY, int DestX, int DestY, int SourceX, int SourceY)
{
    
    int H = sqrt(pow(ValX - DestX, 2));
    int G = pow(ValY - DestY, 2);
    return G + H;
}

int Astar(int EntryNodeX, int EntryNodeY, int ExitNodeX, int ExitNodeY, int height, int width, int visual)
{
    int currentX, currentY, valX, valY;
    insert_sll(p2r, nodeCost(EntryNodeX, EntryNodeY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), EntryNodeX, EntryNodeY);
    

    while(!isEmpty_sll(p2r) && ranArray[ExitNodeX][ExitNodeY].visited == false)
    {        
        ranArray[EntryNodeX][EntryNodeY].colour = 8;
        OrderedList *current = *p2r;
        currentX = current->x;
        currentY = current->y;
        ranArray[currentX][currentY].colour = 3;    //This would be nodes that have been fully explored
        pop_sll(p2r);
        valX = currentX - 1;
        valY = currentY;        
        if (ranArray[valX][valY].visited == false && ranArray[valX][valY].type != whiteBlock)
        {
            setNode(nodeCost(valX, valY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), valX, valY, currentX, currentY);
            insert_sll(p2r, nodeCost(valX, valY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), valX, valY);
            
        }
        valX = currentX;
        valY = currentY + 1;
        if (ranArray[valX][valY].visited == false && ranArray[valX][valY].type != whiteBlock)
        {
            setNode(nodeCost(valX, valY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), valX, valY, currentX, currentY);
            insert_sll(p2r, nodeCost(valX, valY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), valX, valY);
            
        }
        valX = currentX + 1;
        valY = currentY;
        if (ranArray[valX][valY].visited == false && ranArray[valX][valY].type != whiteBlock)
        {
            setNode(nodeCost(valX, valY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), valX, valY, currentX, currentY);
            insert_sll(p2r, nodeCost(valX, valY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), valX, valY);
            
        }
        valX = currentX;
        valY = currentY - 1;
        if (ranArray[valX][valY].visited == false && ranArray[valX][valY].type != whiteBlock)
        {
            setNode(nodeCost(valX, valY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), valX, valY, currentX, currentY);
            insert_sll(p2r, nodeCost(valX, valY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), valX, valY);
        }

        if(visual)
        {
            clear();
            usleep(100000);
            printGrid(height, width);
        }
        
        
    }

    if(isEmpty_sll(p2r))
    {
        return 1;
    }
    else
    {
        while(!isEmpty_sll(p2r))
        {
            pop_sll(p2r);
        }
        return 0;
    }
}

