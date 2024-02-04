#include <stdio.h>
#include <stdlib.h>

#define MAX 32767

typedef struct Graph
{
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
}Graph;

typedef struct Stack//频繁用循环输出入度为0的点效率是比较低的，我们定义栈，然后将入度为0的结点压进去
{
    int data;
    struct Stack *next;
    
}Stack;

Stack * initStack()
{
    Stack *S=(Stack *)malloc(sizeof(Stack));
    S->data=0;
    S->next=NULL;
    return S;
}

int isEmpty(Stack *S)
{
    if(S->next == NULL)
    {
        return 1;
    }
    return 0;
}

void push(Stack *S,int data)
{
    Stack *node=(Stack *)malloc(sizeof(Stack));
    node->data=data;
    node->next=S->next;
    S->next=node;
    S->data++;
}

int pop(Stack *S)
{
    if(isEmpty(S))
    {
        return -1;
    }
    else
    {
        Stack *node=S->next;
        int data=node->data;
        S->next=node->next;
        free(node);
        return data;
    }
}

int *findInDegrees(Graph *G)//计算每一个结点的入度
{
    int *find=(int *)malloc(sizeof(int)*G->vexNum);
    for(int i=0;i<G->vexNum;i++)
    {
        find[i]=0;
    }
    for(int i=0;i<G->vexNum;i++)
    {
        for(int j=0;j<G->vexNum;j++)
        {
            if(G->arcs[i][j])
            {
                find[j]++;
            }
        }
    }
    return find;
}

void topologicalSort(Graph *G)
{
    int index=0;
    int *top=(int *)malloc(sizeof(int)*G->vexNum);//用来存储最后的序列
    int *find=findInDegrees(G);
    Stack *S=initStack();
    for(int i=0;i<G->vexNum;i++)
    {
        if(find[i]==0)
        {
            push(S,i);
        }
    }
    while(!isEmpty(S))
    {
        int vex=pop(S);
        top[index++]=vex;
        for(int i=0;i<G->vexNum;i++)
        {
            if(G->arcs[vex][i]==1)
            {
                find[i]=find[i]-1;
                if(find[i]==0)//这个判断在内部
                {
                    push(S,i);
                }
            }
            
        }
    }
    for(int i=0;i<G->vexNum;i++)
    {
        printf("\033[31m%c\t",G->vexs[top[i]]);
    }
    /* if(index<G->vexNum)有环的话
    {

    } */
}

Graph *initGraph(int vexnum)
{
    Graph *G=(Graph *)malloc(sizeof(Graph));
    G->vexs=(char *)malloc(sizeof(char)*vexnum);
    G->arcs=(int **)malloc(sizeof(int *)*vexnum);
    for(int i=0;i<vexnum;i++)
    {
        G->arcs[i]=(int *)malloc(sizeof(int)*vexnum);
    }
    G->vexNum=vexnum;
    G->arcNum=0;
    return G;
}

void creatGraph(Graph *G,char *vexs,int *arcs)
{
    for(int i=0;i<G->vexNum;i++)
    {
        G->vexs[i]=vexs[i];
        for(int j=0;j<G->vexNum;j++)
        {
            G->arcs[i][j]=*(arcs+i*G->vexNum+j);
            if(G->arcs[i][j]!=0 )
            {
                G->arcNum++;
            }
        }
    }
    G->arcNum/=2;
}

void DFS(Graph *G,int *visit,int index)
{
    printf("%c\t",G->vexs[index]);
    visit[index]=1;
    for(int i=0;i<G->vexNum;i++)
    {
        if(G->arcs[index][i]==1 &&!visit[i])
        {
            DFS(G,visit,i);
        }
    }
}

int main()
{
    Graph *G=initGraph(6);
    int *visit=(int *)malloc(sizeof(int)*G->vexNum);
    for(int i=0;i<G->vexNum;i++)
    {
        visit[i]=0;
    }
    int arcs[6][6]={
        {0,1,1,1,0,0},
        {0,0,0,0,0,0},
        {0,1,0,0,1,0},
        {0,0,0,0,1,0},
        {0,0,0,0,0,0},
        {0,0,0,1,1,0}
    };
    creatGraph(G,"123456",(int *)arcs);
    DFS(G,visit,0);
    printf("\n");
    topologicalSort(G);
    printf("\n");
    return 0;
}