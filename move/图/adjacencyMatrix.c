#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

typedef struct Graph
{
    char * vexs;
    int **arcs;//二级指针
    int vexnum;
    int arcnum;
}Graph;

typedef struct Queue
{
    int front;
    int rear;
    int data[MAXSIZE];
}Queue;

Queue * initQueue()
{
    Queue *Q=(Queue *)malloc(sizeof(Queue));
    Q->front=Q->rear=0;
    return Q;
}

int isFull(Queue *Q)
{
    if((Q->rear+1)%MAXSIZE ==Q->front)
    {
        return 1;
    }
    return 0;
}

int isEmpty(Queue *Q)
{
    if(Q->front==Q->rear)
    {
        return 1;
    }
    return 0;
}

int enQueue(Queue *Q,int data)
{
    if(isFull(Q))
    {
        return 0;
    }
    else
    {
        Q->data[Q->rear]=data;
        Q->rear=(Q->rear+1)%MAXSIZE;
        return 1;
    }
}

int deQueue(Queue *Q)
{
    if(isEmpty(Q))
    {
        return 0;
    }
    else
    {
        int data=Q->data[Q->front];
        Q->front=(Q->front+1)%MAXSIZE;
        return data;
    }
}

Graph * initGraph(int vexsnum)//初始化
{
    Graph * G=(Graph *)malloc (sizeof(Graph));
    G->vexs=(char *)malloc(sizeof(char )*vexsnum);
    G->arcs=(int **)malloc(sizeof(int *) * vexsnum);//二级指针，先给每一行的指针开辟空间
    for(int i=0;i<vexsnum;i++)
    {
        G->arcs[i]=(int *)malloc(sizeof(int )*vexsnum);//为每一行的元素开辟空间.
    }
    G->vexnum=vexsnum;
    G->arcnum=0;
    return G;
}

void creatGraph(Graph *G ,char *vexs,int *arcs)//arcs为领接数组
{
    for(int i=0;i<G->vexnum;i++)
    {
        G->vexs[i]=vexs[i];
        for(int j=0;j<G->vexnum;j++)
        {
            G->arcs[i][j]=*(arcs + i*G->vexnum+j);
            if(G->arcs[i][j] !=0)
            {
                G->arcnum++;
            }
        }
    }
    G->arcnum/=2;   
}

void DFS(Graph * G,int *visit,int index)//visit用来表示结点是否被访问，index表示用来开始遍历的结点的索引
{
    printf("%c\t",G->vexs[index]);
    visit[index]=1;
    for(int i=0;i< G->vexnum;i++)
    {
        if(G->arcs[index][i]==1 && !visit[i])//找到与index相连接的结点，并当没有被访问过的话就对其进行访问。
        {
            DFS(G,visit,i);
        }
    }
}

void BFS(Graph *G ,int *visit,int index)
{
    Queue *Q=initQueue();
    printf("%c\t",G->vexs[index]);
    visit[index]=1;//设置标记为已搜索
    enQueue(Q,index);//由于入队的是结点，所以要将访问过得结点入队，所以第二个参数穿进去的为刚开始的索引值.
    while(!isEmpty(Q))
    {
        int i=deQueue(Q);
        for(int j=0;j<G->vexnum;j++)
        {
            if(!visit[j]  && G->arcs[i][j]==1)
            {
                printf("%c\t",G->vexs[j]);//访问出队元素的每一个，并将其入队
                visit[j]=1;
                enQueue(Q,j);
            }
        }
    }
}

int main()
{
    Graph *G=initGraph(5);
    int *visit=(int *)malloc(sizeof(int)*G->vexnum);
    for(int i=0;i<G->vexnum;i++)
    {
        visit[i]=0;
    }
    int arcs[5][5]={
        0,1,1,1,0,
        1,0,1,1,1,
        1,1,0,0,0,
        1,1,0,0,1,
        0,1,0,1,0
    };
    creatGraph(G,"abcde",(int *)arcs);
    DFS(G,visit,0);
    printf("\n");
     for(int i=0;i<G->vexnum;i++)
    {
        visit[i]=0;
    }
    BFS(G,visit,0);
    printf("\n");
    return 0;
}