#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int level;//树的阶数
    int keyNum;//关键字数量
    int childNum;//孩子数量
    int *keys;//关键字数组
    struct Node **children;//孩子数组
    struct Node *parent; //父亲指针
}Node;

// 初始化结点
Node *initNode(int level)
{
    Node *node=(Node *)malloc(sizeof(Node));
    node->level=level;
    node->keyNum=0;
    node->childNum=0;
    node->keys=(int *)malloc(sizeof(int)*(level+1));
    node->children=(Node **)malloc(sizeof(Node *)*level);
    node->parent=NULL;
    int i;
    for(i=0;i<level;i++)
    {
        node->keys[i]=0;
        node->children[i]=NULL;
    }
    return node;
}

//在结点寻找合适的插入索引
int findSuiteindex(Node *node,int data)
{
    int index=0;
    for(index=1;index<=node->keyNum;index++)
    {
        if(data<node->keys[index])
        {
            break;
        }
    }
    return index;
}

//找到合适的叶子结点
Node *findSuiteleafNode(Node *T,int data)//寻找插入的叶子结点
{
    if(T->childNum==0)
    {
        return  T;
    }
    else
    {
        int index=findSuiteindex(T,data); 
        return findSuiteleafNode(T->children[index-1],data);
    }
}

void addData(Node *node,int data,Node **T)//插入可能会对根结点进行修改，需要二级指针接收根
{
    int index=findSuiteindex(node,data);
    for(int i=node->keyNum;i>=index;i--)//将中间的位置空出来
    {
        node->keys[i+1]=node->keys[i];
    }
    node->keys[index]=data;
    node->keyNum++;
    //判断是否需要分裂
    if(node->keyNum==node->level)
    {
        //找到分裂的位置
        int mid=node->level /2 +node->level%2;
        //分裂过程，将分裂结点的左端与右端的关键字及后续生成新的结点
        Node *lchild=initNode(node->level);
        Node *rchild=initNode(node->level);
        for(int i=1;i<mid;i++)//关键字是从1开始赋值的            就这里错了

        {
            addData(lchild,node->keys[i],T);
            /* lchild->keys[i]=node->keys[i];
            lchild->keyNum++; */
        }
        for(int i=mid+1;i<=node->keyNum;i++)
        {
            addData(rchild,node->keys[i],T);
        }
        //将中间的结点的左右两边结点的孩子孩子赋给两边的树
        for(int i=0;i<mid;i++)
        {
            lchild->children[i]=node->children[i];
            if(node->children[i]!=NULL)//更改父亲结点
            {
                node->children[i]->parent=lchild;
                lchild->childNum++;
            }
        }
        int index=0;//右孩子要制定位置插入
        for(int i=mid;i<node->childNum;i++)
        {
            rchild->children[index++]=node->children[i];
            if(node->children[i]!=NULL)
            {
                node->children[i]->parent=rchild;
                rchild->childNum++;
            }
        }
        //判读父亲结点是否为空结点，对父亲进行操作
        if(node->parent ==NULL)
        {
            Node *newparent=initNode(node->level);
            addData(newparent,node->keys[mid],T);
            newparent->children[0]=lchild;
            newparent->children[1]=rchild;
            newparent->childNum=2;
            lchild->parent=newparent;
            rchild->parent=newparent;
            *T=newparent;
        }
        else
        {
            int index=findSuiteindex(node->parent,node->keys[mid]);
            lchild->parent=node->parent;
            rchild->parent=node->parent;
            node->parent->children[index-1]=lchild;
            if(node->parent->children[index]==NULL)
            {
                for(int i=node->parent->childNum-1;i>=index;i--)
                {
                    node->parent->children[i+1]= node->parent->children[i];
                }
            }
            node->parent->children[index]=rchild;
            node->parent->childNum++;
            addData(node->parent,node->keys[mid],T);
        }
    }
}

void insert(Node **T,int data)
{
    Node *node=findSuiteleafNode(*T,data);
    addData(node,data,T);
}

void printTree(Node *T)
{
   if (T != NULL) 
   {
        for (int i  = 1; i <= T -> keyNum; i++) 
        {
            printf("%d ", T -> keys[i]);
        }
        printf("\n");
        for (int i = 0; i < T -> childNum; i++) 
        {
            printTree(T -> children[i]);
        }
    }
}

Node* find(Node* node, int data) 
{
    if (node == NULL) 
    {
        return NULL;
    }
    for (int i = 1; i <= node -> keyNum; i++) 
    {
        if (data == node -> keys[i]) 
        {
            return node;
        }
        else if (data < node -> keys[i]) 
        {
            return find(node -> children[i - 1], data);
        }
        else 
        {
            if (i != node -> keyNum && data < node -> keys[i + 1]) 
                return find(node -> children[i], data);
        }
    }
    return find(node -> children[node -> keyNum], data);
}

int main()
{
    Node *T=initNode(5);
    insert(&T,1);
    insert(&T,2);
    insert(&T,3);
    insert(&T,4);
    insert(&T,5);
    insert(&T,6);
    insert(&T,7);
    insert(&T,8);
    insert(&T,9);
    insert(&T,10);
    insert(&T,11);
    insert(&T,12);
    insert(&T,13);
    insert(&T,14);
    insert(&T,15);
    printTree(T);
    return 0;
}