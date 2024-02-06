#include <iostream>
using namespace std;
#include <string>

//类模板中成员函数的创建时机
//类模板中成员函数和普通类中成员函数创建时间是有区别的

//普通类中的成员函数一开始就可以创建


template <typename T>
class myClass
{
public:
    T obj;
    //类模板中的成员函数
    void func1()
    {
        obj.showPerson1();
    }
    void func2()
    {
        obj.showPerson2();
    }
};

class Person2
{
public:
    void showPerson2()
    {
        cout << "Person2" << endl;
    }
};

class Person1
{
public:
    void showPerson1()
    {
        cout << "Person1" << endl;
    }
};

void test()
{
    myClass <Person2>p;
    //p.func1();
    p.func2();
}


int main()
{
    test();
    return 0;
}

// 类模板中的成员函数在调用时才创建
//这段代码是可以编译成功的，因为类模板中的成员函数是在调用时才开始创建的，所以是不会发生错误的
// template <typename T>
// class myClass
// {
// public:
//     T obj;
//     //类模板中的成员函数
//     void func1()
//     {
//         obj.showPerson1();
//     }
//     void func2()
//     {
//         obj.showPerson2();
//     }
// };

// class Person12
// {
// public:
//     void showPerson2()
//     {
//         cout << "Person2" << endl;
//     }
// };

// class Person1
// {
// public:
//     void showPerson1()
//     {
//         cout << "Person1" << endl;
//     }
// };


// template <typename T>
// void swap();

// //类模板与函数模板的区别
// //类模板没有自动类型推导的用法
// template <class T1,class T2=int>//模板参数列表
// class Person
// {
// public:
//     Person(T1 name ,T2 age)
//     {
//         this->m_Name=name;
//         this->m_Age=age;
//     }
//     void show()
//     {
//         cout << this->m_Name << endl;
//         cout << this->m_Age << endl;
//     }
//     T1 m_Name;
//     T2 m_Age;
// };

// //类模板在模板列表中可以有默认参数
// void test01()
// {
//     Person<string >p1("Tom",17);
//     p1.show();
// }

// void test()
// {
//     //Person p("John",18);,无类型推导的用法 
//     Person<string ,int > p("John",18);
//     p.show();
// }

// int main()
// {
//     test();
//     test01();
//     return 0;
// }