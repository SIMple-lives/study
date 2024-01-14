#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

Node *initList()
{
    Node *S=(Node *)malloc(sizeof(Node));
    S->data=0;
    S->next=NULL;
    return S; 
}

bool isEmpty(Node * S)
{
    if(S->next==NULL || S->data==0)
    {
        return true;
    }
    return false;
}

int getTop(Node * S)
{
    if(isEmpty(S))
    {
        return -1;
    }
    else
    {
        return S->next->data;
    }
}

void push(Node * S,int data)
{
    Node *node =(Node *)malloc(sizeof(Node));
    node->data=data;
    node->next=S->next;
    S->next=node;
    S->data++;
}

int pop(Node *S)
{
    if(isEmpty(S))
    {
        return -1;
    }
    else
    {
        Node *node=S->next;
        int data=S->data;
        S->next=node->next;;
        free(node);
        S->data--;
        return data;
    }
}

void print(Node *S)
{
    Node *node=S->next;
    while(node)
    {
        printf("%d -> ",node->data);
        node=node->next;
    }
    printf("NULL\n");
}

int main()
{
    Node *L=initList();
    push(L,1);
    push(L,2);
    push(L,3);
    push(L,4);
    print(L);
    pop(L);
    pop(L);
    print(L);
    return 0;
}