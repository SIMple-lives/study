#include <iostream>
using namespace std;
#include <list>
#include <algorithm>

void print(const list<int> &l)
{
    for(list<int>::const_iterator i = l.begin(); i != l.end();i++)
    {
        cout << *i << " ";
    }
    cout << endl;
}

//翻转和排序
bool mycompare(int a,int b)
{
    return a>b;
}

void test()
{
    list<int> l;
    l.push_back(2);
    l.push_back(5);
    l.push_back(3);
    l.push_back(1);
    l.push_back(6);
    l.push_back(4);
    print(l);
    l.reverse();
    print(l);
    //所有不支持随机访问迭代器的容器，不可以用标准的算法
    //不支持随机访问迭代器的容器，内部会提供一些对应的算法
    // sort(l.begin(), l.end());
    // print(l);
    l.sort();
    print(l);
    l.sort(mycompare);
    print(l);
}

int main()
{
    test();
    return 0;
}

//插入和删除
// void test()
// {
//     list<int> l;
//     l.push_back(10);
//     l.push_back(20);
//     l.push_back(30);
//     l.push_front(100);
//     l.push_front(200);
//     l.push_front(300);
//     print(l);
//     l.pop_back();
//     print(l);
//     l.pop_front();
//     print(l);
//     l.insert(l.begin(),1000);
//     print(l);
//     l.insert((l.end()),100000);
//     print(l);
//     l.erase(--l.end());
//     print(l);
//     l.push_back(10);
//     l.push_back(10);
//     print(l);
//     l.remove(10);
//     print(l);
//     l.clear();
//     print(l);
// }

// int main()
// {
//     test();
//     return 0;
// }

//大小操作
// void test()
// {
//     list<int> l1;
//     l1.push_back(10);
//     l1.push_back(20);
//     l1.push_back(30);
//     l1.push_back(40);
//     print(l1);
//     if(l1.empty())
//     {
//         cout << "Empty list" << endl;
//     }
//     else
//     {
//         cout << "不为空 " << endl;
//         cout << l1.size() << endl;
//     }
//     l1.resize(10,1);
//     print(l1);
//     l1.resize(2);
//     print(l1);
// }

// int main()
// {
//     test();
//     return 0;
// }

//赋值操作
// void test()
// {
//     list<int> l1;
//     l1.push_back(10);
//     l1.push_back(20);
//     l1.push_back(30);
//     l1.push_back(40);
//     print(l1);
//     list<int> l2;
//     l2=l1;
//     print(l2);
//     list<int> l3;
//     l3.assign(l2.begin(),l2.end());
//     print(l3);
//     list<int> l4;
//     l4.assign(2,4);
//     print(l4);
// }

// int main()
// {
//     test();
//     return 0;
// }

//构造函数
// void test()
// {
//     list<int>l1;
//     l1.push_back(10);
//     l1.push_back(20);
//     l1.push_back(30);
//     l1.push_back(40);
//     print(l1);
//     list<int>l2(l1.begin(),l1.end());
//     print(l2);
//     list<int>l3(4,3);
//     list<int>l4(l3);
//     print(l4);
//     print(l3);
// }

// int main()
// {
//     test();
//     return 0;
// }