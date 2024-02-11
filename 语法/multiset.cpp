#include <iostream>
using namespace std;
#include <set>
#include <string>

template <typename T>
void print(const T &s)
{
    for(typename T::const_iterator i = s.begin(); i != s.end();i++)
    {
        cout << *i << " ";
    }
    cout << endl;
}

//set的排序
class MyCompare
{
public:
    bool operator()(int v1, int v2) const
    {
        return v1 > v2;
    }
};

void test()
{
    set<int> s1;
    s1.insert(40);
    s1.insert(10);
    s1.insert(30);
    s1.insert(50);
    s1.insert(20);
    print(s1);
    set <int,MyCompare>s2;
    s2.insert(40);
    s2.insert(10);
    s2.insert(30);
    s2.insert(50);
    s2.insert(20);
    for(set<int,MyCompare>::iterator i = s2.begin(); i != s2.end();i++)
    {
        cout << *i << " ";
    }
    cout << endl;
}

class Person
{
public:
    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    string m_Name;
    int m_Age;
};

class mycompare
{
public:
    bool operator()(const Person &a,const Person &b)const
    {
        return a.m_Age > b.m_Age;
    }
};

void test01()
{
    //自定义数据类型  都会指定排序规则
    set <Person,mycompare> s;
    Person p1("John",23);
    Person p2("Alice",19);
    Person p3("Bob",25);
    Person p4("Tom",17);
    s.insert(p1);
    s.insert(p2);
    s.insert(p3);
    s.insert(p4);
    for(set<Person,mycompare>::iterator it =s.begin();it!=s.end();it++)
    {
        cout << it->m_Name << "  " << it->m_Age << endl;
    }
    cout << endl;
}

int main()
{
    test01();
    return 0;
}

//对组的创建
// void test()
// {
//     pair<string,int> p("hello",20);
//     cout<<p.first<<endl;
//     cout<< p.second<<endl;
//     pair<string,int> p2 = make_pair("Tom",18);
//     cout << p2.first << " " << p2.second << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//set与multiset的区别
// void test()
// {
//     set<int> s;
//     pair<set<int>::iterator,bool> ret= s.insert(10);
//     if(ret.second)
//     {
//         cout << "Success" << endl;
//     }
//     else
//     {
//         cout << "Error" << endl;
//     }
//     ret=s.insert(10);
//     if(ret.second)
//     {
//         cout << "Success" << endl;
//     }
//     else
//     {
//         cout << "Error" << endl;
//     }
//     multiset<int> ms;
//     ms.insert(10);
//     ms.insert(10);
//     print(ms);
// }

// int main()
// {
//     test();
//     return 0;
// }

//查找和统计
// void test()
// {
//     set<int> s;
//     s.insert(4);
//     s.insert(1);
//     s.insert(2);
//     s.insert(8);
//     s.insert(5);
//     s.insert(9);
//     s.insert(7);
//     s.insert(6);
//     s.insert(3);
//     print(s);
//     int fin;
//     cin>>fin;
//     if(s.find(fin) != s.end())
//     {
//         cout << s.count(fin) << endl;
//     }
//     else
//     {
//         cout << "Error" << endl;
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
//     set<int> s;
//     s.insert(10);
//     s.insert(30);
//     s.insert(40);
//     s.insert(20);
//     print(s);
//     s.erase(s.begin());
//     print(s);
//     s.erase(20);
//     print(s);
// }

// int main()
// {
//     test();
//     return 0;
// }

//大小和交换
// void test()
// {
//     set<int> s;
//     s.insert(40);
//     s.insert(10);
//     s.insert(30);
//     s.insert(20);
//     print(s);
//     if(s.empty())
//     {
//         cout << "Empty" << endl;
//     }
//     else
//     {
//         cout << s.size() << endl;
//     }
//     set<int> s1;
//     s1.insert(1);
//     s1.insert(2);
//     s1.insert(3);
//     s1.insert(4);
//     s1.swap(s);
//     print(s);
// }

// int main()
// {
//     test();
//     return 0;
// }

//构造和赋值
// void test()
// {
//     set<int> s;
//     //插入数据只有insert的方式
//     //set：所有元素插入时自动排序
//     //set不允许插入重复的值
//     s.insert(20);
//     s.insert(10);
//     s.insert(30);
//     s.insert(40);
//     print(s);
//     set<int> s2(s);
//     print(s2);
//     set <int> s3;
//     s3=s2;
//     print(s3);
// }

// int main()
// {
//     test();
//     return 0;
// }