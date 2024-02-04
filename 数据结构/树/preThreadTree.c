#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int ltag;
    int rtag;
}TreeNode;

void creatTreeNode(TreeNode **T,char *data,int *index)
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
        //创建左结点
        creatTreeNode(&((*T)->lchild),data,index);
        //创建右结点
        creatTreeNode(&((*T)->rchild),data,index);
    }
}

void preThreadTree(TreeNode *T,TreeNode **pre)
{
    if(T)
    {
        if(T->lchild==NULL )//先判断，后赋值
        {
            T->lchild=*pre;
            T->ltag=1;
        }
        if( *pre !=NULL && (*pre)->rchild==NULL)
        {
            (*pre)->rchild=T;
            (*pre)->rtag=1;
        }
        *pre=T;
        if(T->ltag==0)//前面已经改变了指针的指向（指针可能指向的是前驱结点，而不是左孩子），所以需要特殊判断
        preThreadTree(T->lchild,pre);
        preThreadTree(T->rchild,pre);
    }
}

TreeNode *getNext(TreeNode *node)
{
    if(node->rtag==1)//如果结点的指针指向的是后驱结点，则直接返回
    {
        return node->rchild;
    }
    else
    {
        if(node->ltag==0)//如果结点的lchild指针指向的是左结点，则将遍历左结点
        {
            return node->lchild;
        }
        else//如果指针指向的是前驱，那么说明下一个将遍历的为右孩子
        {
            return node->rchild;
        }
    }
}

int main()
{
    char data[MAXSIZE];
    scanf("%s",data);
    int index=0;
    TreeNode *T;
    creatTreeNode(&T,data,&index);
    TreeNode *pre=NULL;
    preThreadTree(T,&pre);
    pre->rtag=1;
    pre->rchild=NULL;
    for(TreeNode *node=T;node!=NULL;node=getNext(node))
    {
        printf("%c ",node->data);
    }
    printf("\n");
    return  0; 
}
