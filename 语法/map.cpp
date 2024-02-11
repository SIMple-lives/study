#include <iostream>
using namespace std;
#include <map>
#include <functional>

void test()
{
    negate<int> n;
    cout << n(40) << endl;
    plus<int> p;
    cout << p(40,n(39)) << endl;
}

int main()
{
    test();
    return 0;
}

// void print(const map<int,int> &m)
// {
//     for(map<int,int>::const_iterator i = m.begin(); i != m.end();i++)
//     {
//         cout << i->first << " " << i->second << endl;
//     }
// }

// //排序
// class MyCompare
// {
// public:
//     bool operator()(int a,int b) const
//     {
//         return a>b;
//     }

// };

// void test()
// {
//     map<int,int,MyCompare> m;
//     m.insert(pair<int,int>(1,10));
//     m.insert(pair<int,int>(2,20));
//     m.insert(pair<int,int>(3,30));
//     m.insert(pair<int,int>(4,40));
//     m.insert(pair<int,int>(5,50));
//     for(map<int,int,MyCompare>::const_iterator i = m.begin(); i != m.end();i++)
//     {
//         cout << i->first << " " << i->second << endl;
//     }
// }

// int main()
// {
//     test();
//     return 0;
// }

//查找和删除
// void test()//都是针对key值的
// {
//     map<int ,int> m;
//     m.insert(make_pair(1,10));
//     m.insert(make_pair(2,20));
//     m.insert(make_pair(3,30));
//     map<int ,int>::iterator it=m.find(2);
//     if(it!=m.end())
//     {
//         cout << it->first << " " << it->second << endl;
//         cout << m.count(3) << endl;
//     }
//     else
//     {
//         cout << "Invalid" << endl ;
//     }
// }

// int main()
// {
//     test();
//     return 0;
// }

//插入和删除
// void test()
// {
//     map<int,int> m;
//     //first
//     m.insert(pair<int,int>(1,10));
//     //second
//     m.insert(make_pair(2,20));
//     //third
//     m.insert(map<int,int>::value_type(3,30));
//     //fourth
//     m[4]=40;//如果没有该键值的元素，会创建一个对应实值为0的元素
//     print(m);
//     //删除
//     m.erase(m.begin());
//     print(m);
//     m.erase(3);
//     print(m);
//     m.clear();
//     print(m);
// }

// int main()
// {
//     test();
//     return 0;
// }

//大小和交换
// void test()
// {
//     map<int,int> m;
//     m.insert(pair<int,int>(1,10));
//     m.insert(pair<int,int>(4,40));
//     m.insert(pair<int,int>(2,20));
//     m.insert(pair<int,int>(3,30));
//     if(m.empty())
//     {
//         cout << "Empty map" << endl;
//     }
//     else
//     {
//         cout << m.size() << endl;
//     }
//     map<int,int> m1;
//     m1.insert(pair<int,int>(1,1));
//     m1.insert(pair<int,int>(4,4));
//     m1.insert(pair<int,int>(2,2));
//     m1.insert(pair<int,int>(3,3));
//     m1.swap(m);
//     print(m);
// }

// int main()
// {
//     test();
//     return 0;
// }

//构造和赋值
// void test()
// {
//     map<int,int> m;
//     m.insert(pair<int,int>(1,10));
//     m.insert(pair<int,int>(2,20));
//     m.insert(pair<int,int>(3,30));
//     m.insert(pair<int,int>(4,40));
//     print(m);
//     map<int,int > m1 (m);
//     print(m1);
//     map<int,int > m3;
//     m3= m1;
//     print(m3);
// }

// int main()
// {
//     test();
//     return 0;
// }