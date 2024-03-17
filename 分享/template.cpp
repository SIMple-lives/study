#include <iostream>
using namespace std;

template <class T>
class Person
{
public:
    Person(T age)
    {
        m_age = age;
    }
    T m_age;
};

int main()
{
    Person<int> p(1);
    cout <<p.m_age << endl;
    return 0;
}

// template <typename T>
// void func(T&&a,T&&b)
// {
//     cout << a+b << endl;
// }

// int main()
// {
//     int a=10;
//     int b=20;
//     func(a,b);
//     func(200,300);
//     return 0;
// }