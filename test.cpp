#include <iostream>
#include <typeinfo>
#include <cmath>
#include <vector>
#include <string>
#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <memory>

int main()
{
    std::shared_ptr<int> p(new int(10));
    {
        std::shared_ptr<int> q(p);
        std::cout << *p << std::endl;
        std::cout << p.use_count() << std::endl;
    }
    std::cout << p.use_count() << std::endl;
    
    return 0;
}



// class ThreadGuard
// {
// public:
//     enum class DeAction{join,detach};
//     ThreadGuard(std::thread&& t,DeAction action): m_t(move(t)) , m_action(action){};
//     ~ThreadGuard()
//     {
//         if(m_t.joinable())
//         {
//             if(m_action==DeAction::join)
//             {
//                 m_t.join();
//             }
//             else
//             {
//                 m_t.detach();
//             }
//         }
//     }
//     ThreadGuard(ThreadGuard&&)=default;
//     ThreadGuard& operator=(ThreadGuard&&)=default;
// private:
//     std::thread m_t;
//     DeAction m_action;
// };

// int main()
// {
//     auto fun = []() {
//         for (int i = 0; i < 10; ++i) {
//             cout << i << " ";
//         }
//         cout << endl;
//     };
//     std::thread t(fun);
//     if(t.joinable())
//     {
//         t.detach();
//     }
//     auto func=[](int k){
//         for(int i=0;i<k;i++)
//         {
//             cout << i << " ";
//         }
//         cout << endl;
//     };
//     std::thread t1(func,20);
//     if(t1.joinable())
//     {
//         t1.join();
//     }
//     return 0;
// }

// #include <iostream>

// int main()
// {
//     int ticket;
//     int age;
//     int studentage;
//     std::cout << "请输入学生票的最大年龄： "<<std::endl;
//     std::cin>>studentage;
//     std::cout << "请输入游客的年龄: " <<std::endl;
//     std::cin>>age;
//     std::cout << "请输入普通门票的价格： "<<std::endl;
//     std::cin>>ticket;
//     double ret;
//     if(age<=12)
//     {
//         ret = 10;
//     }
//     else if(age>12&&age<=studentage)
//     {
//         ret = ticket*0.5;
//     }
//     else if(age>studentage&&age<60)
//     {
//         ret=ticket;
//     }
//     else
//     {
//         ret = ticket*0.3;
//     }
//     std::cout << "游客的票价为: "<< ret << std::endl;
//     return 0;
// }

// int main()
// {
//     // std::cout << "************" << std::endl;
//     // std::cout << "  Welcome" << std::endl;
//     // std::cout << "************" << std::endl;
//     std::cout << "************\n  Welcome\n************\n"<<std::endl;
//     return 0;
// }

// void swap(int &a,int &b)
// {
//     int c=a;
//     a=b;
//     b=c;
// }

// int main()
// {
//     int a,b;
//     std::cin>>a>>b;
//     swap(a,b);
//     cout << a << " " << b << endl;
//     return 0;
// }

// static void *func(void * p)
// {
//     puts("thread is working");
//     pthread_exit(NULL);
//     //return NULL;
// }

// int main()
// {
//     pthread_t tid;
//     int err;
//     puts("Begin");
//     err=pthread_create(&tid,NULL,func,NULL);
//     if(err==0)
//     {
//         cout << "Success!" << endl;
//     }
//     else
//     {
//         fprintf(stderr,"pthread_creat()%s\n",strerror(err));
//     }
//     pthread_join(tid,NULL);
//     puts("End");
//     return 0;
// }


// int main()
// {
//     int a =0;
//     int b=20;
//     cout << a+b << endl;
//     return 0;
// }

// int main()
// {
//     int a=20;
//     double d=static_cast<double>(a);
//     cout << d << endl;
//     return 0;
// }

// class Person
// {
// public:
//     Person()
//     {
//         cout << "默认构造" << endl;
//     }
//     Person(int a):m_A(a)
//     {

//     }
//     void print();
//     int m_A;
// };

// void Person::print()
// {
//     cout << m_A << endl;
// }

// class Son:public Person
// {
// public:
    
// };

// int main()
// {

//     Person p(20);
//     p.print();
//     Son s;
//     s.m_A =20;
//     s.print();
//     return 0;
// }

// void print(int a)
// {
//     cout << a << endl;
// }

// void print(double a)
// {
//     cout << a << endl;
// }

// void print(float a)
// {
//     cout << a << endl;
// }

// int main()
// {
//     int a=10;
//     double b=10.1;
//     float c=10.2;
//     print(a);
//     print(b);
//     print(c);
//     return 0;
// }

// struct student_
// {
//     int num;
//     char a;
// };

// class Person//struct 
// {
// public:
//     Person()
//     {
//         cout << "默认构造函数" << endl;
//     }
//     Person (int a,int b,int c,int d)
//     {
//         cout << "jdklasjdlka" << endl;
//         m_a = a;
//         m_b = b;
//         m_c = c;
//         m_d = d;
//     }
//     void print()
//     {
//         cout << "a: " << m_a << endl;
//         cout << "b: " << m_b << endl;
//         cout << "c: " << m_c << endl;
//         cout << "d: " << m_d << endl;
//     }
//     ~Person()
//     {
//         cout << "析构函数" << endl;
//     }
//     int m_a;
//     int m_b;
// protected:
//     int m_c;
// private:
//     int m_d;
// };

// int main()
// {
//     Person p;
//     p.print();
//     return 0;
// }

// int main()
// {
//     std::string N;
//     std::cin>>N;
//     std::vector<int> num(10,0);
//     for(size_t i=0;i<N.size();i++)
//     {
//         num[N[i]-'0']++;
//     }
//     for(int i=0;i<10;i++)
//     {
//         if(num[i]!=0)
//         {
//             std::cout << i << ":" << num[i] << std::endl;
//         }
//     }
//     return 0;
// }


// class AA {
// public:
//     virtual void print() {
//         cout << "in class AA" << endl;
//     };
// };

// class BB :public AA {
// public:
//     void print() {
//         cout << "in class BB" << endl;
//     };
// };

// void testDynamicCast() {
//     AA* a1 = new BB; // a1是A类型的指针指向一个B类型的对象
//     AA* a2 = new AA; // a2是A类型的指针指向一个A类型的对象

//     BB* b1, * b2, * b3, * b4;

//     b1 = dynamic_cast<BB*>(a1);	// not null，向下转换成功，a1 之前指向的就是 B 类型的对象，所以可以转换成 B 类型的指针。
//     if (b1 == nullptr) 
//         cout << "b1 is null" << endl;
//     else               
//         cout << "b1 is not null" << endl;

//     b2 = dynamic_cast<BB*>(a2);	// null，向下转换失败
//     if (b2 == nullptr) 
//         cout << "b2 is null" << endl;
//     else               
//         cout << "b2 is not null" << endl;

//     // 用 static_cast，Resharper C++ 会提示修改为 dynamic_cast
//     b3 = static_cast<BB*>(a1);	// not null
//     if (b3 == nullptr) 
//         cout << "b3 is null" << endl;
//     else               
//         cout << "b3 is not null" << endl;

//     b4 = static_cast<BB*>(a2);	// not null
//     if (b4 == nullptr) 
//         cout << "b4 is null" << endl;
//     else               
//         cout << "b4 is not null" << endl;

//     a1->print();	// in class BB
//     a2->print();	// in class AA

//     b1->print();	// in class BB
//     //b2->print();    // null 引发异常
//     b3->print();	// in class BB
//     b4->print();	// in class AA
// }

// int main()
// {
//     testDynamicCast();
//     return 0;	
// }

// class Person
// {
// public:
//     void  print()
//     {
//         cout << "Person " << endl;
//     }
// };

// class Son : public Person
// {
// public:
//     void print()
//     {
//         cout << "Son " << endl;
//     }
// };

// void print1(Person *p)
// {
//     p->print();
// }

// int main()
// {
//     Son s;
//     print1(static_cast<Person *>(&s));
//     return 0;
// }

// class A
// {
// public:
//     void Print() { cout << "This is class A." << endl; }
//     //virtual void Print() { cout << "This is class A." << endl; }
// };

// class B : public A
// {
// public:
//     void Print() { cout << "This is class B." << endl; }
// };

// class C : public A
// {
// public:
//     void Print() { cout << "This is class C." << endl; }
// };

// void Handle(A* a)
// {
//     if (typeid(*a) == typeid(A))
//     {
//         cout << "I am a A truly." << endl;
//     }
//     else if (typeid(*a) == typeid(B))
//     {
//         cout << "I am a B truly." << endl;
//     }
//     else if (typeid(*a) == typeid(C))
//     {
//         cout << "I am a C truly." << endl;
//     }
//     else
//     {
//         cout << "I am alone." << endl;
//     }
// }

// int main()
// {
//     A* pA = new B();
//     Handle(pA);   // I am a B truly.
//     delete pA;
//     pA = new C(); // I am a C truly.
//     Handle(pA);
//     return 0;
// }

// int main()
// {
//     int a=211;
//     int b=985;
//     int c=535;
//     auto f=[=] {cout << "a: " << a << ", b: " << b << ", c: " << c << endl;};
//     f();
//     return 0;
// }