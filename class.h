#ifndef CLASSES
#define CLASSES
#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>

int stackEmpty(int stackSize, int stack[stackSize][2], int *top)
{
    if(*top == - 1){return 1;}
    else {return 0;}
}

void push(int elementX, int elementY, int stackSize ,int stack[stackSize][2], int *top)
{
    if(*top == -1)
    {
    stack[stackSize - 1][0] = elementX;
    stack[stackSize - 1][1] = elementY;
    *top = stackSize - 1;
    }
    else if(*top == 0)//Stack is full
    {
    printf("ERROR: The stack is already full. \n");
    }
    else
    {
    stack[(*top) - 1][0] = elementX;
    stack[(*top) - 1][1] = elementY;
    (*top)--;
    }
}

void pop(int stackSize,int stack[stackSize][2], int *top)
{
    if(*top == -1)
    {
    printf("ERROR: The stack is empty. \n");
    }
    else{
    // printf("Element popped: %i, %i \n", stack[(*top)][0], stack[(*top)][1]);
    // If the element popped was the last element in the stack
    // then set top to -1 to show that the stack is empty
    if((*top) == stackSize - 1){
        (*top) = -1;
    }
    else{
        (*top)++;
    }
    }
}

//Create the Node class
struct Node
{
    wchar_t type;
    int colour;
    int distance;
    bool visited;
    int parentNode[2];
    bool dirty;
};

static struct Node** ranArray;


#endif
