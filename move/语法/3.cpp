#include <iostream>
#include <string>
using namespace std;

//函数调用运算符重载()

class Myprint
{
public:
    //重载函数调用运算符
    void operator()(string test)
    {
        cout << test << endl;
    }
};

void test()
{
    Myprint Myprint;
    Myprint("helloworld");
    Myprint.operator()("helloworld");
}

int main()
{
    test();
    return 0;
}

//关系运算符重载
// class Person
// {
// public:
//     Person(string name,int age)
//     {
//         m_Name=name;
//         m_Age=age;
//     }
//     bool operator==(Person &P)
//     {
//         if(this->m_Name==P.m_Name && this->m_Age==P.m_Age)
//         {
//             return true;
//         }
//         return false;
//     }
//     bool operator!=(Person &P)
//     {
//         if(this->m_Name==P.m_Name && this->m_Age==P.m_Age)
//         {
//             return false;
//         }
//         return true;
//     }
//     string m_Name;
//     int m_Age;
// };

// void test()
// {
//     Person p1("John",18);
//     Person p2("John",18);
//     if(p1 == p2)
//     {
//         cout << "p1==p2" << endl;
//     }
//     else
//     {
//         cout << "p1!=p2" << endl;
//     }
//     if(p1!=p2)
//     {
//         cout << "p1!=p2" <<endl;
//     }
//     else
//     {
//         cout << "p1==p2" <<endl;
//     }
// }

// int main()
// {
//     test();
//     return 0;
// }

//赋值运算符重载
// class Person
// {
// public:
//     Person(int age)
//     {
//         m_Age = new int(age);
//     }
//     Person& operator=(Person &p)
//     {
//         //应该先判断是否有属性在堆区，如果有先释放干净，然后在深拷贝
//         if(m_Age !=NULL)
//         {
//             delete m_Age;
//         }
//         m_Age= new int(*(p.m_Age));
//         return *this;
//     }
//     ~Person()
//     {
//         if(m_Age!=NULL)
//         {
//             delete m_Age;
//             m_Age = NULL;
//         }
//     }
//     int *m_Age;
// };

// void test()
// {
//     Person p1(18);
//     Person p2(20);
//     Person p3(30);
//     p3=p2=p1;
//     cout << *p1.m_Age << endl;
//     cout << *p2.m_Age << endl;
//     cout << *p3.m_Age << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//递增运算符重载

// class MyIntegar
// {
//     friend ostream& operator<<(ostream& os,  MyIntegar s);
// public:
//     MyIntegar()
//     {
//         m_Num = 0;
//     }
//     //重载前置++运算符
//     MyIntegar& operator++()
//     {
//         m_Num++;
//         return *this;
//     }
//     MyIntegar operator++(int)//int代表占位参数，可以用于区分前置和后置递增
//     {
//         MyIntegar temp=*this;
//         this->m_Num++;
//         return temp;
//     }

// private:
//     int m_Num;
// };

// ostream& operator<<(ostream& os,  MyIntegar s)
// {
//     os << s.m_Num ;
//     return os;
// }

// void test()
// {
//     MyIntegar myint;
//     cout << ++(++myint)<<endl; 
//     cout << myint << endl;
// }

// void test2()
// {
//     MyIntegar myint;
//     cout << myint++<<endl; 
//     cout << myint << endl;
// }

// int main()
// {
//     test();
//     test2();
//     return 0;
// }

//左移运算符重载
// class Person
// {
// public:
//     // 通常不会利用成员函数重载<<运算符，因为无法实现cout在左侧
//     // void operator<<()
//     // {
        
//     // }
//     int m_A;
//     int m_B;
// };

// //只能全局函数来重载左移运算符
// ostream& operator<<(ostream &cout,Person &p)
// {  
//     cout << "m_A=" << p.m_A <<endl;
//     cout << "m_B=" << p.m_B <<endl;
//     return cout;
// }

// void test()
// {
//     Person p;
//     p.m_A = 10;
//     p.m_B = 10;
//     cout << p << "helloworld" << endl;
//     cout << p.m_A << " " << p.m_B << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//加号运算符重载 
//1.成员函数重载 +号
//2.全局函数重载 +号

// class Person
// {
// public:
//     // Person operator+(Person &p)
//     // {
//     //     Person temp;
//     //     temp.m_A=this->m_A+p.m_A;
//     //     temp.m_B=this->m_B+p.m_B;
//     //     return temp;
//     // }
//     int m_A;
//     int m_B;
// };

// Person operator+(Person &p1,Person &p2)
// {
//     Person temp;
//     temp.m_A=p1.m_A+p2.m_A;
//     temp.m_B=p1.m_B+p2.m_B;
//     return temp;
// }

// Person operator+(Person &p,int num)
// {
//     Person temp;
//     temp.m_A=p.m_A+num;
//     temp.m_B=p.m_B+num;
//     return temp;
// }

// void test()
// {
//     Person p1;
//     p1.m_A = 10;
//     p1.m_B = 10;
//     Person p2;
//     p2.m_A = 10;
//     p2.m_B = 10;
//     Person p3=p1+p2;
//     cout << p3.m_A << endl;
//     cout << p3.m_B << endl;
//     Person p4=p3+10;
//     cout << p4.m_A <<endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//成员函数做友元

// class Building;

// class goodGay 
// {
// public:
//     goodGay();
//     void visit1();//visit可以访问私有成员
//     void visit2();//不可以访问私有成员
//     Building *building;
// };

// class Building
// {
//     friend void goodGay::visit1();
// public:
//     Building();
// public:
//     string m_SettingRoom;
// private:
//     string m_BedRoom;
// };

// Building :: Building()
// {
//     m_SettingRoom = "客厅";
//     m_BedRoom = "卧室";
// }
// goodGay :: goodGay()
// {
//     building = new Building;
// }

// void goodGay :: visit1()
// {
//     cout << "Building " << building->m_SettingRoom <<endl;
//     cout << "Building " << building->m_BedRoom <<endl;
// }

// void goodGay :: visit2()
// {
//     cout << "Building " << building->m_SettingRoom <<endl;
// }

// void test()
// {
//     goodGay g;
//     g.visit1();
//     g.visit2();
// }

// int main()
// {
//     test();
//     return 0;
// }

//类做友元 

// class Building;

// class Building
// {
//     //goodGay类是本类的好朋友，可以访问本类中的私有成员
//     friend class goodGay;
// public:
//     Building();
// public:
//     string m_SittingRoom;
// private:
//     string m_BedRoom;
// };


// class goodGay
// {
//     public:
//     goodGay();
//     void visit();//参观函数访问Building中的属性
//     Building *building;
// };

// goodGay::goodGay()
// {
//     building = new Building;
// }

// void goodGay:: visit()
// {
//     cout<<building->m_SittingRoom<<endl;
//     cout<<building->m_BedRoom<<endl;
// }


// //类外去写成员函数
// Building::Building()
// {
//     m_SittingRoom = "客厅";
//     m_BedRoom = "卧室";
// }  

// void test01()
// {
//     goodGay g;
//     g.visit();
// }

// int main()
// {
//     test01();
//     return 0;
// }

//成员函数做友元
// class Building
// {
//     //goodGay全局函数是 BUilding好朋友 ，可以访问Building中私有成员
//     friend void goodGay(Building &building);
// public:
//     Building()
//     {
//         m_SittingRoom ="客厅";
//         m_BedRoom = "卧室";
//     }
// public:
//     string m_SittingRoom;
// private:
//     string m_BedRoom;
// };

// void goodGay(Building &building)
// {
//     cout << building.m_SittingRoom << endl;
//     cout << building.m_BedRoom << endl;
// }

// void test01()
// {
//     Building building;
//     goodGay(building);
// }

// int main()
// {
//     test01();
//     return 0;
// }

// //const修饰成员函数
// class Person
// {
// public:
//     void showPerson() const
//     {
//         this->m_B=200;
//     }
//     int m_A;
//     mutable int m_B;
// };

// void test()
// {
//     Person p;
//     p.showPerson();
//     cout << p.m_B << endl;
// }

// void test2()
// {
//     // const Person p;
//     // 常对象只能调用常函数
// }

// int main()
// {
//     test();
//     return 0;
// }

// class Person
// {
// public:
//     void showClassName()
//     {
//         cout << "Person" << endl;
//     }
//     void showPersonAge()
//     {
//         //报错原因是因为传入的指针是为NULL空的
//         if(this==NULL) return;
//         cout << "age=" << m_Age << endl;
//     }
//     int m_Age;
// };

// void test01()
// {
//     Person *P=NULL; 
//     P->showClassName();
//     // P->showPersonAge();
// }

// int main()
// {
//     test01();
//     return 0;
// }

//this指针
// class Person
// {
// public:
//     Person(int age)
//     {
//         //解决名称冲突
//         this->age = age;
//     }
//     Person& PersonAddage(Person &P)
//     {
//         this->age += P.age;
//         return *this;
//     }
//     int age;
// };

// void test01()
// {
//     Person p1(18);
//     cout << p1.age << endl;
// }

// void test02()
// {
//     Person p1(10);
//     Person p2(10);
//     p2.PersonAddage(p1).PersonAddage(p1).PersonAddage(p1);
//     cout << p2.age <<endl;
// }

// int main()
// {
//     test02();
//     return 0;
// }

//成员变量 和 成员函数 分开存储
// class Person
// {
// public:
//     int m_A;//属于类的对象上
//     static int m_B;//不属于类的对象上
//     void func()//不属于类的对象上
//     {

//     }
//     static void func2(){}
// };

// int Person ::m_B = 0;

// void test01()
// {
//     Person P;
//     cout << sizeof(P) << endl;
// }

// void test02()
// {
//     Person P;
//     cout << sizeof(P) << endl;
// }

// int main()
// {
//     test02();
//     return 0;
// }

//静态成员函数
// class Person
// {
// public:
//     static void func()
//     {
//         m_A=200;
//         cout << "static" << endl; 
//     }
//     static int m_A;
//     int m_B;
// };

// int Person :: m_A=100;

// void test()
// {
//    Person ::func();
// }

// int main()
// {
//     test();
//     return 0;
// }

//静态成员变量
// class Person
// {
// public:
//     //所有对象共享一份内存
//     //编译阶段就分配内存
//     //类内声明，类外初始化
//     static int m_A;
//     //静态成员变量也具有访问权限
// private:
//     static int m_B;
// };

// int Person ::m_A = 100;
// int Person ::m_B =200;
// void test()
// {
//     Person p;
//     cout << p.m_A << endl;
//     Person p2;
//     p2.m_A = 200;
//     cout << p.m_A << endl;
// }

// void test2()
// {
//     //静态成员变量 不属于某一个对象 ，所有对象都共享同一份数据
//     //1.通过对象进行访问    
//     //2.通过类名进行访问
//     // Person p;
//     // cout<<p.m_A<<endl;
//     cout << Person ::m_A << endl;
//     //cout <<Person ::m_B << endl;
// }

// int main()
// {
//     test2();
//     return 0;
// }

//类对象作为类成员

// class Phone
// {
// public:
//     Phone(string name)
//     {
//         m_PName = name;
//         cout <<"Phone"<<endl;
//     }
//     ~Phone()
//     {
//         cout <<"Phone"<<endl;
//     }
//     string m_PName;
// };

// class Person
// {
// public:
//     Person(string name,string PName):m_Name(name),m_Phone(PName)
//     {
//         cout<<"Person"<<endl;
//     }
//     ~Person()
//     {
//         cout<<"Person"<<endl;
//     }
//     string m_Name;
//     Phone m_Phone;
// };

// void test()
// {
//     Person p("张三","苹果");
//     cout<<p.m_Name<<endl;
//     cout<<p.m_Phone.m_PName<<endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//初始化列表

// class Person
// {
// public:
//     // Person(int a,int b,int c)
//     // {
//     //     m_A = a; m_B = b; m_C = c;
//     // }
//     //初始化列表
//     Person(int a,int b,int c):m_A(a),m_B(b),m_C(c)
//     {
        
//     }
//     int m_A;
//     int m_B;
//     int m_C;
// };

// void test01()
// {
//     // Person p(1,2,3);
//     Person p(30,20,10);
//     cout << p.m_A << endl; 
//     cout << p.m_B << endl;
//     cout << p.m_C << endl;
// }

// int main()
// {
//     test01();
//     return 0;
// }