#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAXSIZE 7

typedef struct TreeNode//
{
    int weight;//权值
    int parent;//父结点
    int lchild;//左孩子
    int rchild;//右孩子
}TreeNode;

typedef struct HFTree
{
    TreeNode *data;//采用顺序存储的方式来存储结点
    int length;//长度
}HFTree;

HFTree *initTree(int *weight,int length)
{
    HFTree *T=(HFTree *)malloc(sizeof(HFTree));//创建树
    T->data=(TreeNode *)malloc(sizeof(TreeNode)*(2*length-1));//创建数组来存储各个结点，有观察可得最后结点个数为权值数组长度的2倍-1；
    T->length=length;//赋值树的长度
    for(int i=0;i<length;i++)
    {
        T->data[i].weight=weight[i];//挨个赋值结点的权值，并初始化指针
        T->data[i].parent=0;
        T->data[i].lchild=-1;
        T->data[i].rchild=-1;
    }
    return T;
}

int * selectMin(HFTree *T)//找到权值数组中最小的两个值，并将他们返回
{
    int min=INT_MAX;
    int second=INT_MAX;
    int minindex;
    int secindex;
    for(int i=0;i<T->length;i++)
    {
        if(T->data[i].parent==0)//找到的必须是不含父亲结点的，含父亲结点的代表已经与一结点构成树，所以需要进行特判
        {
            if(T->data[i].weight<min)
            {
                min=T->data[i].weight;
                minindex=i;
            }
        }
    }
    for(int i=0;i<T->length;i++)
    {
        if(T->data[i].parent==0 && i!=minindex)
        {
            if(T->data[i].weight<second)
            {
                second=T->data[i].weight;
                secindex=i;
            }
        }
    }
    int *res=(int *)malloc(sizeof(int)*2);
    res[0]=minindex;
    res[1]=secindex;
    return res;//返回较小两值的下标
}

void creatHFTree(HFTree *T)
{
    int *res;//接收两个较小值
    int min;
    int second;
    int len=T->length*2-1;//长度
    for(int i=T->length;i<len;i++)//为新生成的各个父结点赋值
    {
        res=selectMin(T);
        min=res[0];
        second=res[1];
        T->data[i].weight=T->data[min].weight+T->data[second].weight;//新结点权值
        T->data[i].lchild=min;//并将新结点的左右孩子进行赋值
        T->data[i].rchild=second;
        T->data[min].parent=i;//将两个较小值的父结点进行设置，代表生成子树，后续这两结点将不参与运算
        T->data[second].parent=i;
        T->length++;//对树的长度进行加一
    }
}

void preOrder(HFTree *T,int index)//前序遍历
{
    if(index != -1)
    {
        printf("%d ", T->data[index].weight);
        preOrder(T,T->data[index].lchild);
        preOrder(T,T->data[index].rchild);
    }
}


int main()
{
    int weight[MAXSIZE]={5,1,3,6,11,2,4};//权值数组
    HFTree *T=initTree(weight,MAXSIZE);
    int *res=selectMin(T);
    creatHFTree(T);
    preOrder(T,T->length-1);
    printf("\n");
    return  0;
}