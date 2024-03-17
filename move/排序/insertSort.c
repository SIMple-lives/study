#include <stdio.h>
#include <stdlib.h>

void insertSort(int arr[] ,int length)
{
    // 外层循环，从第二个元素开始 ，比较0-他们前一个元素之间有没有合适的位置插入
    for(int i=1;i<length;i++)
    {
        for(int j=0;j<i;j++)//在前面寻找比该元素大的值，寻找插入位置
        {
            if(arr[i]<arr[j])
            {
                int temp=arr[i];
                for(int k=i-1;k>=j;k--)
                {
                    arr[k+1]=arr[k];
                }
                arr[j]= temp; 
            }
        }
        printarr(arr,6);
    }
}

void shellSort(int arr[],int length,int step)
{
    for(int i=0;i<length;i++)
    {
        for(int j=i+step;j<length;j+=step)
        {
            for(int k=i;k<j;k+=step)
            {
                if(arr[k]>arr[j])
                {
                    int temp=arr[j];
                    for(int l=j-step;l>=k;l-=step)
                    {
                        arr[l+step]=arr[l];
                    }
                    arr[k]=temp;
                }
            }
        }
    }
}

void printarr(int arr[],int length)
{
    for(int i=0;i<length;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[10]={49,38,65,97,76,13,27,49,55,4};
    int steps[3]={5,3,1};
    for(int i=0;i<3;i++)
    {
        shellSort(arr,10,steps[i]);
    }
    printarr(arr,10);
    return 0;
}