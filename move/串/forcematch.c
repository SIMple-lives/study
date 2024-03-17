#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String
{
    char *data;
    int len;
}String;

String * initString()
{
    String * s=(String *)malloc(sizeof(String));
    s->len=0;
    s->data=NULL;
    return s;
}

void StringAssign(String *s,char *data)
{
    if(s->data!=NULL)
    {
        free(s->data);
    }
    int len=strlen(data);
    if(len==0)
    {
        s->data=NULL;
        s->len=0;
    }
    else
    {
        s->len=len;
        s->data=(char *)malloc(len+1);
        //for(int i=0;i<len;i++,temp++)挨个赋值.
        strcpy(s->data,data);
    }
}

void forcematch(String *s,String *sub)
{
   /*  int i=0;
    int j=0;
    while(i<s->len && j<sub->len)
    {
        if(s->data[i]==sub->data[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j==sub->len)
    {
        printf("\033[42;31m Success \n\033[0m");
    }
    else
    {
        printf("\033[42;31m Error \n\033[0m");
    } */
    char *end=strstr(s->data,sub->data);
    if(end==NULL)
    {
        printf("\033[42;31m Error \n\033[0m");
    }
    else
    {
        printf("\033[42;31m Success \n\033[0m");
    }
}

void printString(String *s)
{
    printf("%s\n",s->data);
    /* for(int i=0;i<s->len;i++)
    {
        printf(i==0 ?"%c":"-> %c",s->data[i]);
    }
    printf("\n"); */
}

int main()
{
    String *s=initString();
    StringAssign(s,"helloworld");
    printString(s);
    String *t=initString();
    StringAssign(t,"helloorld");
    printString(t);
    forcematch(s,t);
    return 0;
}