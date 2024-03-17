#include <iostream>
using namespace std;

void  max(int a,int b)
{
    cout << "int比较" << endl;
    if(a>b)
    cout <<a << endl;
    else 
    cout << b << endl;
}

void  max(double a,double b)
{
    cout << "double 比较" << endl;
    if(a>b)
    cout <<a << endl;
    else 
    cout << b << endl;
}

int main()
{
    double  a=20;
    double  b=30;
    max(a,b);
    return 0;
}

// class P
// {
// public:
//     P operator+(P a)
//     {
//         P temp;
//         temp.m_A=a.m_A+this->m_A;
//         return temp;
//     }
//     int m_A;
// };
// int main()
// {
//     P p1;
//     P p2;
//     p1.m_A = 20;
//     p2.m_A = 30;
//     P p3;
//     p3=p1+p2;

//     return 0;
// }

// class P
// {
// public:
//     P(int a)
//     {
//         m_A=a;
//     }
//     P &operator=()
//     int m_A;
// };

// int main()
// {
//     int b=20;
//     int &a=b;   
//     int &&c=2;
//     cout << c << endl;
//     return 0;
// }

// void swap(int &a,int &b)
// {
//     int temp=a;
//     a=b;
//     b=temp;
// }
// int main()
// {
//     int a=10;
//     int b=20;
//     swap(a,b);
//     cout << b << endl;
   
//     cout << a << endl;
//     return 0;
// }