#include <iostream>
#include <string>
using namespace std;

#define day 7

int main()
{
    bool ok=false;
    cout <<ok<<endl;
    int a =10;
    int b =20;
    int c=30;
    short d=10;
    float f =2.1e-1;
    double dt =3.14;
    char ch='a';
    string str="hello world!";
    cout <<str<<endl;
    // 创建字符型的时候要用单引号
    // 创建字符型时，单引号内只能由一个字符
    cout<<"helloworld\t"<<(int)ch<<"\n"<<endl;
    // 默认情况下，输出一个小数，会显示6位有效数字
    cout <<dt<<endl;
    cout <<f<<endl;
    cout <<"short d="<<d<<endl;
    cout <<"c="<<c+b<<endl;
    cout <<"b =" <<b <<endl;
    cout <<"a =" <<a <<endl;
    cout <<"一周有"<<day<<" 天"<<endl;
    cout <<sizeof(long)<<endl;
    cout <<sizeof(short)<<endl;
    cout <<sizeof(long long)<<endl;
    cout <<sizeof(d)<<endl;
    return 0;
}