#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Grid.h"

static int area = 100;

struct element
{
    int data[2];
    struct element *next;
};
typedef struct element element;

struct queue
{
    int count;
    element *front;
    element *rear;
};
typedef struct queue queue;

void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

int isempty(queue *q)
{
    return (q->rear == NULL);
}

int enqueue(queue *q, int value1, int value2)
{
    if (q->count < area)
    {
        element *tmp;
        tmp = malloc(sizeof(element));
        tmp->data[0] = value1;
        tmp->data[1] = value2;
        tmp->next = NULL;
        if(!isempty(q))
        {
            q->rear->next = tmp;
            q->rear = tmp;
        }
        else
        {
            q->front = q->rear = tmp;
        }
        q->count++;
        return 0;
    }
    else
    {
        return 1;   //Something went wrong, the list is somehow full
    }
}

int* dequeue(queue *q)
{
    element *tmp;
    static int n[2];
    n[0] = q->front->data[0];
    n[1] = q->front->data[1];
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    return(n);
}

void display(element *head)
{
    if(head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d, %d\n", head -> data[0], head -> data[1]);
        display(head->next);
    }
}

void breadthFirstSearch(int height, int width, int startNodeX, int startNodeY, int counter, queue *q, bool visited[height][width], int parentNodes[height][width][2])
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
                    enqueue(q, x, y);
                    visited[i][j] = true;
                    ranArray[x][y].distance = counter;
                    parentNodes[i][j][0] = i;
                    parentNodes[i][j][1] = j;
                }
                x = i;
                y = j + 1;
                if (ranArray[x][y].visited == false)//right
                {
                    enqueue(q, x, y);
                    visited[i][j] = true;
                    ranArray[x][y].distance = counter;
                }
                x = i - 1;
                y = j;
                if (ranArray[x][y].visited == false)//Up
                {
                    enqueue(q, x, y);
                    visited[i][j] = true;
                    ranArray[x][y].distance = counter;
                }
                x = i + 1;
                y = j;
                if (ranArray[x][y].visited == false)//Down
                {
                    enqueue(q, x, y);
                    visited[i][j] = true;
                    ranArray[x][y].distance = counter;
                }
            }
        }
    }
}



int main()
{
    setlocale(LC_CTYPE, "");

    queue *q;
    q = malloc(sizeof(queue));
    initialize(q);

    int height = 10;
    int width = 10;
    int exitNodeX = 3;
    int exitNodeY = 3;
    int startNodeX = 5;
    int startNodeY = 5;
    bool visited[height][width];
    bool parentNodes[height][width][2];

    int counter = 1;

    makeGrid(height, width);
    replaceGridChars(startNodeX, startNodeY, enterSymbol, height, width);
    replaceGridChars(exitNodeX, exitNodeY, exitSymbol, height, width);
    ranArray[startNodeX][startNodeY].distance = 0;
    printGrid(height, width);

    while((
            (ranArray[1][1].visited == false) && 
            (ranArray[height - 2][width - 2].visited == false) && 
            (ranArray[1][width - 2].visited == false) && 
            (ranArray[height - 2][1].visited == false)) 
            || ranArray[exitNodeX][exitNodeY].visited == false)
        {
            breadthFirstSearch(height, width, startNodeX, startNodeY, counter, q);
            counter ++;
        }
    
    return 0;
}
