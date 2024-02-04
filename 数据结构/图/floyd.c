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

Graph *initGraph(int vexnum)
{
    Graph* G=(Graph *)malloc(sizeof(Graph));
    G->vexs=(char *)malloc(sizeof(char)*vexnum);
    G->arcs=(int **)malloc(sizeof(int *)*vexnum);
    for(int i=0;i<vexnum;i++)
    {
        G->arcs[i]=(int *)malloc(sizeof(int)*vexnum);
    }
    G->vexNum=vexnum;
    G->arcNum=0;
    return  G;
}

void creatGraph(Graph *G,char *vexs,int *arcs)
{
    for(int i=0;i<G->vexNum;i++)
    {
        G->vexs[i]=vexs[i];
        for(int j=0;j<G->vexNum;j++)
        {
            G->arcs[i][j]=*(arcs+i*G->vexNum+j);
            if(G->arcs[i][j] !=0 &&G->arcs[i][j]!=MAX)
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

void floyd(Graph *G)
{
    //构建辅助数组
    int D[G->vexNum][G->vexNum];
    int P[G->vexNum][G->vexNum];
    //初始化辅助
    for(int i=0;i<G->vexNum;i++)
    {
        for(int j=0;j<G->vexNum;j++)
        {
            D[i][j]=G->arcs[i][j];
            if(G->arcs[i][j]>0 &&G->arcs[i][j]!=MAX)
            P[i][j]=i;
            else
            P[i][j]=-1;
        }
    }
    for(int i=0;i<G->vexNum;i++)
    {
        for(int j=0;j<G->vexNum;j++)
        {
            for(int k=0;k<G->vexNum;k++)
            {
                if(D[j][i]+D[i][k]<D[j][k])
                {
                    D[j][k]=D[j][i]+D[i][k];
                    P[j][k]=P[i][k];//将其赋值为前驱结点
                }
            }
        }
    }
    for(int i=0;i<G->vexNum;i++)
    {
        for(int j=0;j<G->vexNum;j++)
        {
            printf("%d\t",D[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<G->vexNum;i++)
    {
        for(int j=0;j<G->vexNum;j++)
        {
            printf("\033[31m%d\t\033",P[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    Graph *G=initGraph(4);
    int *visit=(int *)malloc(sizeof(int)*G->vexNum);
    for(int i=0;i<G->vexNum;i++)
    {
        visit[i]=0;
    }
    int arcs[4][4]={
        {0,1,MAX,3},
        {1,0,2,2},
        {MAX,2,0,8},
        {3,2,8,0}
    };
    creatGraph(G,"1234",(int *)arcs);
    DFS(G,visit,0);
    printf("\n");
    floyd(G);
    return 0;
}