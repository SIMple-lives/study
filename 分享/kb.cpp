#include <iostream>
using namespace std; 

class P
{
public:
    P(int a,int b)
    {
        cout << "有参构造函数" << endl;
        m_A=a;
        m_B=new int(b);
    }
    P (const P &other)
    {
        cout << "拷贝构造函数" << endl;
        m_A=other.m_A;
        m_B=new int(*(other.m_B));
    }
    ~P ()
    {
        if(m_B)
        {
            delete m_B;
        }
    }
    int m_A;
    int *m_B;
};

int main()
{
    P p(1,2);
    P p1(p);
    return 0;
}