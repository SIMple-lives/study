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
        cout << "有参构造函数" << endl;
    }
    P(P & other)
    {
        cout << "拷贝构造函数" << endl;
        m_A = other.m_A;
    }
    int m_A;
};

int main()
{
    P p(10);
    P p1=(p);
    return 0;
}

// void print(int &&a)
// {
//     cout << a << endl;
// }

// int main()
// {
//     print(1);
//     return 0;
// }

// int max(const int &a,const int &b)
// {
//     return a+b;
// }

// int main()
// {
//     cout << max(1,2) << endl;
//     return 0;
// }

// class A
// {
// public:
//     int m_A;
// };

// A getTmp()
// {
//     return A();
// }

// int main()
// {
//     int a=10;
//     int &ref=a;
//     int &&ref1 =1;
//     return 0;
// }

// int sum1 = 0;

// int& sum(int &a,int &b) 
// {
//     sum1 = a + b;
//     return sum1;
// }

// int main()
// {
//     int a=10;
//     int b=10;
//     sum(a,b)=30;
//     cout << sum1 << endl;    
//     return 0;
// }

// class Num
// {
// public:
//     Num()
//     {
//         cout << "gz" << endl;
//     }
//     Num(const Num &other)
//     {
//         m_A=other.m_A;
//         m_B=new int (*other.m_B);
//         cout << "kb" << endl;
//     }
//     ~Num()
//     {
//         if(this->m_B)
//         {
//             delete this->m_B;
//             this->m_B=nullptr;
//         }
//     }
//     int m_A;
//     int *m_B;
// };

// int main()
// {
//     Num a;
//     a.m_A=1;
//     a.m_B=new int(20);
//     Num b(a);
//     cout << b.m_A << endl;
//     cout << *b.m_B << endl;
//     cout << a.m_B << endl;
//     return 0;
// }

// class Num
// {
// public:
//     Num(int a): m_A(a)
//     {
// 		cout << "gz" << endl;
//     }
//     int m_A;
// };

// int main()
// {
//     Num num(10);
//     cout << num.m_A << endl;
//     return 0;
// }