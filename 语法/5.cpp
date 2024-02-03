#include <iostream>
using namespace std;
#include <string>

//案例三
//抽象组件
class CPU
{
public:
    virtual void calculate() = 0;
};

class VideoCard 
{
public:
    virtual void display() = 0;
};

class Memory
{
public:
    virtual void storage() = 0;
};

//电脑
class Computer
{
public:
    Computer(CPU *cpu,VideoCard *vc ,Memory *mem)
    {
        m_mem = mem;
        m_vc = vc;
        m_cpu=cpu;     
    }
    void work()
    {
        m_cpu->calculate();
        m_vc->display();
        m_mem->storage();
    }
    ~Computer() 
    {
        if(m_cpu != NULL)
        {
            delete m_cpu;
            m_cpu = NULL;
        }
        if(m_vc != NULL)
        {
            delete m_vc;
            m_vc = NULL;
        }
        if(m_mem != NULL)
        {
            delete m_mem;
            m_mem = NULL;
        }
    }
private:
    CPU * m_cpu;
    VideoCard *m_vc;
    Memory *m_mem;
};

//厂商实现
class Intelcpu:public CPU
{
    virtual void calculate() 
    {
        cout << "Intel CPU Start" << endl;
    }
};

class IntelVideocard:public VideoCard
{
    virtual void display() 
    {
        cout << "Intel Videocard Start" << endl;
    }
};

class IntelMemory:public Memory
{
    virtual void storage() 
    {
        cout << "Intel Memory Start" << endl;
    }
};

class Lenovocpu:public CPU
{
    virtual void calculate() 
    {
        cout << "Lenovo CPU Start" << endl;
    }
};

class LenovoVideocard:public VideoCard
{
    virtual void display() 
    {
        cout << "Lenovo Videocard Start" << endl;
    }
};

class LenovoMemory:public Memory
{
    virtual void storage() 
    {
        cout << "Lenovo Memory Start" << endl;
    }
};

void test()
{
    CPU * intelcpu=new Intelcpu;
    VideoCard * intelvideocard=new IntelVideocard;
    Memory * intelmemory=new IntelMemory;
    Computer * first= new Computer(intelcpu,intelvideocard,intelmemory);
    first->work();
    delete first;
    cout << "-----------------------" << endl;
    Computer * second= new Computer(new Lenovocpu,new LenovoVideocard,new LenovoMemory);
    second->work();
    delete second;
}

int main()
{
    test();
    return 0;
}

//虚析构和纯虚析构
// class Animal
// {
// public:
//     Animal()
//     {
//         cout << "Animal的构造函数" << endl;
//     }
//     // virtual ~Animal() //利用虚析构可以解决 父类指针释放子类对象时的不干净的问题
//     // {
//     //     cout << "Animal的析构函数" << endl;
//     // }
//     //需要声明 ，也需要实现
//     virtual ~Animal () = 0;
//     virtual void speak()=0;
// };

// Animal :: ~Animal()
// {
//     cout << "Animal的纯虚析构" << endl;
// }

// class Cat : public Animal
// {
// public:
//     Cat(string name)
//     {
//         cout << "cat的构造函数" << endl;
//         m_Name = new string(name);
//     }
//     virtual void speak()
//     {
//         cout << *m_Name << "Cat Speaking" << endl;
//     }
//     ~Cat()
//     {
//         if(m_Name!=NULL)
//         {
//             cout << "cat的析构函数调用" << endl;
//             delete m_Name;
//             m_Name = NULL;
//         } 
//     }
//     string *m_Name;
// };

// void test01()
// {
//     Animal *a = new Cat("Tom ");
//     a->speak();
//     //父类指针在析构的时候 ，不会调用子类中的析构函数 ，导致子类如果有属性在堆区的话 ，出现了内存泄漏
//     delete a;
// }

// int main()
// {
//     test01();
//     return 0;
// }

//案例二 
//利用多态案例 ，提供抽象制作饮料基类，提供子类制作

// class AbstractDrinking
// {
// public:
//     virtual void Bool( ) = 0;
//     virtual void Brew( ) = 0;
//     virtual void PourInCup( ) = 0;
//     virtual void PutSomething( ) = 0;
//     void makeDrinking()
//     {
//         Bool( );
//         Brew( );
//         PourInCup();
//         PutSomething( );
//     }
// };

// class coffee :public AbstractDrinking
// {
//     virtual void Bool( ) 
//     {
//         cout << "Coffeewater" << endl;
//     }
//     virtual void Brew( ) 
//     {
//         cout << "冲泡咖啡" <<endl;
//     }
//     virtual void PourInCup( ) 
//     {
//         cout << "倒入杯中" << endl;
//     }
//     virtual void PutSomething( )
//     {
//         cout << "Put something" << endl;
//     }
// };

// class Tea :public AbstractDrinking
// {
//     virtual void Bool( ) 
//     {
//         cout << "Teawater" << endl;
//     }
//     virtual void Brew( ) 
//     {
//         cout << "茶叶咖啡" <<endl;
//     }
//     virtual void PourInCup( ) 
//     {
//         cout << "倒入杯中" << endl;
//     }
//     virtual void PutSomething( )
//     {
//         cout << "Put something" << endl;
//     }
// };

// void test()
// {
//     AbstractDrinking * a=new coffee;
//     a->makeDrinking();
//     delete a;
//     a=new Tea;
//     a->makeDrinking();
//     delete a; 
// }

// int main()
// {
//     test();
//     return 0;
// }

//纯虚函数和抽象类
// class Base
// {
// public:
//     //纯虚函数
//     //只要有一个纯虚函数，这个类称为抽象类
//     //特点：无法实例化对象      抽象类的子类  必须要重写父类中的纯虚函数，否则也属于抽象类
//     virtual void func() = 0 ;
// };

// class Son : public Base
// {
// public:
//     virtual void func()
//     {
//         cout << "实现函数" << endl;
//     }
// };

// void test()
// {
//     //Base b;
//     //new Base;无法实例化对象
//     Son s;//子类必须重写纯虚函数
//     s.func();
// }
 
// int main()
// {
//     test();
//     return 0;
// }

//多态案例  计算器类

// class AbstractCalculator
// {
// public:
//     virtual int getResult()
//     {
//         return 0;
//     }
//     int m_Num1;
//     int m_Num2;
// };

// class Addcalculator : public AbstractCalculator
// {
// public:
//     int getResult()
//     {
//         return m_Num1 + m_Num2;
//     }
// };

// class Subcalculator : public AbstractCalculator
// {
// public:
//     int getResult()
//     {
//         return m_Num1 - m_Num2;
//     }
// };

// class mulcalculator : public AbstractCalculator
// {
// public:
//     int getResult()
//     {
//         return m_Num1 * m_Num2;
//     }
// };

// class Divcalculator : public AbstractCalculator
// {
// public:
//     int getResult()
//     {
//         return m_Num1/m_Num2;
//     }
// };

// void test()
// {
//     AbstractCalculator * abc=new Addcalculator;
//     abc->m_Num1=10;
//     abc->m_Num2=10;
//     cout << abc->getResult() << endl;
//     //用完后记得销毁
//     delete abc;
//     abc=new Subcalculator;
//     abc->m_Num1=10;
//     abc->m_Num2=10;
//     cout << abc->getResult() << endl;
//     delete abc;
//     abc=new mulcalculator;
//     abc->m_Num1=10;
//     abc->m_Num2=10;
//     cout << abc->getResult() << endl;
//     delete abc;
//     abc=new Divcalculator;
//     abc->m_Num1=10;
//     abc->m_Num2=10;
//     cout << abc->getResult() << endl;
//     delete abc;
// }

// int main()
// {
//     test();
//     return 0;
// }

// class Calculator
// {
// public:
//     int getResult(string oper)
//     {
//         if(oper == "+")
//         {
//             return m_num1+m_num2;
//         }
//         else if(oper == "-")
//         {
//             return m_num1-m_num2;
//         }
//         else if(oper == "*")
//         {
//             return m_num1*m_num2;
//         }
//         //如果真想拓展，需要修改源码
//         //在真实开发中 提倡开闭原则
//         //开闭原则：对拓展进行开放，对修改进行关闭。
//     }
//     int m_num1;
//     int m_num2;
// };

// void test01()
// {
//     Calculator c;
//     c.m_num1 = 10;
//     c.m_num2 = 10;
//     cout << c.getResult("+") << endl;
//     cout << c.getResult("-") << endl;
//     cout << c.getResult("*") << endl;
// }

// int main()
// {
//     test01();
//     return 0;
// }

//原理剖析
// class Animal
// {
//     public:
//     virtual void speak()
//     {
//         cout << "Animal" << endl;
//     }
// };

// class Cat :public Animal
// {
//     public:
//     void speak()
//     {
//         cout << "Cat" << endl;
//     }
// };

// class Dog :public Animal
// {
//     public:
//     void speak()
//     {
//         cout << "Dog" << endl;
//     }
// };

// void dospeak(Animal &j)
// {
//     j.speak();
// }

// void test()
// {
//     Cat C;
//     dospeak(C);
//     Dog D;
//     dospeak(D);
// }

// void test02()
// {
//     cout << sizeof(Animal) <<endl;//只有一个非静态的成员函数，所以类似于一个空类，所以为1
// }

// int main()
// {
//     test();
//     test02();
//     return 0;
// }

//多态
// class Animal
// {
//     public:
//     virtual void speak()
//     {
//         cout << "Animal" << endl;
//     }
// };

// class Cat :public Animal
// {
//     public:
//     void speak()
//     {
//         cout << "Cat" << endl;
//     }
// };

// class Dog :public Animal
// {
//     public:
//     void speak()
//     {
//         cout << "Dog" << endl;
//     }
// };

// void dospeak(Animal &j)
// {
//     j.speak();
// }

// void test()
// {
//     Cat C;
//     dospeak(C);
//     Dog D;
//     dospeak(D);
// }

// int main()
// {
//     test();
//     return 0;
// }

// class Animal
// {
// public:
//     int m_Age;
// };
// //利用虚继承  解决菱形继承问题
// //继承之前加上virtual 变为虚继承
// //Animal类称为 虚基类
// class Sheep : virtual public Animal{};
// class Tuo : virtual public Animal{};
// class SheepTuo :public Sheep,public Tuo{};

// void test01()
// {
//     Sheep T;
//     T.m_Age = 1;
//     cout << T.m_Age << endl;
//     SheepTuo st;
//     st.Sheep::m_Age = 18;
//     st.Tuo::m_Age = 28;
//     cout << st.Sheep::m_Age << endl;
//     cout << st.Tuo::m_Age << endl;
//     cout << st.m_Age << endl;
// }

// int main()
// {
//     test01();
//     return 0;
// }