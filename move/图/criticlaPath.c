#include <stdio.h>
#include <stdlib.h>

#define MAX 32767

typedef struct Graph
{
    char *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
}Graph;

typedef struct Stack
{
    int data;
    struct Stack *next;
}Stack;

Stack *initStack()
{
    Stack *S=(Stack *)malloc(sizeof(Stack));
    S->next=NULL;
    S->data=0;
    return S;
}

void push(Stack *S,int data)
{
    Stack *node=(Stack *)malloc(sizeof(Stack));
    node->data=data;
    node->next=S->next;
    S->next=node;
    S->data++;
}

int isEmpty(Stack *S)
{
    if(S->next==NULL)
    {
        return 1;
    }
    return 0;
}

int Pop(Stack *S)
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

int *findIndeGress(Graph *G)
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
            if(G->arcs[i][j]>0&&G->arcs[i][j]!=MAX)
            {
                find[j]++;
            }
        }
    }
    return find;
}

int * topologicalSort(Graph *G)
{
    int *find=findIndeGress(G);
    int index=0;
    int *top=(int *)malloc(sizeof(int)*G->vexNum);
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
        int vex=Pop(S);
        top[index++]=vex;
        for(int i=0;i<G->vexNum;i++)
        {
            if(G->arcs[vex][i]>0 && G->arcs[vex][i]!=MAX)//判断哪一个是该结点其实出发的边
            {
                find[i]--;
                if(find[i]==0)
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
    printf("\n");
    return top;
}

Graph *initGraph(int vexnum)
{
    Graph *G=(Graph *)malloc(sizeof(Graph));
    G->vexs=(char *)malloc(sizeof(char)*vexnum);
    G->arcs=(int **)malloc(sizeof(int*)*vexnum);
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
            if(G->arcs[i][j]!=0&&G->arcs[i][j]!=MAX)
            {
                G->arcNum++;
            }
        }
    }
}

void DFS(Graph *G,int *visit,int index)
{
    printf("%c\t",G->vexs[index]);
    visit[index]=1;
    for(int i=0;i<G->vexNum;i++)
    {
        if(G->arcs[index][i]>0 && !visit[i] &&G->arcs[index][i]!=MAX)
        {
            DFS(G,visit,i);
        }
    }
}

int getindex(int *top,Graph *G,int i)
{
    int j;
    for(j=0;j<G->vexNum;j++)
    {
        if(top[j]==i)
        {
            break;
        }
    }
    return j;
}

void criticalPath(Graph *G)
{
    int *top=topologicalSort(G);
    //维护两个数组存储最早开始时间与最晚开始时间
    int *early=(int *)malloc(sizeof(int)*G->vexNum);
    int *late=(int *)malloc(sizeof(int)*G->vexNum);
    //初始化两个数组
    for(int i=0;i<G->vexNum;i++)
    {
        early[i]=0;
        late[i]=0;
    }
    for(int i=0;i<G->vexNum;i++)//对pop中的每一个计算最早的发生时间
    {
        int max=0;
        for(int j=0;j<G->vexNum;j++)//从面推后面的，遍历每一条边，计算最大值
        {               
            if(G->arcs[j][top[i]]> 0 && G->arcs[j][top[i]]!=MAX)//要知道那些顶点可以到顶点index,所以是相反的,因为最早发生时间是要求最大值的
            {
                int index=getindex(top,G,j);
                if(early[index]+G->arcs[j][top[i]]>max)//仍然是top【i】
                {
                    max=early[index]+G->arcs[j][top[i]];
                }
            }
        }
        early[i]=max;
    }
    for(int i=0;i<G->vexNum;i++)
    {
        printf("%d\t",early[i]);
    }
    printf("\n");
    late[G->vexNum-1]=early[G->vexNum-1];
    //计算最晚发生时间，最晚要从倒数第一个结点开始计算
    for(int i=G->vexNum-2;i>=0;i--)
    {
        int min=MAX;
        for(int j=0;j<G->vexNum;j++)
        {
            if(G->arcs[top[i]][j]>0&&G->arcs[top[i]][j]!=MAX)//从倒数第二个开始，所以他的值需要判断到他的顶点的最小值
            {
                int index=getindex(top,G,j);
                if(late[index]-G->arcs[top[i]][j]<min)
                {
                    min=late[index]-G->arcs[top[i]][j];
                }
            }
        }
        late[i]=min;
    }
    for(int i=0;i<G->vexNum;i++)
    {
        printf("%d\t",late[i]);
    }
    printf("\n");
    for(int i=0;i<G->vexNum;i++)
    {
        for(int j=0;j<G->vexNum;j++)
        {
            if(G->arcs[i][j]>0 &&G->arcs[i][j]!=MAX)
            {
                int start=getindex(top,G,i);
                int end=getindex(top,G,j);
                if(late[end]-G->arcs[i][j]-early[start]==0)
                {
                    printf("start=%d end=%d\n",i,j);
                }
            }
        }
    }
}

int main()
{
    Graph *G=initGraph(9);
    int *visit=(int *)malloc(sizeof(int)*G->vexNum);
    for(int i=0;i<G->vexNum;i++)
    {
        visit[i]=0;
    }
    int arcs[9][9]={
        {0,6,4,5,MAX,MAX,MAX,MAX,MAX},
        {MAX,0,MAX,MAX,1,MAX,MAX,MAX,MAX},
        {MAX,MAX,0,MAX,1,MAX,MAX,MAX,MAX},
        {MAX,MAX,MAX,0,MAX,2,MAX,MAX,MAX},
        {MAX,MAX,MAX,MAX,0,MAX,9,7,MAX},
        {MAX,MAX,MAX,MAX,MAX,0,MAX,4,MAX},
        {MAX,MAX,MAX,MAX,MAX,MAX,0,MAX,2},
        {MAX,MAX,MAX,MAX,MAX,MAX,MAX,0,4},
        {MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,0}
    };
    creatGraph(G,"012345678",(int *)arcs);
    DFS(G,visit,0);
    printf("\n");
    criticalPath(G);
    printf("\n");
    return 0;
}