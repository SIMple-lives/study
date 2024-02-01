#include <iostream>
using namespace std;
#include <string>

//多继承语法
class Base1
{
    public:
    Base1()
    {
        m_A=100;
    }
    int m_A;
};

class Base2
{
    public:
    Base2()
    {
        m_A=200;
    }
    int m_A;
};

class Son :public Base1,public Base2
{
    public:
    Son()
    {
        m_C=300;
        m_D=400;
    }
    int m_C;
    int m_D;
};

void test()
{
    Son s;
    cout << sizeof(Son) << endl;
    cout << s.Base1::m_A << endl;
    cout << s.Base2::m_A << endl;
}

int main()
{
    test();
    return 0;
}

//继承中同名静态成员处理方式
// class Base
// {
// public:
//     static void func()
//     {
//         cout << "Base function" << endl;
//     }
//     static int m_A;
// };

// int Base :: m_A = 100;

// class Son :public Base
// {  
// public:
//     static void func()
//     {
//         cout << "Son function" << endl;
//     }
//     static int m_A;
// };

// int Son :: m_A = 200;

// void test()
// {
//     Son s;
//     cout << s.m_A << endl; 
//     cout << Son:: m_A << endl;
//     cout << Base ::m_A << endl;
//     cout << s.Base::m_A << endl;
//     cout << Son::Base::m_A << endl; 
// }

// void test01()
// {
//     Son s;
//     s.func();
//     s.Base::func();
//     Son ::func();
//     Son::Base::func();
// }

// int main()
// {
//     test01();
//     return 0;
// }

//继承中同名处理方式
// class Base
// {
//     public:
//     Base()
//     {
//         m_A = 100;
//     }
//     void func()
//     {
//         cout << "base函数的func调用" << endl;
//     }
//     void func(int a)
//     {
//         cout << "int a"<<endl;
//     }
//     int m_A;
// };

// class Son :public Base
// {
//     public:
//     Son()
//     {
//         m_A = 200;
//     }
//     void func()
//     {
//         cout << "Son的函数调用" <<endl;
//     }
//     int m_A;
// };

// // ostream& operator<<(ostream& os,  Son& s)
// // {
// //     os << s.m_A<<endl;
// //     return os;
// // }

// void test()
// {
//     Son s;
//     cout << s.m_A << endl;
//     cout << s.Base::m_A << endl;
// }
// //同名函数的处理方式
// void test01()
// {
//     Son s;
//     s.func();
//     s.Base::func(10);
// }

// int main()
// {
//     test01();
//     return 0;
// }

//继承子父类析构构造顺序
// class Base
// {
//     public:
//     Base()
//     {
//         cout << "Base" << endl;
//     }
//     ~Base()
//     {
//         cout << "Basexg" << endl;
//     }
// };

// class Son :public Base
// {
//     public:
//     Son()
//     {
//         cout << "Son" << endl;
//     }
//     ~Son()
//     {
//         cout << "Sonxg" << endl;
//     }
// };

// void test()
// {
//     Son s;
// }

// int main()
// {
//     test();
//     return 0;
// } 

// class Base
// {
// public:
//     int m_A;
// protected:
//     int m_B;
// private:
//     int m_C;
// };

// class Son :public Base
// {
// public:
//     int m_D;
// };

// int main()
// {
//     cout << sizeof(Son) << endl;
//     return 0;
// }

//继承方式
//公共继承
// class Base1
// {
// public:
//     int m_A;
// protected:
//     int m_B;
// private:
//     int m_C;
// };

// class Son1 : public Base1
// {
// public:
//     void func()
//     {
//         m_A = 10;
//         m_B = 10;
//         //m_C = 10;父类中的私有权限成员 子类访问不到
//     }
// };

// void test01()
// {
//     Son1 s1;
//     s1.m_A = 10;
//     s1.func();
//     cout << s1.m_A << endl;
//     //cout << s1.m_B << endl;保护权限，类外访问不到
// }

// class Base2
// {
// public:
//     int m_A;
// protected:
//     int m_B;
// private:
//     int m_C;
// };

// class Son2 :protected Base2
// {
// public:
//     void func()
//     {
//         m_A=10;
//         m_B=10;
//     }
// };

// void test02()
// {
//     Son2 s;
//     //s.m_A 也变为保护权限      全部访问不到
//     s.func();
// }

// class Base3
// {
// public:
//     int m_A;
// protected:
//     int m_B;
// private:
//     int m_C;
// };

// class Son3 :private Base3
// {
// public: 
//     void func()
//     {
//         m_A=10;
//     }
// };

// void test03()
// {
//     Son3 s;
//     //s.m_A=20;父类中的全部成员变为私有成员，类外访问不到
// }

//继承
// class BasePage
// {
// public:
//     void header()
//     {
//         cout << "首页、公开课、登陆、注册（公共头部）" << endl;
//     }
//     void footer()
//     {
//         cout << "帮助中心、交流合作、站内地图、（公共底部）" << endl;
//     }
//     void left()
//     {
//             cout << "公共分类列表" << endl;
//     }
// };

// class Java: public BasePage
// {
// public:
//     void content()
//     {
//         cout << "java" << endl;
//     }
// };

// class Python : public BasePage
// {
// public:
//     void content()
//     {
//         cout << "phthon" << endl;
//     }
// };

// void test()
// {
//     Java J;
//     J.header();
//     J.left();
//     J.content();
//     J.footer();
//     Python P;
//     P.header();
//     P.left();
//     P.content();
//     P.footer();
// }

// int main()
// {
//     test();
//     return 0;
// }

// class Java
// {
// public:
//     void header()
//     {
//         cout << "公共头部" <<endl;
//     }
//     void footer()
//     {
//         cout << "公共尾部" << endl;
//     }
//     void left() 
//     {
//         cout << "连接"<<endl;
//     }
//     void content()
//     {
//         cout << "java"<<endl;
//     }
// };

// class PYthon
// {
// public:
//     void header()
//     {
//         cout << "公共头部" <<endl;
//     }
//     void footer()
//     {
//         cout << "公共尾部" << endl;
//     }
//     void left() 
//     {
//         cout << "连接"<<endl;
//     }
//     void content()
//     {
//         cout << "Python"<<endl;
//     }
// };

// void test()
// {
//     cout << "java下载视频" << endl;
//     Java j;
//     j.header();
//     j.footer();
//     j.left();
//     j.content();
//     PYthon p;
//     p.content();
//     p.footer();
//     p.header();
//     p.left();
// }

// int main()
// {
//     test();
//     return 0;
// }
