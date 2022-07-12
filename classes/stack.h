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
    *top = stackSize - 1;   //If the stack is empty, set it to 1 - the stacksize, because the stack grows down
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
    if(*top == -1)//Stops user from popping from the stack if its empty
    {             //This should never happen, because we always double check if the stack is empty before popping from it
    printf("ERROR: The stack is empty. \n");
    }
    
    else{
    if((*top) == stackSize - 1){//If the element popped was the last in the stack
        (*top) = -1;            //Set top to -1 to show the stack is empty
    }
    else{
        (*top)++;               //Otherwise, increment top
    }
    }
}