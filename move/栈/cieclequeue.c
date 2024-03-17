#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

typedef struct Queue
{
    int front;
    int rear;
    int data[MAXSIZE];
}Queue;

Queue *  initQueue()
{
    Queue * Q=(Queue *)malloc(sizeof(Queue));
    Q->front=Q->rear=0;
    return Q;
}

int getlen(Queue *Q)
{
    return (Q->rear-Q->front+MAXSIZE)%MAXSIZE;
}

void printQueue(Queue *Q)//要知道队列当前的长度.
{
    int length=getlen(Q);
    int index=Q->front;
    for(int i=0;i<length;i++)
    {
        printf("%d ->",Q->data[index]);
        index=(index+1)%MAXSIZE;
    }
    printf("NULL\n");
} 

int isFull(Queue *Q)//判断是否队满
{
    if((Q->rear+1)%MAXSIZE==Q->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty(Queue *Q)
{
    if(Q->front==Q->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int enqueue(Queue *Q,int data)
{
    if(isFull(Q))
    {
        return 0;
    }
    else
    {
        Q->data[Q->rear]=data;
        Q->rear=(Q->rear+1)%MAXSIZE;
        return 1;
    }
}

int dequeue(Queue*Q)
{
    if(isEmpty(Q))
    {
        return 0;
    }
    else
    {
        int data=Q->data[Q->rear];
        Q->front=(Q->front+1)%MAXSIZE;
        return data;
    }
}

int main()
{
    Queue* Q=initQueue();
    enqueue(Q,1);
    enqueue(Q,2);
    enqueue(Q,3);
    enqueue(Q,4);
    enqueue(Q,5);
    printQueue(Q);
    dequeue(Q);
    dequeue(Q);
    printQueue(Q);
    enqueue(Q,6);
    printQueue(Q);
    enqueue(Q,7);
    printQueue(Q);
    return 0;
}