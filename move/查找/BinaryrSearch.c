#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int *data;
    int length;
    int num;
}List;

List *initlist(int lenght)
{
    List *list=(List *)malloc(sizeof(List));
    list->data=(int *)malloc(sizeof(int )*lenght);
    list->length=lenght;
    list->num=0;
    return list;
}

void listADD(List *list,int data)
{
    list->data[list->num]=data;
    list->num++;
}

void printList(List *list)
{
    for(int i=0;i<list->num;i++)
    {
        printf("%d\t",list->data[i]);
    }
    printf("\n");
}

int binarysearch(int key,List *list)
{
    int start=0;
    int end=list->num-1;
    int mid;
    while(start<=end)
    {
        mid=(start+end)/2;
        if(key>list->data[mid])
        {
            start=mid+1;
        }
        else if(key<list->data[mid])
        {
            end=mid-1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

int binarysearchRecursionn(int key,List *list,int start,int end)
{
    if(start==end)
    {
        if(list->data[start]==key)
        {
            return start;
        }
        return -1;
    }
    int mid=(start+end)/2;
    if(list->data[mid]<key)
    {
        return binarysearchRecursionn(key,list,mid+1,end);
    }
    else if(list->data[mid]>key)
    {
        return binarysearchRecursionn(key,list,start,mid-1);
    }
    else
    {
        return mid;
    }
}

int main()
{
    List *list=initlist(9);
    listADD(list,1);
    listADD(list,2);
    listADD(list,3);
    listADD(list,4);
    listADD(list,5);
    listADD(list,6);
    listADD(list,7);
    listADD(list,8);
    listADD(list,9);
    printList(list);
    printf("%d\n", binarysearch (3,list));
    printf("%d\n", binarysearchRecursionn (3,list,0,list->num-1));
    return 0;
}