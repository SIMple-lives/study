#include <iostream>
using namespace std;
#include <deque>
#include <algorithm>
#include <vector>

//排序
template<typename T>
void print(const T &d)
{
    for(typename T::const_iterator i = d.begin(); i != d.end();i++)
    {
        cout << *i << " ";
    }
    cout << endl;
}

void test()
{
    deque<int> d;
    d.push_back(6);
    d.push_back(4);
    d.push_back(3);
    d.push_back(1);
    d.push_back(5);
    d.push_back(2);
    print(d);
    sort(d.begin(), d.end());
    print(d);
    vector<int> v;
    for(int i =0;i<6;i++)
    {
        v.push_back(i);
    }
    print(v);
}

int main()
{
    test();
    return 0;
}

//插入和删除
// void print(const deque<int> &d)
// {
//     for(deque<int>::const_iterator i = d.begin(); i != d.end(); i++) 
//     {
//         cout << *i << " ";
//     }
//     cout << endl;
// }

// void test01()
// {
//     deque<int> d1;
//     d1.push_back(30);
//     d1.push_back(40);
//     d1.push_back(50);
//     d1.push_front(20);
//     d1.push_front(10);
//     print(d1);
//     // d1.pop_back();
//     // d1.pop_front();
//     // print(d1);
//     // insert插入
//     d1.insert(d1.begin(),1);
//     print(d1);
//     d1.insert(d1.begin(),2,0);
//     print(d1);
//     //按照区间进行插入
//     deque<int>d2;
//     d2.push_back(1);
//     d2.push_back(2);
//     d2.push_back(3);
//     d1.insert(d1.begin(),d2.begin(),d2.end());
//     print(d1);
//     d1.erase(d1.begin());
//     print(d1);
//     d1.erase(d1.begin(),d1.end());
//     print(d1);
// }

// int main()
// {
//     test01();
//     return 0;
// }

//大小操作
// void print(const deque<int> &d)
// {
//     for(deque<int>::const_iterator i = d.begin(); i != d.end();i++)
//     {
//         cout << *i << " ";
//     }
//     cout << endl;
// }

// void test()
// {
//     deque<int> d;
//     for(int i=6;i<11;i++)
//     {
//         d.push_back(i);
//     }
//     for(int i=5;i>0;i--)
//     {
//         d.push_front(i);
//     }
//     print(d);
//     if(d.empty())
//     {
//         cout << "d is empty" << endl;
//     }
//     else
//     {
//         cout << d.size() << endl;
//     }
//     d.resize(6);
//     print(d);
//     cout << d.size() << endl;
//     d.resize(12);
//     print(d);
//     cout << d.size() << endl;
//     d.resize(15,4);
//     print(d);
//     cout << d.size() << endl;
//     d.clear();
//     if(d.empty())
//     {
//         cout << "d is empty" << endl;
//     }
//     else
//     {
//         cout << d.size() << endl;
//     }
// }

// int main()
// {
//     test();
//     return 0;
// }

//deque的构造函数
// void print(const deque<int> &d)
// {
//     for(deque<int>::const_iterator i = d.begin(); i != d.end();i++)
//     {
//         cout << *i << " ";
//     }
//     cout << endl;
// }

// void test()
// {
//     deque<int> d1;
//     for(int i =0;i<10;i++)
//     {
//         d1.push_back(i);
//     }
//     print(d1);
//     deque<int>d2(d1.begin(),d1.end());
//     print(d2);
//     deque<int>d3(10,100);
//     deque<int>d4(d3);
//     print(d4);
//     print(d3);
// }

// int main()
// {
//     test();
//     return 0;
// }