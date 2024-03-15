#include <iostream>
using namespace std;
#include <cstring>
#include <pthread.h>
#include <cstdlib>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;


static void *func(void *p)
{
    pthread_mutex_lock(&mut_num);
    while(1)
    {
        while(num==0)
        {
            pthread_mutex_unlock(&mut_num);
            sched_yield();
            pthread_mutex_lock(&mut_num);
        }
        if(num==-1)
        {
            pthread_mutex_unlock(&mut_num);
            break; 
        }
        int i=num;
        num=0; 
        pthread_mutex_unlock(&mut_num);
        int mark=1;
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
            cout<< i << " is a primer" << endl;
            //cout << (int)p << endl;
        }
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid[THRNUM];
    int err;
    for(int i = 0;i<THRNUM;i++)
    {
        err=pthread_create(tid+i,NULL,func,(void*) i);
        if(err)
        {
            fprintf(stderr,"pthread_create()%s\n",strerror(err));
            exit(1);
        }
    }
    //下发任务
    for(int i=LEFT;i<=RIGHT;i++)
    {
        pthread_mutex_lock(&mut_num);
        while(num!=0)
        {
            pthread_mutex_unlock(&mut_num);
            sched_yield();//类似于极短的sleep.确保自己不会抢到该锁
            pthread_mutex_lock(&mut_num);
        }
        num=i;
        pthread_mutex_unlock(&mut_num);
    }
    pthread_mutex_lock(&mut_num);
    while(num!=0)
    {
        pthread_mutex_unlock(&mut_num);
        sched_yield();
        pthread_mutex_lock(&mut_num);
    }
    num=-1;
    for(int i = 0;i<THRNUM;i++)
    {
        pthread_join(tid[i],NULL);
       
    }
    pthread_mutex_destroy(&mut_num);
    return 0;
} 