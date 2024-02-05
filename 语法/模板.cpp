#include <iostream>
using namespace std;
#include <string>

//类模板
template <typename T1,typename T2>
class Person
{
public:
    Person(T1 name ,T2 age)
    {
        m_Name = name;
        m_Age = age;
    }
    T1 m_Name;
    T2 m_Age;
};

void test()
{
    Person<string,int> p("John",17);
    cout << p.m_Age << endl;
    cout << p.m_Name << endl;
}

int main()
{
    test();
    return 0;
}


//模板的局限性
//函数模板并不是万能的，有些特定的数据类型，需要用具体化方式做特殊实现
//对比两个数据是否相等

// class Person
// {
// public:
//     Person(string name, int age)
//     {
//         m_name = name;
//         m_age = age;
//     }
//     string m_name;
//     int m_age;
// };

// template <typename T>
// bool mycompare(T &a, T &b)
// {
//     if(a==b)
//     return true;
//     else 
//     return false;
// }

// //利用具体化Person的版本实现代码，具体化优先调用
// template<>bool mycompare(Person &a,Person &b)
// {
//     if(a.m_name==b.m_name&&a.m_age==b.m_age)
//     {
//         return true;
//     }
//     else
//     return false;
// }

// void test()
// {
//     int a=10;
//     int b=20;
//     cout << mycompare(a,b) << endl;//发生错误，无法比较。1.比较运算符重载   2.
// }

// void test01()
// {
//     Person p1("Tom",10);
//     Person p2("Tom",10);
//     cout << mycompare(p1,p2)<<endl;
// }

// int main()
// {
//     test01();
//     return 0;
// }

//调用规则
// template<typename T>
// void myprint(T a,T b)
// {
//     cout << "函数模板" << endl;
// }

// template<typename T>
// void myprint(T a,T b,T c)
// {
//     cout << "函数模板1" << endl;
// }

// void myprint(int a,int b)
// {
//     cout << "普通函数" << endl;
// }

// void test()
// {
//     int a = 10;
//     int b = 10;
//     //myprint(a,b);//会报错，由于普通函数没有实现体,就需要用到空函数参数列表，强制调用函数模板
//     myprint<>(a,b);
//     myprint(a,b,17);
// }
 
// int main()
// {
//     test();
//     return 0;
// }

//普通函数与函数模板的区别
// template <typename T>
// T myadd(T a, T b) {
//     return a + b;
// }

// int add(int a,int b)
// {
//     return a + b;
// }

// void test()
// {
//     int a=10;
//     int b=10;
//     char c='a';
//     add(a,c);
//     //myadd(a,c);
//     //显示指定类型
//     cout << myadd<int>(a,c) << endl;
// }

// int main()
// {
//     test();  
//     return 0;
// }

//实现通用的对数组进行排序的函数模板
 
// template <typename T>
// int partition(T *a,int i,int j)
// {
//     T x = a[i];
//     while(i<j)
//     {
//         while(i<j && a[j]>=x)
//         {
//             j--;
//         }
//         if(i<j)
//         {
//             a[i]=a[j];
//             i++;
//         }
//         while(i<j && a[i]<x)
//         {
//             i++;
//         }
//         if(i<j)
//         {
//             a[j]=a[i];
//             j--;
//         }
//     }
//     a[i] =x;
//     return i;
// }

// template <typename T>
// void mySort(T *a,int i,int j)
// {
//     if(i<j)
//     {
//         int x=partition(a,i,j);
//         mySort(a,i,x-1);
//         mySort(a,x+1,j);
//     }
// }

// template <typename T>
// void printSort(T *a ,int len)
// {
//     for(int i=0;i<len;i++)
//     {
//         cout << a[i] << "  ";
//     }
//     cout << endl;
// }

// void test()
// {
//     char chararr[]= "bacdfe";
//     mySort(chararr,0,5);
//     printSort(chararr,6);
//     int num[]={4,5,1,2,9,7,0,3,6,8};
//     mySort(num,0,9);
//     printSort(num,10);
// }

// int main()
// {
//     test();
//     return 0;
// }

//函数模板的注意事项
//1.自动类型能够推导，必须要能够推导出一致的数据类型
//2.模板要必须推导出确定的数据类型，才可以使用
// template <class T>
// void mySwap(T &a,T &b)
// {
//     T temp;
//     temp=a;
//     a=b;
//     b=temp;
// }

// template <class T>
// void func()
// {
//     cout << "function" << endl;
// }

// int main()
// {
//     int a=10;
//     int b=20;
//     char c ='c';
//     //正确的mySwap(a,b);
//     //mySwap(a,c);无法确定出一致的数据类型
//     func<int>();//模板无法确定出确定的数据类型
//     return 0;
// }

//函数模板
// template <typename T>//声明一个模板，告诉编译器后面代码中紧跟着的T不要报错，T是一个通用的数据类型
// void myswap(T &a, T &b) 
// {
//     T temp=a;
//     a=b;
//     b=temp;
// }

// //两个整形交换
// void swap(int &a, int &b) 
// {
//     int tmp=a;
//     a=b;
//     b=tmp;
// }

// //两个浮点型交换

// int main()
// {
//     int a=10;
//     int b=20;
//     //两种方式使用函数模板
//     //1.自动类型推导
//     myswap(a,b);
//     cout << a << endl;
//     cout << b << endl;
//     //2.显示指定类型
//     myswap<int>(a,b);
//     cout << a << endl;
//     cout << b << endl;
//     return 0;
// }