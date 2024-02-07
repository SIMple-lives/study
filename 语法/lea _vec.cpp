#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>



//容器嵌套容器
// void test()
// {
//     vector<vector <int>>v;
//     vector<int> v1;
//     vector<int> v2;
//     vector<int> v3;
//     vector<int> v4; 
//     //向小容器内添加数据
//     for(int i=0;i<4;i++)
//     {
//         v1.push_back(i+1);
//         v2.push_back(i+5);
//         v3.push_back(i+9);
//         v4.push_back(i+13);
//     }
//     //将小容器加到大容器中
//     v.push_back(v1);
//     v.push_back(v2);
//     v.push_back(v3);
//     v.push_back(v4);
//     //通过大容器，遍历所有的数据
//     for(vector<vector<int>> :: iterator it=v.begin();it!=v.end();it++)
//     {
//         for(vector<int>::iterator is=(*it).begin();is!=(*it).end();is++)
//         {
//             cout << *is << "   "; 
//         }
//         cout << endl;
//     }
// }

// int main()
// {
//     test();
//     return 0;
// }

// //vector存放自定义数据类型
// class Person
// {
// public:
//     Person(string name,int age)
//     {
//         this->m_Name = name;
//         this->m_Age = age;
//     }
//     string m_Name;
//     int m_Age;
// };

// void test()
// {
//     vector<Person> v;
//     Person p1("John",10);
//     Person p2("Tom",11);
//     Person p3("Bob",12);
//     Person p4("herry",13);
//     Person p5("Alice",14);
//     v.push_back(p1);
//     v.push_back(p2);
//     v.push_back(p3);
//     v.push_back(p4);
//     v.push_back(p5);
//     for(vector<Person>::iterator it =v.begin(); it !=v.end();it++)
//     {
//         // cout << (*it).m_Name << " " << (*it).m_Age << endl;
//         cout << it->m_Name << " " << it->m_Age << endl;
//     }
// }

// void test01()
// {
//     vector<Person *> v;
//     Person p1("John",10);
//     Person p2("Tom",11);
//     Person p3("Bob",12);
//     Person p4("herry",13);
//     Person p5("Alice",14);
//     v.push_back(&p1);
//     v.push_back(&p2);
//     v.push_back(&p3);
//     v.push_back(&p4);
//     v.push_back(&p5);
//     for(vector<Person *>::iterator it =v.begin(); it !=v.end();it++)
//     {
//         // cout << (*it).m_Name << " " << (*it).m_Age << endl;
//         cout << (*(*it)).m_Name << "     " << (*(*it)).m_Age << endl;
//     }
// }

// int main()
// {
//     test01();
//     return 0;
// }

//vector容器存放内置数据类型

// void myPrint(int val)
// {
//     cout << val << endl;
// }

// void test()
// {
//     //创建l一个vector的容器，      数组
//     vector<int> v;
//     //向容器中插入数据
//     v.push_back(10);
//     v.push_back(20);
//     v.push_back(30);
//     v.push_back(40);
//     //通过迭代器访问容器中的数据
//     // vector<int>::iterator itBegin =v.begin();//起始迭代器  指向容器中的第一个元素
//     // vector<int>::iterator itEnd =v.end(); //结束迭代器 指向容器中最后一个位置的下一个位置
//     // //第一种遍历方式
//     // while(itBegin!=itEnd)
//     // {
//     //     cout << *itBegin << endl;
//     //     itBegin++;
//     // }
//     //第二种
//     // for(vector<int>::iterator it=v.begin();it!=v.end();it++)
//     // {
//     //     cout << *it << endl;
//     // }
//     //第三种 利用STL中提供的遍历算法
//     for_each(v.begin(),v.end(),myPrint);;
// }

// int main()
// {
//     test();
//     return 0;
// }