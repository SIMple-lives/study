#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
}Node;

Node * initList()
{
    Node *L=(Node *)malloc(sizeof(Node));
    L->data=0;
    L->next=L;
    L->prev=L;
    return L;
}

void headInsert(Node *L,int data)
{
    Node *node=(Node *)malloc(sizeof(Node));
    node->data=data;
    if(L->data==0)
    {
        node->next=L->next;
        node->prev=L;
        L->next=node;
        L->prev=node;
    }
    else
    {
        node->next=L->next;
        node->prev=L;
        L->next->prev=node;
        L->next=node;
    }
    L->data++;
}

void tailInsert(Node *L,int data)
{
    Node *node=L;
    while(node->next!= L)
    {
        node=node->next;
    }
    Node *N=(Node *)malloc(sizeof(Node));
    N->data=data;
    N->prev=node;
    N->next=L;
    L->prev=node;
    node->next=N;
    L->data++;
}

bool delete(Node *L,int data)
{
    Node *node=L->next;
    while(node!=L)
    {
        if(node->data==data)
        {
            node->prev->next=node->next;
            node->next->prev=node->prev;
            free(node);
            node=NULL;
            L->data--;
            return true;
        }
        else
        {
            node=node->next;
        }
    }
    return false;
}

void print(Node *L)
{
    Node *node=L->next;
    while(node!=L)
    {
        printf("%d -> ",node->data);
        node=node->next;
    }
    printf("NULL\n");
}

int main()
{
    Node *L=initList();
    headInsert(L,1);
    headInsert(L,2);
    headInsert(L,3);
    headInsert(L,4);
    print(L);
    tailInsert(L,5);
    tailInsert(L,6);
    tailInsert(L,7);
    tailInsert(L,8);
    print(L);
    delete(L,2);
    delete(L,6);
    print(L);
    return 0;
}