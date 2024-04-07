// #include <iostream>
// #include <vector>
// using namespace std;

// int main()
// {
//     vector<char> ch;
//     for(int i =97;i<102;i++)
//     {
//         ch.push_back(i);
//     }
//     for(auto i:ch)
//     {
//         cout << i << endl;
//     }
//     return 0;
// }

// int main()
// {
//     vector<int> nums;
//     for(int i =0;i<10;i++)
//     {
//         nums.push_back(i);
//     }
//     for(auto &u:nums)
//     {
//         cout << u << endl;
//     }
//     return 0;
// }

// int main()
// {
//     vector<int> v={1,2,3,4,5};
//     for(auto & n :v)
//     {
//         cout << n << endl;
//     }
//     return 0;
// }

#include <iostream>
#include <queue>
#include <functional>
//#include <algorithm>
   
int  main()
{
    std::priority_queue<int> a;
    for(int i = 0; i < 10; i++)
    {
        a.push(i);
    }

    for(int i = 10 ; i > 0; i--)
    {
        a.push(i);
    }
    int size = a.size();
    for(int i =0 ;i<size;i++)
    {
        std::cout << a.top() << std::endl;
        a.pop();
    }
    std::cout << "Hello, World!" << std::endl;
    // auto cmp = [](int a,int b) -> bool {return a > b ;};
    // std::priority_queue< int,std::vector<int> ,decltype(cmp)> v(cmp);
    std::priority_queue<int,std::vector<int>,std::greater<int>> v;
    for(int i = 0; i < 10; i++)
    {
        v.push(i);
    }
    for(int i = 10 ; i > 0; i--)
    {
        v.push(i);
    }
    for(int i =0 ;i<size;i++)
    {
        std::cout << v.top() << std::endl;
        v.pop();
    }
    return 0;
}