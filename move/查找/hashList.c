#include <stdio.h>
#include <stdlib.h>

#define NUM 5

typedef struct HashList
{
    int num;
    char *data;
}HashList;

HashList *initHashList()
{
    HashList *list=(HashList *)malloc(sizeof(HashList));
    list->num=0;
    list->data=(char *)malloc(sizeof(char)*NUM);
    for(int i=0;i<NUM;i++)
    {
        list->data[i]=0;
    }
    return list;
}

int hash(int  data)
{
    return data % NUM;
}

void put(HashList *list,char data)
{
    int index=hash(data);
    if(list->data[index]!=0)
    {
        int count=1;
        while(list->data[index]!=0)//不等于0
        {
            index=hash((hash(data)+count));
            count++; 
        }
    }
    list->data[index]=data;
    list->num++;
}

int main()
{
    HashList *list=initHashList();
    put(list,'A');
    put(list,'F');
    printf("%c\n",list->data[0]);
    printf("%c\n",list->data[1]);
    return 0;
}