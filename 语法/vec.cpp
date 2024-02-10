#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

//预留空间
void test()
{
    vector<int> v;
    v.reserve(100000);
    int num =0;
    int *p=NULL;
    for(int i=0;i<100000;i++)
    {
        v.push_back(i);
        if(p!=&v[0])
        {
            p=&v[0];
            num++;
        }
    }
    cout << num << endl;
}

int main()
{
    test();
    return 0;
}

//互换容器
//实际用途
// void test()
// {
//     vector<int> v;
//     for(int i = 0; i <100000;i++)
//     {
//         v.push_back(i);
//     }
//     cout << v.size() << endl;
//     cout << v.capacity() << endl;
//     v.resize(3);
//     vector <int>(v).swap(v);
//     cout << v.size() << endl;
//     cout << v.capacity() << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }
// void print(vector<int> &v)
// {
//     for(vector<int>::iterator it =v.begin(); it != v.end();it++)
//     {
//         cout << *it << " ";
//     }
//     cout << endl;
// }

// void test()
// {
//     vector<int> v1;
//     for(int i=0;i<10;i++)
//     {
//         v1.push_back(i);
//     }
//     cout << "交换前 :" << endl;
//     print(v1);
//     vector<int> v2;
//     for(int i=10;i>0;i--)
//     {
//         v2.push_back(i);
//     }
//     print(v2);
//     cout << "交换后 :" << endl;
//     v1.swap(v2);
//     print(v1);
//     print(v2);
// }

// int main()
// {
//     test();
//     return 0;
// }

//数据存取
// void test()
// {
//     vector<int> v1;
//     for(int i=0;i<10;i++)
//     {
//         v1.push_back(i);
//     }
//     for(int i=0;i<v1.size();i++)
//     {
//         cout << v1[i] << " ";
//     }
//     cout << endl;
//     //利用at方式访问成员
//     for(int i=0;i<v1.size();i++)
//     {
//         cout << v1.at(i) << " ";
//     }
//     cout << endl;
//     cout << "第一个元素为 :" << v1.front() << endl;
//     cout << "最后一个元素为:" << v1.back() << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//插入和删除
// void print(vector<int> &v)
// {
//     for(vector<int>::iterator it=v.begin(); it!=v.end();it++)
//     {
//         cout << *it << " ";
//     }
//     cout << endl;
// }

// void test()
// {
//     vector<int> v1;
//     v1.push_back(10);
//     v1.push_back(20);
//     v1.push_back(30);
//     v1.push_back(40);
//     v1.push_back(50);
//     print(v1);
//     //尾部删除
//     v1.pop_back();
//     print(v1);
//     //插入    第一个参数是迭代器
//     v1.insert(v1.begin(),100);
//     print(v1);
//     v1.insert(v1.begin(),2,1000);
//     print(v1);
//     //删除   第一个参数也是迭代器
//     v1.erase(v1.begin());
//     print(v1);
//     // v1.erase(v1.begin(),v1.end());
//     v1.clear();
//     print(v1);
// }

// int main()
// {
//     test();
//     return 0;
// }

//vector容器的容量和大小
// void print(vector<int> &v)
// {
//     for(vector<int>::iterator it= v.begin();it!=v.end();it++)
//     {
//         cout << *it << " ";
//     }
//     cout << endl;
// }

// void test()
// {
//     vector <int> v1;
//     for(int i=0;i<10;i++)
//     {
//         v1.push_back(i);
//     }
//     print(v1);
//     if(v1.empty())//为真，代表容器为空
//     {
//         cout << "V1 empty" << endl;
//     }
//     else
//     {
//         cout << "V1 not empty" << endl;
//         cout << "V1 的容量为: " << v1.capacity() << endl;
//         cout << "V1 的大小为: " << v1.size() << endl;
//     }
//     v1.resize(15,100);//利用重载的版本，可以指定默认的填充值
//     print(v1);//如果重新指定的过长，比原先的长度长，默认用 0 填充新的位置
//     v1.resize(4);
//     print(v1);//如果指定比原来短了，超出部分会删除.
//     cout << "V1 的容量为: " << v1.capacity() << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

// void print(vector<int> &v)
// {
//     for(vector<int>::iterator it=v.begin(); it!=v.end();it++)
//     {
//         cout << *it << " ";
//     }
//     cout << endl;
// }

// //vector构造函数
// void test()
// {
//     vector <int> v1;
//     for(int i=0;i<10;i++)
//     {
//         v1.push_back(i);
//     }
//     print(v1);
//     vector<int> v2(v1.begin(),v1.end());
//     print(v2);
//     vector<int> v3(10,100);
//     print(v3);
//     vector <int> v4(v3);
//     print(v4);   
// }

// int main()
// {
//     test();
//     return 0;
// }