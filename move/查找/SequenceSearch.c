#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int *data;
    int length;
    int num;
}List;

List *initList(int length)
{
    List *list=(List *)malloc(sizeof(List));
    list->length=length;
    list->num=0;
    list->data=(int *)malloc(sizeof(int)*length);
    return list;
}

void listAdd(List *list,int data)
{
    list->data[list->num]=data;
    list->num++;
}

int search(List *list,int key)
{
    for(int i=0;i<list->num;i++)
    {
        if(list->data[i]==key)
        {
            return i;
        }
    }
    return -1;
}

void printlist(List *list)
{
    for(int i=0;i<list->num;i++)
    {
        printf("%d\t",list->data[i]);
    }
    printf("\n");
}

int main()
{
    List *list=initList(5);
    listAdd(list,1);
    listAdd(list,2);
    listAdd(list,3);
    listAdd(list,4);
    printlist(list);
    printf("%d\n",search(list,5));
    printf("%d\n",search(list,2));
    return 0;
}