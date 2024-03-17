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
    list->num=1;
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
   int i;
   list->data[0]=key;
   i=list->num-1;
   while(key!=list->data[i])
   {
        i--;
   }
   return i;
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
    listAdd(list,4);
    listAdd(list,5);
    listAdd(list,6);
    listAdd(list,7);
    printlist(list);
    printf("%d\n",search(list,4));
    printf("%d\n",search(list,8));
    return 0;
}