#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// int main()
// {
//     srand((unsigned int)time(NULL));
//     for(int i=0;i<5;i++)
//     {
//         int a=rand();
//         cout<<"a = "<<a<<endl;
//     }
//     return 0;
// }

// int main()
// {
//     unsigned int i=10;
//     unsigned int j=42;
//     std::cout<<j-i<<std::endl;
//     std::cout<<i-j<<std::endl;
//     int m=10;
//     int n=42;
//     std::cout<<n-m<<std::endl;
//     std::cout<<m-n<<std::endl;
//     std::cout<<m-j<<std::endl;
//     std::cout<<i-m<<std::endl;
//     return 0;
// }
// 11111111111111111111111100000000
// 00000000000000000000000000001010
// 00000000000000000000000000101010
// 10000000000000000000000000100000
/* int main()
{
    int i;
    
} */

//#include "Sales_item.h"
/* int main()
{
    Sales_item book;
    std::cin>>book;
    std::cout<<book<<std::endl;
    return 0;
} */

// int main()
// {
//     int v1;
//     std::cin >> v1;
//     std::cout<<"helloworld"<<v1;
//     std::cout<<std::endl;
//     return 0;
// }

// /* struct grade
// {
//     int math;
//     int english;
//     int chinese;
// };

// struct student
// {
//     int id;
//     string name;
//     struct grade stu;
//     int age;
// };



// int main()
// {
//     struct student s1;

//     cin >> s1.stu.english;
//     cin >> s1.stu.chinese;
//     cin >> s1.stu.math;
//     cout << s1.stu.english << endl;
// } */

/* int main()
{
    student s1[3];
    for(int i=0; i<3; i++)
    {
        cin >> s1[i].age;
        cin >> s1[i].math;
        cin >> s1[i].name;
        cin >> s1[i].id;
    }
    for(int i=0; i<3; i++)
    {
        cout << s1[i].math << endl;
        cout << s1[i].age << endl;
        cout << s1[i].name << endl;
        cout << s1[i].id << endl;
    }
    student *s2=&s1[1];
    cout << s2->math <<endl;
    return 0;
} */

// int main()
// {
//     int arr[10]={0,1,2,3,4,5,6,7,8,9};
//     int *p=arr;
//     cout<<*p<<endl;

//     return 0;
// }

// int main()
// {
//     int a=10;
//     cout << &a << endl;
//     int *p=&a;
//     cout << p << endl;
//     cout <<&p << endl;
//     cout <<sizeof(p) << endl;
//     cout <<sizeof(char *)<<endl;
//     cout <<sizeof(double *)<<endl;
//     cout <<sizeof(float *)<<endl;
//     cout <<sizeof(long *)<<endl;
//     return 0;
// }

// int add(int x, int y)
// {
//     return x+y;
// }

// int main()
// {
//     int a;
//     cin >> a;
//     int b;
//     cin>>b;
//     int sum=add(a,b);
//     cout<<sum<<endl;
//     return 0;
// }

// int main()
// {
//     int arr[2][3]={{1,2,3},{4,5,6}};
//     cout <<  arr << endl;
//     cout <<sizeof(arr[0])<<endl;
//     cout <<sizeof(arr[0][0])<<endl;
//     cout <<sizeof(arr)/sizeof(arr[0])<<endl;
//     cout <<sizeof(arr[0])/sizeof(arr[0][0])<<endl;
//     system("pause");
//     return 0;
// }

/* int main()
{
    cout <<"1.xxxx"<<endl;

    goto start;
    cout <<"2.xxxx"<<endl;

    cout <<"3.xxxx"<<endl;

    cout <<"4.xxxx"<<endl;
    
    //标记要加后面要加的是冒号
    start:
    cout <<"5.xxxx"<<endl;
    return 0;
} */

/* int main()
{
    for(int i=1;i<10;i++)
    {
        for(int j=1;j<=i;j++)
        {
            cout<< j <<"*"<<i<<"="<< j*i <<"   ";
        }
        cout <<endl;
    }
    return 0;
} */

// int main()
// {
//     for(int i=100;i<10000;i++)
//     {
//         int sum=0;
//         int num=i;
//         int x=0;
//         while(num)
//         {
//             x++;
//             num/=10;
//         }
//         num=i;
//         while(num)
//         {
//             int a=num%10;
//             int y=1;
//             for(int j=0;j<x;j++)
//             {
//                 y*=a;
//             }
//             sum+=y;
//             num/=10;
//         }
//          if(i==sum)
//         {
//             cout << i << endl;
//         }
//     }
//     return 0;
// }

/* int main()
{
    int a;
    do
    {
        cin >> a;
    }while(a>0);
    cout << a << endl;
    return 0;
} */

/* int main()
{
    int num=rand()%100+1;
    int guess;
    while(cin>>guess)
    {
        if(guess<num)
        {
            cout<<"猜小了"<<guess<<endl;
        }
        else if(guess>num)
        {
            cout << "猜打了" << guess<<endl;
        }
        else
        {   
            cout <<"guess successfully"<<endl;
            break;
        }
    }
    return 0;
} */

// int main()
// {
    // int i=1;
    // while(i<=10)
    // {
        // cout<<i<<endl;
        // i++;
    // }
    // return 0;
// }

/* int main()
{
    int a;
    cin>>a;
    int b;
    cin>>b;
    int c;
    cin>>c;
    if(a>b)
    {
        if(a>c)
        {
            cout<<a<<endl;
        }
        else
        {
            cout<<c<<endl;
        }
    }
    else
    {
        if(c>b)
        {
            cout<<c<<endl;
        }
        else
        {
            cout<<b<<endl;
        }
    }

    return 0;
} */

/* int main()
{
    //1.整形
    /* int a=0;
    cout<<"请给整形赋值: "<<endl;
    cin >> a;
    cout <<"a= "<<a<<endl; */
    //2.浮点型
    /* double b=0;
    cout <<"请给浮点型赋值:"<< endl;
    cin >> b;
    cout <<"b= "<<b<<endl; */
    //3.字符型
    /* char c;
    cout <<"请给字符赋值: "<< endl;
    cin >> c;
    cout <<"ch="<<c<<endl; */
    //4.字符串型
   /*  string str;
    cout<<"请给字符串赋值："<<endl;
    cin >>str;
    cout << "str="<<str<<endl; */
    //布尔
    /* bool d;
    cin >>d;
    cout <<d<<endl; */
    /* int a=10;
    cout << !a<<endl;
    cout <<!!a<<endl;
    return 0;
} */ 