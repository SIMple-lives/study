#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

Node * initList()
{
    Node *L=(Node *)malloc(sizeof(Node));
    L->data=0;
    L->next=NULL;
    return L;
}

void enqueue(Node *Q,int data)
{
    Node *node=(Node *)malloc(sizeof(Node));
    node->data=data;
    Node *q=Q;
    for(int i=0;i<Q->data;i++)
    {
        q=q->next;
    }
    node->next=q->next;
    q->next=node;
    Q->data++;
}

int dequeue(Node *Q)
{
    if(isEmpty(Q))
    {
        return -1;
    }
    Node *node=Q->next;
    int data=node->data;
    Q->next=node->next;
    free(node);
    Q->data--;
    return data;
}

void print(Node *Q)
{
    Node *node=Q->next;
    while(node)
    {
        printf("%d -> ",node->data);
        node =node->next;
    }
    printf("NULL\n");
}

int isEmpty(Node *L)
{
    if(L->data==0 || L->next==NULL)
    {
        return 1;
    }
    return 0;
}

int main()
{
    Node *Q=initList();
    enqueue(Q,1);
    enqueue(Q,2);
    enqueue(Q,3);
    enqueue(Q,4);
    enqueue(Q,5);
    print(Q);
    dequeue(Q);
    dequeue(Q);
    dequeue(Q);
    dequeue(Q);
    dequeue(Q);
    dequeue(Q);
    print(Q);
    return 0;
}
