#include <stdio.h>
#include <stdlib.h>

#define MAX 32767

typedef struct Graph
{
    char *vexs;
    int ** arcs;
    int vexNum;
    int arcNum;
}Graph;

typedef struct Edge
{
    int start;
    int end;
    int weight;
}Edge;

Edge * initEdge(Graph *G)
{
    Edge * edge=(Edge *)malloc(sizeof(Edge)*G->arcNum);
    int index=0;
    for(int i=0;i<G->vexNum;i++)
    {
        for(int j=i+1;j<G->vexNum;j++)
        {
            if(G->arcs[i][j]!=MAX)
            {
                edge[index].start=i;
                edge[index].end=j;
                edge[index].weight=G->arcs[i][j];
                index++;
            }
        }
    }
    return edge;
}

void sortEdge(Edge *edge,Graph *G)
{
    Edge temp;
    for(int i=0;i<G->arcNum-1;i++)
    {
        for(int j=0;j<G->arcNum-1-i;j++)
        {
            if(edge[j].weight>edge[j+1].weight)
            {
                temp=edge[j];
                edge[j]=edge[j+1];
                edge[j+1]=temp;
            }
        }
    }
}

void kruskal(Graph *G)
{
    int *connected=(int *)malloc(sizeof(int)*G->vexNum);//辅助数组，用来判断当前的连通分量
    for(int i=0;i<G->vexNum;i++)
    {
        connected[i]=i;
    }
    Edge *edge=initEdge(G);
    sortEdge(edge,G);
    for(int i=0;i<G->arcNum;i++)
    {
        int start=connected[edge[i].start];//起点的连通分量
        int end=connected[edge[i].end];//终点的连通分量
        if(start!=end)//当两个连通分量不相同的话，输出
        {
            printf("v%c -> v%c ,weight=%d\n",G->vexs[edge[i].start],G->vexs[edge[i].end],edge[i].weight);
            for(int j=0;j<G->vexNum;j++)//输出完之后进行调整
            {
                if(connected[j]==end)//找到当前边的终点
                {
                    connected[j]=start;//终点的连通分量赋值为起点的连通分量.
                }
            }
        }
    }
}

Graph *initGraph(int vexnum)
{
    Graph *G=(Graph *)malloc(sizeof(Graph));
    G->vexs=(char *)malloc(sizeof(char)*vexnum);
    G->arcs=(int **)malloc(sizeof(int *)*vexnum);
    for(int i=0;i<vexnum;i++)
    {
        G->arcs[i]=(int *)malloc(sizeof(int )*vexnum);
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
        if(G->arcs[index][i]>0 && G->arcs[index][i]!=MAX && !visit[i])
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
    kruskal(G);
    return  0;
}