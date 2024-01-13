#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node *next;
}Node;

Node * initList()//头结点的数据域来存储链表中的结点数
{
    Node *list=(Node *)malloc(sizeof(Node));
    list->next=NULL;
    list->data=0;
    return list;
}

void headInsert(Node * list,int data)//头插法
{
    Node *node=(Node *)malloc(sizeof(Node));
    node->data=data;
    node->next=list->next;
    list->next=node;
    list->data++;
}

void tailInsert(Node * list,int data)//尾插法
{
    Node *head=list;
    Node *node=(Node *)malloc(sizeof(Node));
    node->data=data;
    node->next=NULL;//找最后一个结点
    list=list->next;//指向链表中的第一个元素
    while(list->next!=NULL)
    {
        list=list->next;
    }
    list->next=node;
    head->data++;
}

void numInsert(Node * list,int data ,int num)//指定位置插入
{
    if(num> list->data)
    {
        return ;
    }
    if(num<=0)
    {
        headInsert(list,data);
    }
    else 
    {
        Node * current=list->next;
        for(int i=1;current!=NULL;i++)
        {
            if(i==num)
            {
                Node *insertnode=(Node *)malloc(sizeof(Node));
                insertnode->data=data;
                insertnode->next=current->next;
                current->next=insertnode;
                return ;
            }
            current=current->next;
        }
    }
}

void deleNode(Node *list,int data)
{
    Node *pre=list;
    Node *current=list->next;
    while(current)//也可以用for循环使用list-data来删除
    {
        if(current->data==data)
        {
            pre->next=current->next;
            free(current);
            break;
        }
        pre=current;
        current=current->next;
    }
    list->data--;
}

void print(Node *list)
{
    list=list->next;
    while(list)
    {
        printf("%d ",list->data);
        list=list->next;  
    }
    printf("\n"); 
}

int main()
{
    Node *list=initList();
    headInsert(list,1);
    headInsert(list,2);
    headInsert(list,3);
    headInsert(list,4);
    headInsert(list,5);
    numInsert(list,0,5);
    tailInsert(list,6);
    tailInsert(list,7);
    tailInsert(list,8);
    tailInsert(list,9);
    tailInsert(list,10);
    print(list);
    deleNode(list,2);
    print(list);
    return 0;
}