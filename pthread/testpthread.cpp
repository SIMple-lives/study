#include <iostream>
using namespace std;
#include <cstring>
#include <pthread.h>
#include <cstdlib>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT+1)

struct thrst
{
    int n;
};

static void *func(void *num)
{
    //int i=*((int*)num);
    int i=((struct thrst*)num)->n;
    int mark=1;
    //free(num);
    for(int j=2;j<i/2;j++)
    {
        if(i%j==0)
        {
            mark=0;
            break;
        }
    }
    if(mark)
    {
        cout << i << " is a primer" << endl;
    }
    pthread_exit(num);
}

int main()
{
    pthread_t tid[THRNUM];
    int err;
    struct thrst *p;
    void *ptr;
    for(int i = LEFT;i<=RIGHT;i++)
    {
        p=(struct thrst*)malloc(sizeof(struct thrst));
        if(p==NULL)
        {
            perror("malloc");
            exit(1);
        }
        p->n=i;
        err=pthread_create(tid+(i-LEFT),NULL,func,p);
        if(err)
        {
            fprintf(stderr,"pthread_create()%s\n",strerror(err));
            exit(1);
        }
    }
    for(int i = LEFT;i<=RIGHT;i++)
    {
        pthread_join(tid[i-LEFT],&ptr);
        free(ptr);
    }
    return 0;
}