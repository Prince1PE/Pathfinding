#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <stdlib.h>

struct queuedElement
{
    int data[2];
    struct queuedElement *next;
};
typedef struct queuedElement queuedElement;

struct queue
{
    int count;
    queuedElement *front;
    queuedElement *rear;
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

void enqueue(queue *q, int valueX, int valueY)
{
    queuedElement *tmp;
    tmp = malloc(sizeof(queuedElement));
    tmp->data[0] = valueX;
    tmp->data[1] = valueY;
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
}

void dequeue(queue *q)
{
    queuedElement *tmp;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
}

void display(queuedElement *head)
{
    if(head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d, %d\n", head -> data[0], head ->data[1]);
        display(head->next);
    }
}
#endif