#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

typedef struct TreeNode//由于要时刻调整树，所以需要增加height来标记树的高度
{
    int data;
    int height;//存储树的高度，用来判断高度差，时刻调整二叉树，使得为平衡二叉树
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TreeNode;

int getHeight(TreeNode *node)//获取树的高度
{
    return node?node->height:0;
}

int max(int a,int b)//求最大值
{
    return a>b? a : b ;
}

void RRRotation(TreeNode *node ,TreeNode ** root)//node为父亲结点
{
    TreeNode *temp=node->rchild;//找到中间的那个结点//TreeNode *temp=node.rchild;
    node->rchild=temp->lchild;//中间结点的左孩子变为父亲结点的右孩子node->rchild=temp->lchild
    temp->lchild= node; //然后左孩子变为原先的父亲结点//temp->lchild=node;
    node->height=max(getHeight(node->lchild),getHeight(node->rchild))+1;
    temp->height=max(getHeight(temp->lchild),getHeight(temp->rchild))+1;
    *root=temp;//根节点变为中间的那个结点
}

void LLRotation(TreeNode *node,TreeNode **root)//将中间的结点取出
{
    TreeNode *temp=node->lchild;//找到中间的那个结点
    node->lchild= temp->rchild;//中间结点的右孩子变为父亲结点的左孩子
    temp->rchild=node;//右孩子变为自己原先的父亲
    node->height=max(getHeight(node->lchild),getHeight(node->rchild))+1;//更新高度
    temp->height=max(getHeight(temp->lchild),getHeight(temp->rchild))+1;
    *root=temp;//根节点变为中间的那个结点
}

void avlInsert(TreeNode **T,int data)
{
    if(*T==NULL)
    { 
        *T=(TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data=data;
        (*T)->height=0;
        (*T)->lchild=NULL;
        (*T)->rchild=NULL;
    }
    else if(data<(*T)->data)
    {
        avlInsert(&((*T)->lchild),data);
        //拿到当前左右子树的高度
        int lheight=getHeight((*T)->lchild);
        int rheight=getHeight((*T)->rchild);
        //判断高度差，插在了左边，所以结果只可能为LL,LR
        if(lheight-rheight==2)
        {
            if(data<(*T)->lchild->data)//LL
            {
                LLRotation(*T,T);//传进去的为最上面的的那个根结点
            }
            else//LR 
            {
                RRRotation((*T)->lchild,&(*T)->lchild);//LR就是根节点的左孩子的RR与根节点的LL
                LLRotation(*T,T);
            }
        }
    }
    else if(data>(*T)->data)
    {
        avlInsert(&((*T)->rchild),data); 
        int lheight=getHeight((*T)->lchild);
        int rheight=getHeight((*T)->rchild);
        if(rheight-lheight==2)
        {
            if(data>(*T)->rchild->data)//RR
            {
                RRRotation(*T,T);
            }
            else//RL
            {
                LLRotation((*T)->rchild,&(*T)->rchild);//RL就是一次根节点右孩子的LL与根节点的RR
                RRRotation(*T,T);
            }
        }
    }
    (*T)->height=max(getHeight((*T)->lchild),getHeight((*T)->rchild))+1;//在这里更新高度，树的高度为子树的最大值加一
}

void  preOrder(TreeNode *T)
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
    int nums[MAXSIZE]={1,8,6,7,10};
    for(int i=0;i<5;i++)
    {
        avlInsert(&T,nums[i]);
    }
    preOrder(T);
    printf("\n");
    return 0;
}