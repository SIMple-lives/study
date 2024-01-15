#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String
{
    char *data;
    int len
}String;

String * initString()
{
    String * s =(String *)malloc(sizeof(String));
    s->data=NULL;
    s->len=0;
    return s;
}

void StringAssign(String *s ,char *data)
{
    if(s->data!=NULL)
    {
        free(s->data);
        s->len=0;
    }
    int len=strlen(data);
    if(len==0)
    {
        s->data=NULL;
        s->len=0;
    }
    else
    {
        s->data=(char *)malloc(sizeof(char)*(len+1));
        s->len+=len;
        for(int i=0;i<len;i++,data++)
        {
            s->data[i]=*data;
        }
    }
}

int *getNext(String *s)
{
    int *next=(int *)malloc(sizeof(int)*s->len);
    int i=0;
    int j=-1;
    next[i]=j;
    while(i<s->len-1)
    {
        if(j==-1 || s->data[i]==s->data[j])
        {
            i++;
            j++;
            next[i]=j;
        }
        else//如果相等，则加一进行赋值，如果不相等则回溯j的值为上一个.
        {
            j=next[j];
        }
    }
    return next; 
}

void kmpmatch(String *s,String *t,int  * next)
{
    int i=0;
    int j=0;
    while(i<s->len && j<t->len)
    {
        if( j==-1 ||s->data[i]==t->data[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }
    }
    if(j==t->len)
    {
        printf("\033[42;32m Success \n\033[0m");
    }
    else
    {
        printf("\033[42;32m Error \n\033[0m");
    }
}

void printString(String *s)
{
    for(int i=0;i<s->len;i++)
    {
        printf(i==0?"%c":"->%c ",s->data[i]);
    }
    printf("\n");
}

int main()
{
    String *s=initString();
    StringAssign(s,"helloworld");
    printString(s);
    String *t=initString();
    StringAssign(t,"heloworld");
    printString(t);
    int *next=getNext(t);
    kmpmatch(s,t,next);
    return 0;
}