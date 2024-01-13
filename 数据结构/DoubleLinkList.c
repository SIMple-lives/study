#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;  //指向前
    struct Node *prev;  //指向后
}Node;

Node *initList()
{
    Node *L=(Node *)malloc(sizeof(Node));
    L->data = 0;
    L->next = NULL;
    L->prev = NULL;
    return L;
}

void headinsert(Node *L,int data)
{
    Node *node=(Node *)malloc(sizeof(Node));
    node->data = data;
    if(L->data==0)//链表为空
    {
        node->next=L->next;
        node->prev=L;
        L->next=node;
    }
    else
    {
        node->next = L->next;
        node->prev= L;
        L->next->prev=node;//跟新插入后元素的向前指的指针
        L->next=node;//跟新头结点向后指的指针
    }
    L->data++;
}

void tailinsert(Node *L,int data)
{
    Node *node=(Node *)malloc(sizeof(Node));
    node->data=data;
    Node *N=L;
    while(N->next)
    {
        N=N->next;
    }
    node->next=N->next;//以后插入的时候最好不要直接进行赋值,例如node->next=NULL;尽量使用代码部分的方法。
    N->next=node;
    node->prev=N; 
    L->data++;
}

bool delete(Node *L,int data)
{
    Node *node=L->next;
    while(node)
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
        node=node->next;
    }
    return false;
}

void print(Node *L)
{
    Node *node=L->next;
    while(node)
    {
        printf("%d -> ",node->data);
        node=node->next;
    }
    printf("NULL\n");
}

int main()
{
    Node *list=initList();
    headinsert(list,1);
    headinsert(list,2);
    headinsert(list,3);
    headinsert(list,4);
    print(list);
    tailinsert(list,5);
    tailinsert(list,6);
    tailinsert(list,7);
    tailinsert(list,8);
    print(list);
    delete(list,2);
    delete(list,6);
    print(list);
    return 0;
}