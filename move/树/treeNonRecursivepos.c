#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50

typedef struct TreeNode//由于要判断每一个结点是否被访问过，所以树中需要增加一个结点来查看是否被访问
{
    char data;
    int flag;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TreeNode;

typedef struct StackNode
{
    TreeNode *data;
    struct StackNode *next;
}StackNode;

void creatTree(TreeNode **T,char *data,int *index)
{
    char ch;
    ch=data[*index];
    *index+=1;
    if(ch=='#')
    {
        *T=NULL;
    }
    else
    {
        *T=(TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data=ch;
        (*T)->flag= 0;
        creatTree(&((*T)->lchild),data,index);
        creatTree(&((*T)->rchild),data,index);
    }
}

StackNode * initStack()
{
    StackNode  *S=(StackNode *)malloc(sizeof(StackNode));
    S->data=NULL;
    S->next=NULL;
    return S;
}

void push(StackNode *S,TreeNode *data)
{
    StackNode *node=(StackNode *)malloc(sizeof(StackNode));
    node->data=data;
    node->next=S->next;
    S->next=node;
}

int isEmpty(StackNode *S)
{
    if(S->next==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

StackNode *pop(StackNode *S)
{
    if(isEmpty(S))
    {
        return NULL;
    }
    StackNode *node=S->next;
    S->next=node->next;
    return node;
}

StackNode * getTop(StackNode *S)
{
    if(isEmpty(S))
    {
        return NULL;
    }
    else
    {
        StackNode *node=S->next;
        return node;
    }
}

void posOrder(TreeNode * T)
{
    TreeNode *node = T ;
    StackNode *S=initStack();
    while(node || !isEmpty(S))//当结点为空且全部出栈，则遍历结束
    {
        if(node)//不为空
        {
            push(S,node);//则进栈
            node=node->lchild;//向下遍历左孩子
        }
        else
        {
            TreeNode *top=getTop(S)->data;//拿到栈顶元素
            if(top->rchild && top->rchild->flag==0)//如果栈顶元素有右孩子并且没有被访问的话，则将右孩子进站
            {
                top=top->rchild;
                push(S,top);//右孩子进栈
                node=top->lchild;//重复寻找的步骤
            }
            else
            {
                top=pop(S)->data;//如果被访问过则出栈
                printf("%c ",top->data);//打印
                top->flag=1;//设置标志为
            }
        }
    }
}

int main()
{
    char data[MAXSIZE];
    scanf("%s",data);
    int index=0;
    TreeNode *T;
    creatTree(&T,data,&index);
    posOrder(T);
    printf("\n");
}