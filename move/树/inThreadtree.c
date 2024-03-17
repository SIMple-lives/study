#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int ltag;//ltag=0代表指向的是自己的孩子
    int rtag;
}TreeNode;

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
        (*T)->ltag=0;
        (*T)->rtag=0;
        creatTree(&((*T)->lchild),data,index);
        creatTree(&((*T)->rchild),data,index);
    }
}

void initThreadTree(TreeNode *T,TreeNode **pre)//pre为前驱结点
{
    if(T)
    {
        initThreadTree(T->lchild,pre);
        if(T->lchild==NULL)//如果左孩子为空
        {
            T->ltag=1;//将设置为标志指向前驱结点
            T->lchild=*pre;//指针指向前一个结点
        }
        if(*pre!=NULL && (*pre)->rchild==NULL)//如果前一个结点的右孩子为空，
        {
            (*pre)->rtag=1;//设置标志位
            (*pre)->rchild=T;//则指向后继结点
        }
        *pre=T;
        initThreadTree(T->rchild,pre);
    }
}

TreeNode * getFirst(TreeNode *T)
{
    while(T->ltag==0)
    {
        T=T->lchild;
    }
    return T;
}

TreeNode * getNext(TreeNode *node)
{
    if(node->rtag==1)
    {
        return node->rchild;
    }
    else
    {
        return getFirst(node->rchild); 
    }
}

int main()
{
    char data[MAXSIZE];
    scanf("%s",data);
    int index=0;
    TreeNode *T;
    TreeNode *pre=NULL;
    creatTree(&T,data,&index);
    initThreadTree(T,&pre);
    pre->rtag=1;
    pre->rchild=NULL;
    for(TreeNode *node=getFirst(T);node !=NULL;node=getNext(node))
    {
        printf("%c ",node->data);
    }
    printf("\n");
    return  0;
}