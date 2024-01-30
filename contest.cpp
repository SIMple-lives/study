#include <iostream>
#include <stdbool.h>
#include <string>
using namespace std;

class Person
{
    public:
    Person()
    {
        cout << "Person" << endl;
    }
    Person(int a,int height)
    {
        m_age =a;
        m_height= new int(height);
        cout << "Personyc" << endl;
    }
    Person(const Person &other)
    {
        cout << "Personkb" << endl;
        m_age = other.m_age;
        m_height =new int(*other.m_height);//深拷贝
    }
    ~Person()
    {
        //析构，将堆区开辟的空间做释放操作
        if(m_height !=NULL)
        {
            delete m_height;
        }
        cout << "Personxg" << endl;
    }
    int m_age;
    int *m_height; 
};

void test01()
{
    Person p1(18,160);
    cout << p1.m_age << endl;
    cout << *p1.m_height << endl;
    Person p2(p1);
    cout << p2.m_age << endl;
    cout << *p2.m_height <<endl;//会发生错误，因为p2是浅拷贝，但析构函数内部对p2进行了释放，对堆区的内存重复释放
}

int main()
{
    test01();
    return 0;
}

//拷贝构造函数的调用时机
// class Person
// {
//     public:
//     Person()
//     {
//         cout << "Person" << endl;
//     }
//     Person(int a)
//     {
//         age = a;
//         cout << "Personyc" << endl;
//     }
//     Person(const Person &other)
//     {
//         age = other.age;
//         cout << "Personkb" << endl;
//     }
//     ~Person()
//     {
//         cout << "Personxg" << endl;
//     }
//     int age;
// };

// void test01()
// {
//     Person p1(20);
//     Person p2(p1);
//     cout << p2.age << endl;
// }

// void dowork(Person p)
// {
    
// }

// void test02()
// {
//     Person p;
//     dowork(p);
// }

// Person dowork2()
// {
//     Person p;
//     return p;
// }


// void test03()
// {
//     Person p=dowork2();
// }

// int main()
// {
//     test03();
//     return 0;
// }

// class Person
// {
//     public:
//     Person()//可以函数重载
//     { 
//         cout << "Person构造" << endl;
//     }
//     Person(int a)
//     {
//         cout << "Person有参" <<endl;
//         age = a;
//     }
//     Person(const Person &p)
//     {
//         age=p.age;
//         cout<< "Person拷贝"<<endl;
//     }
//     ~Person()
//     {
//         cout << "Person析构" << endl;
//     }
//     int age;
// };

// void test01()
// {
//     //1.括号法
//     // Person p;
//     // Person p2(10);
//     // Person p3(p2);
//     //2.显示法
//     Person p1;
//     Person p2=Person(10);
//     Person p3=Person(p2);
//     //person(10)匿名对象，这一行结束之后就销毁
//     //3.隐式转换
//     Person p4=10;//相当于person p4=person (10)
// }

// int main()
// {
//     test01();
//     return 0;
// }

// class Person
// {
//     public:
//     //1/构造函数 进行初始化操作
//     Person()
//     {
//         cout << "Person构造函数的调用" << endl;
//     }
//     //2.析构函数
//     ~ Person()
//     {
//         cout << "Person析构函数的调用" << endl;
//     }
// };

// int main()
// {
//     Person P;
//     return 0;
// }

// class Point
// {   
// public:
//     void setx(int x)
//     {
//         m_X = x;
//     }
//     void sety(int y)
//     {
//         m_Y = y;
//     }
//     int getX() 
//     {
//         return m_X;
//     }
//     int getY() 
//     {
//         return m_Y;
//     }
// private:
//     int m_X;
//     int m_Y;
// };

// class Circle
// {
// public:
//     void setR(int r)
//     {
//         m_R = r;
//     }
//     int getR() 
//     {
//          return m_R; 
//     }
//     void setcenter(Point center)
//     {
//         m_Center = center;
//     }
//     Point getCenter() 
//     {
//         return m_Center;
//     }
// private:
//     int m_R;
//     //在类中可以让另外一个类作为本来中的成员.
//     Point m_Center;
// };

// void isIncircle(Circle &c1,Point &p1)
// {
//     int x=(c1.getCenter().getX()-p1.getX())*(c1.getCenter().getX()-p1.getX())+
//     (c1.getCenter().getY()-p1.getY())*(c1.getCenter().getY()-p1.getY());
//     int y=c1.getR()*c1.getR();
//     if(x==y)
//     {
//         cout<<"Circle"<<endl;
//         return ;
//     }
//     else if(x<y)
//     {
//         cout <<"incircle"<<endl;
//         return ;
//     }
//     else
//     {
//         cout<<"outCircle"<<endl;
//         return ;
//     }
// }

// int main()
// {
//     Circle c1;
//     c1.setR(10);
//     Point center;
//     center.setx(10);
//     center.sety(0);
//     c1.setcenter(center);
//     Point p1;
//     p1.setx(10);
//     p1.sety(10);
//     isIncircle(c1,p1);
//     Point p2;
//     p2.setx(10);
//     p2.sety(13);
//     isIncircle(c1,p2);
//     Point p3;
//     p3.setx(10);
//     p3.sety(9);
//     isIncircle(c1,p3);
//     return 0;
// }

// class Cube
// {
//     public:
//     void setL(int x)
//     {
//         m_L = x;
//     }
//     void setW(int x)
//     {
//         m_W = x;
//     }
//     void setH(int x)
//     {
//         m_H = x;
//     }
//     int getL()
//     {
//         return m_L;
//     }
//     int getW()
//     {
//         return m_W;
//     }
//     int getH()
//     {
//         return m_H;
//     }
//     int calculateS()
//     {
//         return 2*m_L*m_W+2*m_H*m_W+2*m_H*m_L;
//     }
//     int calculateV()
//     {
//         return m_H*m_W*m_W;
//     }
//     bool isSameclass(Cube &other)
//     {
//         if(m_L==other.getL()&&m_H==other.getH()&&m_W==other.getW())
//         {
//             return true;
//         }
//         return false;
//     }
//     private:
//     int m_L;
//     int m_W;
//     int m_H;
// };

// bool isSame(Cube &a, Cube &b)
// {
//     if(a.getL() == b.getL()&&a.getH() == b.getH()&&a.getW()==b.getW())
//     {
//         return true;
//     }
//     return false;
// }

// int main()
// {
//     Cube c1;
//     c1.setL(10);
//     c1.setH(10);
//     c1.setW(10);
//     cout<<c1.calculateS()<<endl;
//     cout<<c1.calculateV()<<endl;
//     Cube c2;
//     c2.setL(10);
//     c2.setH(10);
//     c2.setW(10);
//     cout<<isSame(c1, c2)<<endl;
//     cout<<c1.isSameclass(c2)<<endl;
//     return 0;
// }

//成员属性设置为私有
//1.可以自己控制读写权限
//2.对于写权限，可以检测数据的有效性

// class Person
// {
//     public:
//     //设置姓名
//     void setName(string name)
//     {
//         m_Name=name;
//     }
//     string getName()
//     {
//         return m_Name;
//     }
//     int getAge()
//     {
//         return m_Age;
//     }
//     void setIdol(string idol)
//     {
//         m_Idol=idol;
//     }
//     string getId()
//     {
//         return m_Idol;
//     }
//     void setAge(int age)
//     {
//         if(age>=0 && age<150)
//         {
//             m_Age=age;
//         }
//         else
//         cout<<"年龄输出有误，赋值失败"<<endl;
//     }
//     private:
//     string m_Name;//可读可写
//     int m_Age=18;   //只读
//     string m_Idol;//只写
// };

// int main()
// {
//     Person p;
//     p.setName("John");
//     p.setIdol("John");
//     p.setAge(151);
//     cout<< p.getName()<<endl;
//     cout<<p.getAge()<<endl;
//     cout<<p.getId()<<endl;
//     return 0;
// }

// class Person
// {
// public:
// 	string m_Name;
// protected:
//     string m_Car;
// private:
//     int m_Password;
// public:
//     void func()
//     {
//         m_Name="张三";
//         m_Car="饿狼传说";
//         m_Password=123145;
// 	}
// };

// int main()
// {
//     Person p1;
//     cin>>p1.m_Name;

//     return 0;
// }

// class Student
// {
//     //公共权限
// public://权限
//     string m_Name;
//     int m_Id;
//     void show()
//     {
//         cout<< "姓名 ："<<m_Name << "  学号 ："<<m_Id<<endl;
//     }
//     void set(string name, int id)//给姓名赋值
//     {
//         m_Name = name;
//         m_Id = id;
//     }
// };

// int main()
// {
//     Student s1;
//     s1.set("张三",1);
//     s1.show();
//     Student s2;
//     cin>>s2.m_Name>>s2.m_Id;
//     s2.show();
//     return 0;
// }

// const double PI =3.14;
// class Circle 
// {
//     //访问权限
// public:
//     //圆的属性
//     int m_r;
//     //行为
//     //获取周长
//     double calculateZC()
//     {
//         return 2*PI*m_r;
// 	}
// };

// int main()
// {
//     Circle c1;
//     c1.m_r=10;
//     cout<<c1.calculateZC()<<endl;
//     return 0;
// }

// void func(int &a)//这两个可以作为函数重载的条件，因为函数的参数类型不同
// {
//     cout << "func(int &a)调用" <<endl;
// }

// void func(const int &a)
// {
//     cout << "func(const int &a)调用"<<endl;
// }

// int main()
// {
//  	int a=10;
//     func(a);//调用的是第一个，因为这是一个变量.
//     const int b=10;
//     func(b);//调用的是第二个。
//     return 0;
// }

// void func()
// {
//     cout<<"helloworld"<<endl;
// }

// int  func(int a,int b)
// {
//     return a+b;
// }

// void func(int a,double b)
// {
//     cout<<"helloworldint double"<<endl;
// }

// void func(double a,int b)
// {
//     cout<<"helloworlddouble int"<<endl;
// }

// int main()
// {
//     func();
//     cout<<func(10,20)<<endl;
//     func(1.1,2);
//     func(2,1.1);
//     return 0;
// }

// int fun(int a,int )
// {
//     return a;
// }

// int main()
// {
//     int a=10;
//     int b=10;
//     cout << fun(a,b) << endl;
//     return 0;
// }

// int fun(int a,int b=20,int c=30)//函数的默认参数，如果我们传入了参数，值就使用我们传入的参数，如果我们没有传入参数，那么就使用函数的默认参数值
// {
//     return a+b+c;
// }

// int main()
// {
//     cout<< fun(1,40,50)<<endl;
//     return 0;
// }

// int main()
// {
//     int *arr=new int[10];
//     for(int i=0;i<10;i++)
//     {
//         arr[i]=i+1;
//     }
//     int &num=arr[0];
//     cout<<num<<endl;
//     delete[] arr;
//     return 0;
// }

// int main()
// {
//     int a=10;
//     int &b=a;
//     cout<<a<<endl;
//     cout<<b<<endl;
//     b=30;
//     cout<<a<<endl;
//     cout<<b<<endl;
//     double d=9.1;
//     double &c=d;
//     cout<<c<<endl;
//     return 0;
// }

// int *func()
// {
//     int *p=new int(10);
//     return p;
// }

// int *func1()
// {

//     int * arr=new int[10];//代表数组有10个元素
//     for(int i=0;i<10;i++)
//     {
//         arr[i]=i;
//     }
//     return arr;
// }

// int main()
// {
//     int *p=func();
//     cout<<*p <<endl;
//     delete p;
//     // cout<< *p <<endl;
//     int *arr=func1();
//     for(int i=0;i<10;i++)
//     {
//         cout<<arr[i]<<endl;
//     }
//     delete[] arr;
//     return 0;
// }

// int main()
// {
//     int a=10;
//     cout << (int)  &a << endl;
//     return 0;
// }

// #define MAX 1000

// struct Person
// {
//     string name;
//     int m_Sex;
//     int m_Age;
//     string m_Phone;
//     string m_Address;
// };

// struct Addressbook
// {
//     struct Person arr[MAX];
//     int Size;
// };

// void menu()
// {
//     cout << "\033[42;31m********************************"<<endl;
//     cout << "\033[43;32m*****       1.add         ******"<<endl;
//     cout << "\033[42;33m*****      2.show         ******"<<endl;
//     cout << "\033[43;34m*****      3.delete       ******"<<endl;
//     cout << "\033[42;35m*****      4.find         ******"<<endl;
//     cout << "\033[43;36m*****      5.fix          ******"<<endl;
//     cout << "\033[42;35m*****      6.alldelete    ******"<<endl;
//     cout << "\033[43;34m*****      7.exit         ******"<<endl;
//     cout << "\033[42;31m********************************"<<endl;
// }

// void add(struct Addressbook *book)
// {
//     if(book->Size==MAX)
//     {
//         cout<<"full size"<<endl;
//     }
//     else
//     {
//         cout<<"name"<<endl;
//         cin>>book->arr[book->Size].name;

//     }
// }

// int main()
// { 
//     int input = 0;
//     Addressbook address;
//     address.Size=0;
//     while(true)
//     {
//         menu();
//         cin>>input;
//         switch(input) 
//         {
//             case 1:
//             add(&address);
//             break;
//             case 2:
//             break;
//             case 3:
//             break;
//             case 4:
//             break;
//             case 5:
//             break;
//             case 6:
//             break;
//             case 0:
//             cout<<"exit"<<endl;
//             system("pause");
//             return 0;
//             break;
//             default:
//             break;
//         }
//     }
    
//     return 0;
// }