#include <iostream>
using namespace std;
#include <string>

// 类模板与友元
// template <class T1,class T2>
// class Person;

// //类外实现
// template <class T1 ,class T2>
// void printPerson2(Person<T1,T2> p)
// {
//     cout << p.m_Name<<endl;
//     cout << p.m_Age<<endl;
// }

// //通过全局函数打印Person的信息
// template <class T1 ,class T2>
// class Person
// {
//     //全局函数类内实现
//     friend void printPerson(Person<T1,T2> p)
//     {
//         cout << p.m_Name<<endl;
//         cout << p.m_Age<<endl;
//     }
//     //全局函数类外实现
//     //加空模板的参数列表
//     friend void printPerson2<>(Person<T1,T2> p);
// public:
//     Person(T1 name ,T2 age)
//     {
//         this->m_Name=name;
//         this->m_Age=age;
//     }
// private:
//     T1 m_Name;
//     T2 m_Age;
// };

// void test()
// {
//     Person <string ,int> p ("Hello",18);
//     printPerson(p);
// }

// void test01()
// {
//     Person <string ,int>   p("ahjsd",19);
//     printPerson2(p);
// }

// int main()
// {
//     test01();
//     return 0;
// }

//类模板成员函数在类外实现
// template <class T1,class T2>
// class Person
// {
// public:
//     Person(T1 name ,T2 age);
//     // {
//     //     this->m_Age=age;
//     //     this->m_Name=name;
//     // }
//     void showName();
//     // {
//     //     cout << this->m_Age << endl;
//     //     cout << this->m_Name << endl;
//     // }
//     T1 m_Name;
//     T2 m_Age;
// };

// template <class T1,class T2> 
// Person<T1,T2> :: Person(T1 name ,T2 age)
// {
//     this->m_Age=age;
//     this->m_Name=name;
// }

// template <class T1,class T2>
// void Person<T1,T2> :: showName()
// {
//     cout << this->m_Name << endl;
//     cout << this->m_Age << endl;
// }

// void test()
// {
//     Person<string,int>p("John",18);
//     p.showName();
// }

// int main()
// {
//     test();
//     return 0;
// }

//类模板与继承
// template <class T>
// class Base
// {
// public:
//     T m;
// };

// //class Son : public Base //错误的，必须要知道父类中T的数据类型，才能继承给子类
// class Son : public Base <int>
// {

// };

// //想灵活指定类模板中的类型，子类也需要变为模板

// template <class T1,class T2>
// class Son1 : public Base<T2>
// {
// public:
//     Son1()
//     {
//         cout << typeid(T1).name() << endl;
//         cout << typeid(T1).name() << endl;
//         cout << typeid(T2).name() << endl;
//     }
//     T1 obj;
// };

// void test()
// {
//     Son s1;
// }

// void test01()
// {
//     Son1 <int ,char> s;

// }

// int main()
// {
//     //test();
//     test01();
//     return 0;
// }