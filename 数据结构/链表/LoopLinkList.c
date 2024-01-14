#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

Node * initList()
{
    Node *list=(Node *)malloc(sizeof(Node));
    list->data=0;
    list->next=list;//单循环链表，所以头结点会指向自己.
    return list;
}

void headInsert(Node *list,int data)
{
    Node * node=(Node *)malloc(sizeof(Node));
    node->data=data;
    node->next=list->next;
    list->next=node;
    list->data++;
}

void tailInsert(Node *list,int data)
{
    Node *node=(Node *)malloc(sizeof(Node));
    Node * N=list;
    node->data=data;
    node->next=list;
    while(N->next!=list)
    {
        N=N->next;
    }
    N->next=node;
    list->data++;
}

bool delete(Node *list,int data)
{
    Node *node=list->next;
    Node *pre=list;
    while(node!=list)
    {
        if(node->data==data)
        {
            pre->next=node->next;
            free(node);
            node=NULL;
            list->data--;
            return true;
        }
        pre=node;
        node=node->next;
    }
    return false;
}

void print(Node *list)
{
    Node *node=list->next;
    while(node!=list)
    {
        printf("%d ->",node->data);
        node =node->next;
    }
    printf("NUll\n");
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
    delete (L,4);
    print(L);
    return 0;
}