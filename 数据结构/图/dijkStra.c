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

Graph * initGraph(int vexnum)
{
    Graph * G=(Graph *)malloc(sizeof(Graph));
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
            if(G->arcs[i][j] !=0 && G->arcs[i][j]!=MAX)
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
        if(G->arcs[index][i] >0 &&G->arcs[index][i]!=MAX &&!visit[i])
        {
            DFS(G,visit,i);
        }
    }
}

int getMin(Graph *G,int *D,int *S)
{
    int min=MAX;
    int index;
    for(int i=0;i<G->vexNum;i++)
    {
        if(!S[i]&&min>D[i])
        {
            min=D[i];
            index=i;
        }
    }
    return index;
}

void dijkstra(Graph *G,int index)
{
    //首先新建3个数组
    int *S=(int *)malloc(sizeof(int)*G->vexNum);//记录了目标结点到其他结点的最短路径是否求得
    int *P=(int *)malloc(sizeof(int)*G->vexNum);//记录了目标结点的到其他顶点的最短路径的前驱结点
    int *D=(int *)malloc(sizeof(int)*G->vexNum);//记录了目标结点到其他结点的最短路径的长度
    //初始化数组
    for(int i=0;i<G->vexNum;i++)
    {
        if(i==index)
        S[i]=1;
        else
        S[i]=0;
        if(G->arcs[index][i]>0 && G->arcs[index][i]!=MAX)//如果起始顶点与后续结点连通，那么后续结点的前驱结点为index
        P[i]=index;
        else
        P[i]=-1;
        D[i]=G->arcs[index][i];
    }
    for(int i=0;i<G->vexNum-1;i++)//找最小边，循环结点数-1次
    {
        int index=getMin(G,D,S);//最小边
        S[index]=1;//找到了最短路径，接下来去调整数组
        for(int j=0;j<G->vexNum;j++)
        {
            if(D[index]+G->arcs[index][j]<D[j] && !S[j])//如果中转结点的值小于原先到达的值，那么调整最小追，并将P数组中的前驱结点进行更改
            {
                D[j]=D[index]+G->arcs[index][j];
                P[j]=index;
            }
        }
    }
    for(int i=0;i<G->vexNum;i++)
    {
        printf("%d\t",S[i]);
    }
    printf("\n");
    for(int i=0;i<G->vexNum;i++)
    {
        printf("%d\t",P[i]);
    }
    printf("\n");
    for(int i=0;i<G->vexNum;i++)
    {
        printf("%d\t",D[i]);
    }
    printf("\n");
}

int main()
{
    Graph * G=initGraph(7);
    int *visit=(int *)malloc(sizeof(int)*G->vexNum);
    for(int i=0;i<G->vexNum;i++)
    {
        visit[i]=0;
    }
    int arc[7][7]={
        {0,12,MAX,MAX,MAX,16,14},
        {12,0,10,MAX,MAX,7,MAX},
        {MAX,10,0,3,5,6,MAX},
        {MAX,MAX,3,0,4,MAX,MAX},
        {MAX,MAX,5,4,0,2,8},
        {16,7,6,MAX,2,0,9},
        {14,MAX,MAX,MAX,8,9,0}
    };
    creatGraph(G,"1234567",(int *)arc);
    DFS(G,visit,0);
    printf("\n");
    dijkstra(G,0);
    return 0;
}