#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50
typedef struct TreeNode 
{
    char data;
    struct TreeNode * lchild;
    struct TreeNode * rchild;
}TreeNode;

typedef struct QueueNode
{
    TreeNode *data;
    struct QueueNode *next;
    struct QueueNode *prev;
}QueueNode;

void creatTreeNode(TreeNode **T,char *data,int *index)
{
    char ch;
    ch=data[*index];
    *index+=1;
    if(ch == '#')
    {
        *T=NULL;
    }
    else
    {
        *T=(TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data=ch;
        creatTreeNode(&((*T)->lchild),data,index);
        creatTreeNode(&((*T)->rchild),data,index);
    }
}

void printTreeNode(TreeNode *T)
{
    if(T==NULL)
    {
        return ;
    }
    else
    {
        printf("%c ",T->data);
        printTreeNode(T->lchild);
        printTreeNode(T->rchild);
    }
}

QueueNode *initQueue()
{
    QueueNode *Q=(QueueNode *)malloc(sizeof(QueueNode));
    Q->data=NULL;
    Q->next=Q;
    Q->prev=Q;
    return Q;
}

void enqueue(TreeNode*data,QueueNode *Q)//尾插
{
    QueueNode *node=(QueueNode *)malloc(sizeof(QueueNode));
    node->data=data;
    if(Q->next==Q)
    {
        node->prev=Q;
        node->next=Q; 
        Q->prev=node;
        Q->next=node;
    }
    else 
    {
        node->next=Q;
        node->prev=Q->prev;
        Q->prev->next=node;
        Q->prev=node;
    }
    
}

int isEmpty(QueueNode *Q)
{
    if(Q->next==Q)
    {
        return 1;
    }
    return  0;
}

QueueNode * deQueue(QueueNode *Q)
{
    if(isEmpty(Q))
    {
        return NULL;
    }
    else 
    {
            QueueNode *node=Q->next;
            Q->next->next->prev=Q;
            Q->next=Q->next->next;
            return node;
    }
}

void levelTraverse(QueueNode *Q,TreeNode *T)
{
    enqueue(T,Q);//先将根结点入队
    while(!isEmpty(Q))//非空
    {
        QueueNode *node=deQueue(Q);//然后将元素出队
        printf("%c ",node->data->data);//然后进行访问
        if(node->data->lchild)//在分别将出队元素的左右孩子分别放进去
        {
            enqueue(node->data->lchild,Q);
        }
        if(node->data->rchild)
        {
            enqueue(node->data->rchild,Q);  
        }
    }
}

int main()
{
    TreeNode *T;
    int index=0;
    QueueNode *Q=initQueue();
    char data[MAXSIZE];
    scanf("%s",data);
    creatTreeNode(&T,data,&index);
    printTreeNode(T);
    printf("\n");
    levelTraverse(Q,T);
    printf("\n");
    return 0;
}