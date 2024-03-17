#include <iostream>
using namespace std;

void RunCode(int &&m) 
{
    cout << "rvalue ref" << endl;
}
void RunCode(int &m) 
{
    cout << "lvalue ref" << endl;
}
void RunCode(const int &&m) 
{
    cout << "const rvalue ref" << endl;
}
void RunCode(const int &m) 
{
    cout << "const lvalue ref" << endl;
}

template <typename T>
void myforward(T && a)
{
    RunCode(forward<T>(a));
}

int main()
{
    int a = 0;
    int b = 0;
    const int c = 0;
    const int d = 0;
    return 0;
}

// void process(int &i)
// {
//     cout << "process(int &)" << i << endl;
// }

// void process(int &&i)
// {
//     cout << "process(int &&)" << i << endl;
// }

// void myforward(int &&i)
// {
//     cout <<"myforward(int &&)" << i << endl;
//     //process(i);
//     process(forward<int>(i));
// }

// int main()
// {
//     int a =0;
//     process(a);
//     process(1);
//     process(move(a));
//     myforward(2);
//     myforward(move(a));
//     return 0;
// }