#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50

typedef struct TreeNode//后序遍历的时候需要一个指针指向结点的父亲，所以需要变为3叉链表
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    struct TreeNode *parent;
    int ltag;
    int rtag;
}TreeNode;

void creatTree(TreeNode ** T,char *data,int *index,TreeNode *parent)
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
        (*T)->parent=parent;
        creatTree(&((*T)->lchild),data,index,*T);
        creatTree(&((*T)->rchild),data,index,*T);
    }
}

void postThreadTree(TreeNode *T,TreeNode **pre)
{
    if(T)
    {
        postThreadTree(T->lchild,pre);
        postThreadTree(T->rchild,pre);
        if(T->lchild==NULL)
        {
            T->ltag=1;
            T->lchild=*pre;
        }
        if(*pre!=NULL && (*pre)->rchild==NULL)
        {
            (*pre)->rtag=1;
            (*pre)->rchild=T;
        }
        *pre=T;
    }
}

TreeNode * getFirst(TreeNode *T)
{
    while(T->ltag==0)//要用ltag与rtag进行判断，经过线索化指针的指向已经改变了 
    {
        T=T->lchild; 
    }
    if(T->rtag==0)
    {
        return getFirst(T->rchild);
    }
    return T;
}

TreeNode * getNext(TreeNode *node)
{
    if(node->rtag==1)//如果node的右结点指向后继，则返回右结点
    {
        return node->rchild;
    }
    else//则说明该结点具有右结点
    {
        if(node->parent==NULL)//如果该结点的父结点为NULL,则该结点为根节点，遍历结束
        {
            return NULL;
        }
        else if(node->parent->rchild==node)//如果该结点为右孩子的话
        {
            return node->parent;//那么下一步遍历的即为父结点
        }
        else//左孩子
        {
            if(node->parent->rtag==0)//如果父结点的右孩子存在
            {
                getFirst(node->parent->rchild);//以父结点的右孩子进行根再次寻找
            }
            else
            {
                return node->parent;//不存在的话开始遍历根节点
            }
        }
    }
}

int main()
{
    TreeNode *T;
    char data[MAXSIZE];
    scanf("%s",data);
    int index=0;
    creatTree(&T,data,&index,NULL);
    TreeNode *pre=NULL;
    postThreadTree(T,&pre);
    for(TreeNode *node=getFirst(T);node!=NULL;node=getNext(node))
    {
        printf("%c ",node->data);
    }
    printf("\n");
    return 0;
}