#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50

typedef struct TreeNode
{
    char data;
    struct TreeNode * lchild;
    struct TreeNode * rchild;
}TreeNode;

typedef struct StackNode
{
    TreeNode *data;
    struct StackNode *next;
}StackNode;

void creatTree(TreeNode **T,char *data, int *index)
{
    char ch;
    ch=data[*index];
    *index+=1;//一定记住是*index+=1
    if(ch=='#')
    {
        *T=NULL;
    }
    else
    {
        *T=(TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data=ch;
        creatTree(&((*T)->lchild),data,index);
        creatTree(&((*T)->rchild),data,index);
    }
}

StackNode *initStack()
{
    StackNode * S=(StackNode *)malloc(sizeof(StackNode));
    S->data=NULL;
    S->next=NULL;
    return S;
}

void push(StackNode *S,TreeNode *T)//栈，头插法
{
    StackNode *node=(StackNode *)malloc(sizeof(StackNode));
    node->data=T;
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

StackNode *pop(StackNode *S)//出栈，头部删除
{
    if(isEmpty(S))
    {
        return NULL;
    }
    else
    {
        StackNode *node=S->next;
        S->next=node->next;
        return node;
    }
}

void preOrder(TreeNode * T)//前序遍历
{
    TreeNode *node=T;
    StackNode *S=initStack();
    while(node || !isEmpty(S))
    {
        if(node)
        {
            printf("%c ",node->data);
            push(S,node);
            node=node->lchild;
        }
        else
        {
            node=pop(S)->data;
            node=node->rchild;
        }
    }
}

void inOrder(TreeNode *T)//中序遍历
{
    TreeNode *node=T;
    StackNode *S=initStack();
    while(node || !isEmpty(S))
    {
        if(node)
        {
            push(S,node);
            node=node->lchild;
        }
        else
        {
            node=pop(S)->data;
            printf("%c ",node->data);
            node=node->rchild;
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
    preOrder(T);
    printf("\n");
    inOrder(T);
    printf("\n");
    return 0;
}