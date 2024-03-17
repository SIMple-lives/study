#include <stdio.h>
#include <stdlib.h>

/**
 * 图顶点之间不通的话，那么领接矩阵的值MAX 
 * 如果顶点为本身的话，那么邻接矩阵的值为0
 */
 
#define MAX 32767

typedef struct Graph
{
    char *vexs;
    int  ** arcs;
    int vexNum;
    int arcNum;
}Graph;

typedef struct Edge
{
    char vex;//记录U集合到最小边的起始结点
    int weight;//记录最小边
}Edge;

/*
当edge.wight等于0时，代表当前结点已经加入集合u,与自身与自身的权值为0相呼应
*/

Edge * initEdge(Graph* G,int  index)
{
    Edge *edge=(Edge *)malloc(sizeof(Edge)*G->vexNum);
    for(int i=0;i<G->vexNum;i++)
    {
        edge[i].vex=G->vexs[index];//将该结点加入到集合U中
        edge[i].weight=G->arcs[index][i];
    }
    return edge;
}

int getMinEdge(Edge * edge,Graph *G)//在edge终寻找最小的那条边
{
    int index;
    int min=MAX;
    for(int i=0;i<G->vexNum;i++)
    {
        if(edge[i].weight!=0 && min>edge[i].weight)
        {
            index=i;
            min=edge[i].weight;
        }
    }
    return index;
}

void prime(Graph *G,int index)
{
    int min;
    Edge *edge=initEdge(G,index);
    for(int i=0;i<G->vexNum-1;i++)//一共需要找几次
    {
        min=getMinEdge(edge,G);//找到最小边的终点
        printf("v%c -> v%c   weight=%d\n",edge[min].vex,G->vexs[min],edge[min].weight);
        edge[min].weight=0;//将结点加入到U数组当中
        for(int j=0;j<G->vexNum;j++)//对当前加入的结点的权值进行赋值
        {
            if(G->arcs[min][j]<edge[j].weight)
            {
                edge[j].weight=G->arcs[min][j];//继续添加较小的边
                edge[j].vex=G->vexs[min];//对起始结点进行赋值
            }
        }
    } 
}

Graph *initGraph(int vexsNum)
{
    Graph *G=(Graph *)malloc(sizeof(Graph));
    G->vexs=(char *)malloc(sizeof(char )*vexsNum);
    G->arcs=(int **)malloc(sizeof(int *)*vexsNum);
    for(int i=0;i<vexsNum;i++)
    {
        G->arcs[i]=(int *)malloc(sizeof(int )*vexsNum);
    }
    G->vexNum=vexsNum;
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
            if(G->arcs[i][j]!=0 && G->arcs[i][j]!=MAX)
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
        if(G->arcs[index][i]>0 &&G->arcs[index][i]!=MAX && !visit[i])
        {
            DFS(G,visit,i);
        }
    }
}

int main()
{
    Graph *G=initGraph(6);
    int *visit=(int *)malloc(sizeof(int )*G->vexNum);
    for(int i=0;i<G->vexNum;i++)
    {
        visit[i]=0;
    }
    int arcs[6][6]={
        {0,6,1,5,MAX,MAX},
        {6,0,5,MAX,3,MAX},
        {1,5,0,5,6,4},
        {5,MAX,5,0,MAX,2},
        {MAX,3,6,MAX,0,6},
        {MAX,MAX,4,2,6,0}
        };
    creatGraph(G,"123456",((int *)arcs));
    DFS(G,visit,0);
    printf("\n");
    prime(G,0);
    return 0;
}