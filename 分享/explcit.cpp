#include <iostream>
using namespace std;

class P
{
public:
    P()
    {
        cout << "默认构造函数" << endl;
    }
    P(int a)
    {
        m_A = a;
    }
    explicit P(P& a)
    {
        m_A = a.m_A;
    }
    int m_A;
};

int main()
{
    P p;
    p.m_A = 1;
    P p1=P(1);
    cout << p1.m_A << endl;
    return 0;
}

