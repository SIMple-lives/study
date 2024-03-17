#include <iostream>
#include <future>
#include <thread>

int add(int a ,int b)
{
    return a+b;
}

bool isPrimer(int k)
{
    if(k<=1)
    {
        return false;
    }
    for(int i=2;i<=k/2;i++)
    {
        if(k%i==0)
        {
            return false;
        }
    }
    return true;
}

int main()
{   
    std::packaged_task <int(int,int)> task(add);
    std::future<int> fut=task.get_future();
    std::thread t(std::move(task),2,3);
    std::cout << fut.get() << std::endl;
    std::packaged_task <bool(int)> task1(isPrimer);
    std::future<bool> func=task1.get_future();
    std::thread tt(std::move(task1),7);
    std::cout << func.get() << std::endl;
    tt.join();
    t.join();
    return 0;
}