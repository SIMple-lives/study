#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 6

typedef struct TreeNode
{
    int data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TreeNode;

TreeNode * bstSearch(TreeNode *T,int key)//查找key值
{
    if(T)
    {
        if(T->data==key)
        {
            return T;
        }
        else if(key<T->data)
        {
            return bstSearch(T->lchild,key);
        }
        else
        {
            return bstSearch(T->rchild,key);
        }
    }
    else
    {
        return NULL;
    }
}

void  * bstInsert(TreeNode **T,int  key)
{
    if(*T==NULL)
    {
        *T=(TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data=key;
        (*T)->lchild=NULL;
        (*T)->rchild=NULL;
    }
    else if(key==(*T)->data)
    {
        return ;
    }
    else if(key <(*T)->data)
    {
        bstInsert(&((*T)->lchild),key);
    }
    else
    {
        bstInsert(&((*T)->rchild),key);
    }
}

void preOrder(TreeNode *T)
{
    if(T)
    {
        printf("%d ",T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

int main()
{
    TreeNode *T=NULL;
    int nums[MAXSIZE]={4,5,19,23,2,8};
    for(int i=0;i<MAXSIZE;i++)
    {
        bstInsert(&T,nums[i]);
    }
    preOrder(T);
    printf("\n");
    return 0;
}