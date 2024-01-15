#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode
{
    char  data;
    struct TreeNode * lchild;
    struct TreeNode * rchild;
}TreeNode;

void creatTree(TreeNode ** T,char *ch,int *index)
{
    char data;
    data=ch[*index];
    *index +=1;
    if(data=='#')//此时为空结点
    {
        *T=NULL;
    }
    else
    {
        *T=(TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data=data;
        creatTree(&((*T)->lchild),ch,index);//创建左子树
        creatTree(&((*T)->rchild),ch,index);//创建右子树 
    }
}

void printTree(TreeNode *T)//前序遍历
{
    if(T==NULL)
    {
        return ;
    }
    else
    {
        //先输出值，然后在分别遍历左子树与右子树
        printf("%c ",T->data);
        printTree(T->lchild);
        printTree(T->rchild);
    }
}

void inprintTree(TreeNode * T)//中序遍历
{
    if(T==NULL)
    {
        return ;
    }
    else
    {
        inprintTree(T->lchild);
        printf("%c ",T->data);
        inprintTree(T->rchild);
    }
}

void poxprintTree(TreeNode *T)
{
    if(T==NULL)
    {
        return ;
    }
    else
    {
        poxprintTree(T->lchild);
        poxprintTree(T->rchild);
        printf("%c ",T->data);
    }
}

int main(int argc,char *argv[])
{
    TreeNode *T;
    int index=0;
    if(argc!=1)
    creatTree(&T,argv[1],&index);
    else
    {
        char data[20];
        scanf("%s",data);
        creatTree(&T,data,&index);
    }
    printTree(T);
    printf("\n");
    inprintTree(T);
    printf("\n");
    poxprintTree(T);
    printf("\n");
    return 0;
}