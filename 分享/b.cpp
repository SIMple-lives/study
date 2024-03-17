#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "默认构造" << endl;
    }
    A(int a)
    {
        m_A=a;
    }
    A(const A& a)
    {
        m_A=a.m_A;
    }
    A operator+(  A b)
    {
        A temp;
        temp.m_A=b.m_A+this->m_A;
        return temp;
    }
    int m_A;
};

int main()
{
    A a;
    a.m_A = 20;
    A b(10);
    c=b.operator+(a).operator+(a).operator+(a);
    return 0;
}