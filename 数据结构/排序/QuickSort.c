#include <stdio.h>
#include <stdlib.h>

void printarr(int arr[],int length)
{
    for(int i=0;i<length;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int partition(int arr[],int i,int j)
{
    int x=arr[i];
    while(i<j)
    {
        while(i<j && arr[j]>=x)
        {
            j--;
        }
        if(i<j)
        {
            arr[i]=arr[j];
            i++;
        }
        while(i<j&&arr[i]<x)
        {
            i++;
        }
        if(i<j)
        {
            arr[j]=arr[i];
            j--;
        }
    }
    arr[i]=x;
    return i;
}

void QuickSort(int arr[],int i,int j )
{
    if(i<j)
    {
        int index=partition(arr,i,j);
        QuickSort(arr,i,index-1);
        QuickSort(arr,index+1,j);
    } 
}

int main()
{
    int arr [8]={27,38,13,49,76,97,65,49};
    QuickSort(arr,0,7);
    printarr(arr,8);
    return 0;
}