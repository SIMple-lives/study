---
title: C++ 初始
---
## 1.编写C++程序步骤

* 创建项目
* 创建文件 
* 编写代码
* 运行程序

## 1.3变量

**作用**：给一段指定的内存空间起名，方便操作这段内存

**语法**：数据类型 变量名 =初始值

## 1.5关键字

预先保留的单词

在定义变量或者常量的时候，不要用关键字

![image-20240126134407666](/home/future/.config/Typora/typora-user-images/image-20240126134407666.png)

## 标识符命名规则

* 标识符不能是关键字

* 标识符只能由字母，数字，下划线组成

* 第一个字符必须为字母或者下划线

* 标识符中区分大小写

  > 给标识符命名时，争取做到见名知意的效果，方便阅读

## 数据类型

### 实型

![image-20240126141803008](/home/future/.config/Typora/typora-user-images/image-20240126141803008.png)

也可以用科学计数法表示.

### 字符型

![image-20240126141934528](/home/future/.config/Typora/typora-user-images/image-20240126141934528.png)

![image-20240126143210223](/home/future/.config/Typora/typora-user-images/image-20240126143210223.png)

## 字符串型

```c++
//c风格的字符串
char str[]="helloworld";
//c++风格的字符串
//要包含头文件
string str="helloworld";
```

## 布尔类型

本质上1代表真，0代表假

占一个字节.

## 数据的输入

### 关键字cin

![image-20240126153759842](/home/future/.config/Typora/typora-user-images/image-20240126153759842.png)

***

**小数间是不能做取模运算的**

## 程序流程结构

![image-20240126161658969](/home/future/.config/Typora/typora-user-images/image-20240126161658969.png)

## 跳转语句

![image-20240126185118480](/home/future/.config/Typora/typora-user-images/image-20240126185118480.png)

 

![image-20240126190028482](/home/future/.config/Typora/typora-user-images/image-20240126190028482.png)

 ## 数组

## 函数

**作用**：将一段经常使用的代码封装起来，减少重复的代码

![image-20240126195613509](/home/future/.config/Typora/typora-user-images/image-20240126195613509.png)

 

## 指针

![image-20240126204357351](/home/future/.config/Typora/typora-user-images/image-20240126204357351.png)

## 结构体

# 核心编程

## 内存分区模型

* 代码区  存放CPU执行的机器指令   **共享** **只读** 

* 全局区  

  ![image-20240129161914846](/home/future/.config/Typora/typora-user-images/image-20240129161914846.png)

* 栈区

  > 不要返回局部变量的地址

* 堆区

  > 在c++中主要利用new在堆区开辟内存

**意义**：不同区域存放的数据，赋予不同的生命周期，给我们更大的灵活编程

### 堆区

![image-20240129163348833](/home/future/.config/Typora/typora-user-images/image-20240129163348833.png)

new的基本语法

# 引用

**作用**：给变量起别名

**语法**：数据类型  &别名 =原名

## 注意事项

* 引用必须要初始化
* 引用一旦初始化后，就不可以更改 

引用可以简化指针的用法.	

![image-20240129175346070](/home/future/.config/Typora/typora-user-images/image-20240129175346070.png)

通过引用参数产生的效果按地址传递是一样的。引用的语法更加的简单。

引用是可以作为函数的返回值存在的.

不返回局部变量的引用. 	

函数的调用可以作为**左值.**

![image-20240129192841197](/home/future/.config/Typora/typora-user-images/image-20240129192841197.png)

**本质**：引用的本质在c++内部实现是一个指针常量.

![image-20240129193443168](/home/future/.config/Typora/typora-user-images/image-20240129193443168.png)

引用必须引一块合法的内存空间。

const修饰的局部变量不再全局区.

## 函数

## 函数默认参数

在c++中，函数的形参列表中的形参是可以有默认值的

**语法** ：返回值类型  函数名 （参数= 默认值） {}

![image-20240129194847742](/home/future/.config/Typora/typora-user-images/image-20240129194847742.png)

函数的默认参数，如果我们传入了参数，值就使用我们传入的参数，如果我们没有传入参数，那么就使用函数的默认参数值

**注意事项：**

* 如果某个位置已经有了默认参数，那么这个位置往后，从左到右都必须要有默认值
* 如果函数声明有默认参数，函数实现就不能有默认参数
* 声明和实现只能一个有默认参数

## 函数占位参数

c++中的函数的形参列表可以有占位参数，用来做占位，调用函数时必须填补该位置

语法：返回值类型 函数名 （数据类型） { }

目前占位参数我们还用不到.

占位参数还可以有默认参数.

## 函数重载

**作用：**函数名可以相同，提高复用性

### 满足条件

* 同一个作用域下
* 函数名称相同
* 函数参数类型不同 或者 个数不同 或者顺序不同

**注意事项：**

* 函数的返回值不可以作为函数重载的条件

* 引用作为重载的条件

  ```c++
  void fun(int &a)//这两个可以作为函数重载的条件，因为函数的参数类型不同
  {
      cout << "func(int &a)调用" <<endl;
  }
  
  void fun(const int &a)
  {
      cout << "func(const int &a)调用"<<endl;
  }
  
  int main()
  {
   	int a=10;
      func(a);//调用的是第一个，因为这是一个变量.
      int func(10);//调用的是第二个。
      return 0;
  }
  ```

* 函数重载碰到默认参数(会出现二义性，尽量避免使用)

  ```c++
  void func2(int a)
  {
      cout << "func2(int a)的调用" <<endl;
  }
  
  void func2(int a,int b=10)
  {
      cout << "func2(int a,int b)的调用" <<endl;
  }
  
  int main()
  {
     	func2(10);
      return 0;
  }
  ```

  

# 类和对象

c++面向对象的三大特性为：封装、继承、多态

c++认为万事万物都皆为对象，对象上有其属性和行为

具有相同性质的对象，我们可以抽象称为类，人属于人类，车属于车类

## 封装

### 意义

封装是c++面向对象的三大特性之一

* 将属性和行为作为一个整体，表现生活中的事物
* 将属性和行为加以权限控制

封装意义1：

在设计类的时候，属性和行为写在一起，表示事物

语法：class 类名 {   访问权限 ：   属性 /行为  }；

```c++
const double PI =3.14;
class Circle 
{
    //访问权限
public:
    //圆的属性
    int m_r;
    //行为
    //获取周长
    double calculateZC()
    {
        return 2*PI*m_r;
	}
}

int main()
{
	//通过圆类 创建具体的圆（对象）
    //实例化(通过一个类  创建一个对象的过程) 
    Circle c1;
    //给圆对像的属性进行赋值、
    c1.m_r=10 ;
    cout << c1.calculateZC()<<endl;
    return 0;
}
```

 

```c++
class Student//设计学生类
{
    public ://公共权限
    //类中的属性和行为  我们统称为 成员
    //属性 也成为 成员属性 成员变量
    //行为 也称为 成员函数 成员方法
    //属性 
    string m_Name;
    int m_Id;
    //行为
    void show()
    {
        cout<<"姓名：  " << m_Name << "学号 :" << m_Id<<endl;
    }
    void set_name(string name)
    {
        m_Name=name;
	}
    void set_Id(int id)
    {
        m_Id=id;
    }
}

int main()
{
    Student s1;
    cin>>s1.m_Name>>m_Id;
    s1.show();
    Student s1;
    s2.set_name("张三");
    s2.set_Id(1);
    return 0;
}
```

封装意义二：

类在设计时，可以把属性和行为放在不同的权限下，加以控制

三种权限：

1.public		 公共权限

2.protected	  保护权限

3.private		私有权限	

```c++
//访问权限 三种
//公共权限	public			成员 类内可以访问 类外也可以访问
//保护权限	protected		成员 类内可以访问 类外不可以访问
//私有权限	private			成员 类内可以访问 类外不可以访问
//私有权限与保护权限的区别 在继承的时候可以区分 儿子可以访问父亲中的保护内容
//儿子不可以访问父亲的私有内容
class Person
{
public:
	string m_Name;
protected:
    string m_Car;
private:
    int m_Password;
public:
    void func()
    {
        m_Name="张三";
        m_Car="饿狼传说"；
        m_Password=123145;
	}
};

```

## class 和 struct 的区别

在c++中struct 和 class  唯一的区别就在于默认的访问权限不同

**区别：**

* struct	默认权限为**公共**
* class          默认权限为**私有**

## 成员属性设置为私有

**优点**：

* 将所有成员属性设置为私有，可以自己控制读写权限
* 由于写权限，我们可以检测数据的有效性

**在类中可以让另外一个类作为类中本来的成员**

```c++
class Point
{
    public:
    //在此实现成员函数
    private:
    int m_X;
    int m_Y;
}
class circle
{
    public:
    //在此实现成员函数
    private:
    int m_R;
    Point m_Center;
}
```

```c++
//在头文件中可以进行类的声明
class Point
{
    public:
    void setx(int x);
    void sety(int y);
    private:
    int m_X;
    int m_Y;
}

class Circle
{
    public:
    void setm_R(int r);
    int getr();
    private:
    int m_R;
    Point Center;
}
//在其余的文件定义该函数的时候需要加作用域
void Point:: setx(int x)
{
    m_X=x;
}
```

## 对象的初始化清理

c++中的面向对象来源于生活 ，每个对象也都会有初始设置 以及对象销毁前的清理数据的设置。

### 构造函数和析构函数

![image-20240130143257455](/home/future/.config/Typora/typora-user-images/image-20240130143257455.png)

![image-20240130143539381](/home/future/.config/Typora/typora-user-images/image-20240130143539381.png)

**构造函数的分类及调用：**

* 按参数
  * 有参构造
  * 无参构造

* 按类型
  * 普通构造
  * 拷贝构造

三种调用方法：  

* 括号法

  ```c++
  Person P;//默认构造时后面不要加括号
  Person p1(10);
  Person p2(p1);
  ```

* 显示法

  ```c++
  Person p;
  Person p1=Person(10);
  Person P2=Person(p2);
  ```

* 隐式转换法

  ```c++
  Person p4=10;
  Person p5=p4;
  ```

**构造函数的调用顺序**:

> 1.当普通构造一个对象时，程序先自动调用默认构造函数分配空间，在调用自定义构造函数(如果有的话)
>
> 2.当拷贝构造一个对象时，程序先自动调用默认构造函数分配空间，然后分两种情况，如果程序有自定义拷贝函数，则调用自定义拷贝构造函数；如果没有，就调用默认拷贝构造函数进行浅拷贝.

### 拷贝构造函数调用时机

c++拷贝构造函数调用时机

* 使用一个创建完毕的对象来初始化一个新对象
* 值传递的方式给函数参数传值(做参数)
* 以值的方式返回局部对象(做返回值) 

### 构造函数调用规则

默认情况下，c++编译器至少给一个类添加3个函数

1.默认构造参数（无参，函数体为空）

2.默认析构函数（无参，函数体为空）

3.默认拷贝构造函数，对属性值进行拷贝



**规则如下：**

* 如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造
* 如果用户定义拷贝构造函数，c++不会在提供其他的构造函数

### 深拷贝与浅拷贝

浅拷贝：简单的赋值操作

深拷贝：在堆区重新申请空间，进行拷贝操作

```c++
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
    cout << *p2.m_height <<endl;//会发生错误，因为p2是浅拷贝，但析构函数内部对p2进行了释放
}			

int main()
{
    test01();
    return 0;
}
```

  ![image-20240130162328490](/home/future/.config/Typora/typora-user-images/image-20240130162328490.png)

![image-20240130162226901](/home/future/.config/Typora/typora-user-images/image-20240130162226901.png)

所以需要深拷贝来解决该问题，自己实现拷贝构造函数

### 初始化列表

**作用**：c++提供了初始化列表语法，用来初始化（类的）属性

![image-20240130193845123](/home/future/.config/Typora/typora-user-images/image-20240130193845123.png)

```c++
class Person
{
public:
    //Person(int a,int b,int c)
    //{
    //		m_A=a;m_B=b;m_C=c;
	//}
    Person(int a,int b,int c):m_A(a),m_B(b),m_C(c)
    {
        
    }
    int m_A;
    int m_B;
    int m_C;
}
void test
{
    Person p;
}

int main()
{
    test();
    return 0;
}
```

**初始化const成员变量的唯一方法就是使用初始化列表**

### 类对象作为类成员

c++类中的成员可以是另一个类的对象，我们称该成员为对象成员

```c++
class A{}
class B
{
    A a;
}//B类中有对象A作为成员，A为对象成员
```

那么当创建B对象时，A与B的构造和析构的顺序是谁先谁后？

先构造A对象.

当其他类的对象作为本类成员，构造时先构造**类对象**，在构造**自身.**

先析构B对象

析构时先析构自身，在析构类对象.

### 静态成员

静态成员就是在成员变量和成员函数前加上关键字static，成为静态成员

* 静态成员变量
  * 所有对象共享同一份数据
  * 在编译阶段分配内存
  * 类内声明，类外初始化

* 静态成员函数
  * 所有对象共享一个函数
  * 静态成员函数只能访问静态成员变量,不可以访问非静态成员变量
    * 无法区分到底是哪一个对象的属性
    * 也是有访问权限的

```c++
class Person
{
Public:
    static int m_A;
}

int Person:: m_A=100;

void test()
{
	Person P;
    cout << P.m_A <<endl;//100
    Person p2;
    p2.m_A=200;
    cout << P.m_A <<endl;//200
}

void test02()
{
    cout <<Person :: m_A <<endl;
}
```

```c++
class Person
{
public:
    static void func()
    {
        cout << "static" << endl; 
    }
};

void test()
{
   Person ::func();
}

int main()
{
    test();
    return 0;
}
```

## c++对象模型和this指针

### 成员变量和成员函数分开存储

类的成员变量和成员函数分开存储

只有非静态成员变量才属于类的对象上

空对象的大小为1

c++编译器会给每一个空对象分配一个字节空间，是为了空对象占内存的位置.

每个空对象有一个独一无二的内存地址

### this指针概念

每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码

那么问题是：这一块代码是如何区分那个对象调用自己的呢?

c++通过提供特殊的对象指针，this指针，解决上述问题.this指针指向被调用的成员函数所属的对象。



this指针是**隐含**每一个**非静态**的成员函数内的一种**指针**

this指针不需要定义，直接使用即可

**用途**：

* 当形参和成员变量名同名时，可用this指针来区分
* 在类的非静态成员函数中返回对象本身，可使用return *this

```c++
class Person
{
public:
    Person(int age)
    {
        //解决名称冲突
        this->age = age;
    }
    Person& PersonAddage(Person &P)//要返回引用， 如果返回的是Person的值话，返回的是对p2的一份拷贝
    {
        this->age += P.age;
        return *this;//返回*this
    }
    int age;
};

void test01()
{
    Person p1(18);
    cout << p1.age << endl;
}

void test02()//链式编程思想
{
    Person p1(10);
    Person p2(10);
    p2.PersonAddage(p1).PersonAddage(p1).PersonAddage(p1);
    cout << p2.age <<endl;
}

int main()
{
    test02();
    return 0;
}
```

### 空指针访问成员函数

c++中空指针也是可以调用成员函数的，但是也要注意有没有用到this指针	

对this判空有助于提高代码的健壮性

```c++
class Person
{
public:
    void showClassName()
    {
        cout << "Person" << endl;
    }
    void showPersonAge()
    {
        //报错原因是因为传入的指针是为NULL空的
        if(this==NULL) return;
        cout << "age=" << m_Age << endl;
    }
    int m_Age;
};

void test01()
{
    Person *P=NULL; 
    P->showClassName();
    // P->showPersonAge();
}

int main()
{
    test01();
    return 0;
}
```

### const修饰成员函数

常函数：

* 成员函数后加const后我们称这个函数为常函数
* 常函数内不可以修改成员属性
* 成员属性声明时加关键字mutable后，在常函数中依然可以修改

常对象：

* 声明对象前加const称该对象为常对象
* 常对象只能调用常函数
  * 普通成员函数可以修改属性

![image-20240131112417975](/home/future/.config/Typora/typora-user-images/image-20240131112417975.png)

在成员函数后面加const，修饰的是this指向，让指针指向的值也不可以修改.

### 友元

在程序里，有些私有属性，也想让类外特殊的一些函数或者类进行访问，就需要用到友元的技术	

友元的目的就是一个函数或者类 访问另一个类中私有成员

**友元的关键字**：friend

友元的三种实现 

* 全局函数做友元

  ```c++
  class Building
  {
      //goodGay全局函数是 BUilding好朋友 ，可以访问Building中私有成员
      friend void goodGay(Building &building);
  public:
      Building()
      {
          m_SittingRoom ="客厅";
          m_BedRoom = "卧室";
      }
  public:
      string m_SittingRoom;
  private:
      string m_BedRoom;
  };
  
  void goodGay(Building &building)
  {
      cout << building.m_SittingRoom << endl;
      cout << building.m_BedRoom << endl;
  }
  
  void test01()
  {
      Building building;
      goodGay(building);
  }	
  ```

* 类做友元

  ```c++
  class Building
  {
      //goodGay类是本类的好朋友，可以访问本类中的私有成员
      friend class goodGay;
  public:
      Building();
  public:
      string m_SittingRoom;
  private:
      string m_BedRoom;
  };
  
  
  class goodGay
  {
      public:
      goodGay();
      void visit();//参观函数访问Building中的属性
      Building *building;
  };
  
  goodGay::goodGay()
  {
      building = new Building;
  }
  
  void goodGay:: visit()
  {
      cout<<building->m_SittingRoom<<endl;
      cout<<building->m_BedRoom<<endl;
  }
  
  
  //类外去写成员函数
  Building::Building()
  {
      m_SittingRoom = "客厅";
      m_BedRoom = "卧室";
  }  
  
  void test01()
  {
      goodGay g;
      g.visit();
  }
  ```

* 成员函数做友元

  ```c++
  class Building;
  
  class goodGay 
  {
  public:
      goodGay();
      void visit1();//visit可以访问私有成员
      void visit2();//不可以访问私有成员
      Building *building;
  };
  
  class Building
  {
      friend void goodGay::visit1();
  public:
      Building();
  public:
      string m_SettingRoom;
  private:
      string m_BedRoom;
  };
  
  Building :: Building()
  {
      m_SettingRoom = "客厅";
      m_BedRoom = "卧室";
  }
  goodGay :: goodGay()
  {
      building = new Building;
  }
  
  void goodGay :: visit1()
  {
      cout << "Building " << building->m_SettingRoom <<endl;
      cout << "Building " << building->m_BedRoom <<endl;
  }
  
  void goodGay :: visit2()
  {
      cout << "Building " << building->m_SettingRoom <<endl;
  }
  
  void test()
  {
      goodGay g;
      g.visit1();
      g.visit2();
  }
  ```

  

## 运算符重载

元算符重载概念：对已有的运算符重新进行定义，赋予其另外一种功能，以适应不同的数据类型

### 加号运算符重载

作用：实现两个自定义数据类型相加的运算

```c++
Person p3=p1.operator+(p2);
简化为
Person p3=p1+p2;
class Person
{
public:
    // Person operator+(Person &p)
    // {
    //     Person temp;
    //     temp.m_A=this->m_A+p.m_A;
    //     temp.m_B=this->m_B+p.m_B;
    //     return temp;
    // }
    //本质上的调用是 Person p3=p1.operator+(p2);
    int m_A;
    int m_B;
};

Person operator+(Person &p1,Person &p2)//本质上调用是Person p3=operator+(p2,p1);
{
    Person temp;
    temp.m_A=p1.m_A+p2.m_A;
    temp.m_B=p1.m_B+p2.m_B;
    return temp;
}

void test()
{
    Person p1;
    p1.m_A = 10;
    p1.m_B = 10;
    Person p2;
    p2.m_A = 10;
    p2.m_B = 10;
    Person p3=p1+p2;
    cout << p3.m_A << endl;
    cout << p3.m_B << endl;
}

```

![image-20240131182219790](/home/future/.config/Typora/typora-user-images/image-20240131182219790.png)

**运算符重载也可以发生函数重载.**

总结：

* 对于内置的数据类型的表达式的运算符是不可能改变的
* 不要滥用运算符重载

### 左移运算符重载

可以输出自定义的数据类型

![image-20240131185118381](/home/future/.config/Typora/typora-user-images/image-20240131185118381.png)

通常不会利用成员函数重载<<运算符，因为无法实现cout在左侧

```c++
class Person
{
public:
    // 通常不会利用成员函数重载<<运算符，因为无法实现cout在左侧
    // void operator<<()
    // {
    // }
    int m_A;
    int m_B;
};

//只能全局函数来重载左移运算符
ostream& operator<<(ostream &cout,Person &p)
{  
    cout << "m_A=" << p.m_A <<endl;
    cout << "m_B=" << p.m_B <<endl;
    return cout;
}

void test()
{
    Person p;
    p.m_A = 10;
    p.m_B = 10;
    cout << p<<endl;
    cout << p.m_A << " " << p.m_B << endl;
}
```

> 重载左移运算符可以配合友元实现输出自定义数据类型

### 递增运算符重载

作用：通过重载运算符，实现自己的整形数据

```c++
class MyIntegar
{
    friend ostream& operator<<(ostream& os,  MyIntegar s);
public:
    MyIntegar()
    {
        m_Num = 0;
    }
    //重载前置++运算符
    MyIntegar& operator++()
    {
        m_Num++;
        return *this;
    }
    MyIntegar operator++(int)//int代表占位参数，可以用于区分前置和后置递增
    {
        MyIntegar temp=*this;
        this->m_Num++;
        return temp;
    }
private:
    int m_Num;
};

ostream& operator<<(ostream& os,  MyIntegar s)
{
    os << s.m_Num ;
    return os;
}

void test()
{
    MyIntegar myint;
    cout << ++(++myint)<<endl; 
    cout << myint << endl;
}

void test2()
{
    MyIntegar myint;
    cout << myint++<<endl; 
    cout << myint << endl;
}
```

### 赋值运算符重载

c++编译器至少给一个类添加4个函数

1.默认构造函数(无参，函数体为空)

2.默认析构函数(无参，函数体为空)

3.默认拷贝构造函数，对属性进行值拷贝

4.赋值运算符 operator=,对属性进行值拷贝

如果类中有属性指向堆区，做赋值操作时也会出现深浅拷贝问题

```c++
class Person
{
public:
    Person(int age)
    {
        m_Age = new int(age);
    }
    Person& operator=(Person &p)
    {
        //应该先判断是否有属性在堆区，如果有先释放干净，然后在深拷贝
        if(m_Age !=NULL)
        {
            delete m_Age;
        }
        m_Age= new int(*(p.m_Age));
        return *this;
    }
    ~Person()
    {
        if(m_Age!=NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }
    }
    int *m_Age;
};

void test()
{
    Person p1(18);
    Person p2(20);
    Person p3(30);
    p3=p2=p1;
    cout << *p1.m_Age << endl;
    cout << *p2.m_Age << endl;
    cout << *p3.m_Age << endl;
}   
```

### 关系运算符重载

作用：重载关系运算符，可以让两个自定义类型对象进行对比操作

```c++
class Person
{
public:
    Person(string name,int age)
    {
        m_Name=name;
        m_Age=age;
    }
    bool operator==(Person &P)
    {
        if(this->m_Name==P.m_Name && this->m_Age==P.m_Age)
        {
            return true;
        }
        return false;
    } 
     bool operator!=(Person &P)
    {
        if(this->m_Name==P.m_Name && this->m_Age==P.m_Age)
        {
            return false;
        }
        return true;
    } 
    string m_Name;
    int m_Age;
};

void test()
{
    Person p1("John",18);
    Person p2("John",18);
    if(p1 == p2)
    {
        cout << "p1==p2" << endl;
    }
    else
    {
        cout << "p1!=p2" << endl;
    }
}
```

### 函数调用运算符重载

* 函数调用运算符()也可以重载
* 由于重载后使用的方式非常像函数的调用，因此称为仿函数
* 仿函数没有固定写法，非常灵活

```c++
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
}
```

![image-20240131212420250](/home/future/.config/Typora/typora-user-images/image-20240131212420250.png)

## 继承

继承是面向对象的三大特性之一

![image-20240201183224645](/home/future/.config/Typora/typora-user-images/image-20240201183224645.png)

我们发现，定义这些类的时候，下级别的成员除了拥有上一级的共性，还有自己的特性。

这个时候考虑利用继承技术，减少代码重复。

### 基本语法

> 		class  子类 ： 继承方式  父类
> 			
> 		子类   也称为  派生类
> 			
> 		父类   也称为   基类

```c++
class BasePage
{
public:
    void header()
    {
        cout << "首页、公开课、登陆、注册（公共头部）" << endl;
    }
    void footer()
    {
        cout << "帮助中心、交流合作、站内地图、（公共底部）" << endl;
    }
    void left()
    {
            cout << "公共分类列表" << endl;
    }
};

class Java: public BasePage
{
public:
    void content()
    {
        cout << "java" << endl;
    }
};

class Python : public BasePage
{
public:
    void content()
    {
        cout << "phthon" << endl;
    }
};

```

**好处：减少重复代码。**

### 继承方式

一共有三种：

* 公共继承

  ```c++
  class Base1
  {
  public:
      int m_A;
  protected:
      int m_B;
  private:
      int m_C;
  };
  
  class Son1 : public Base1
  {
  public:
      void func()
      {
          m_A = 10;
          m_B = 10;
          //m_C = 10;父类中的私有权限成员 子类访问不到
      }
  };
  ```

* 保护继承

  ```c++
  class Base2
  {
  public:
      int m_A;
  protected:
      int m_B;
  private:
      int m_C;
  };
  
  class Son2 :protected Base2
  {
  public:
      void func()
      {
          m_A=10;
          m_B=10;
      }
  };
  ```

* 私有继承

  ```c++
  class Base3
  {
  public:
      int m_A;
  protected:
      int m_B;
  private:
      int m_C;
  };
  
  class Son3 :private Base3
  {
  public: 
      void func()
      {
          m_A=10;
      }
  };
  ```

  

![image-20240201193527145](/home/future/.config/Typora/typora-user-images/image-20240201193527145.png)

### 继承中的对象模型

**问题：**从父类继承过来的成员，那些属于子类对象中？

```c++
class Base
{
public:
    int m_A;
protected:
    int m_B;
private:
    int m_C;
};

class Son :public Base
{
public:
    int m_D;
};

int main()
{
    cout << sizeof(Son) << endl; //**16**
    return 0;
}
```

父类中的所有非静态成员属性都会被子类继承下去

父类中私有成员属性  是被编译器隐藏了，因此访问不到  但是确实是被继承下去了

### 继承中构造和析构顺序

子类继承父类后，当创建子类对象，也会调用父类的构造函数

问题：父类和子类的构造和析构顺序是谁先谁后

```c++
class Base
{
    public:
    Base()
    {
        cout << "Base" << endl;
    }
    ~Base()
    {
        cout << "Basexg" << endl;
    }
};

class Son :public Base
{
    public:
    Son()
    {
        cout << "Son" << endl;
    }
    ~Son()
    {
        cout << "Sonxg" << endl;
    }
};

void test()
{
    Son s;
}

int main()
{
    test();
    return 0;
}
```

![image-20240201201220096](/home/future/.config/Typora/typora-user-images/image-20240201201220096.png)

继承中的构造和析构顺序：

* 构造先构造父类，在构造子类
* 析构先析构子类，在构造父类

### 继承中同名处理方式

问题：当子类与父类出现同名的成员，如何通过子类对象，访问到子类或父类中同名的数据？

* 访问子类同名成员		直接访问即可
* 访问父类同名成员                需要加作用域

```c++
void test()
{
    Son s;
    cout << s.m_A << endl;
    cout << s.Base::m_A << endl;//如果通过子类对象  访问到父类中同名成员，需要加作用域
}
```

```c++
//同名函数的处理方式
void test01()
{
    Son s;
    s.func();
    s.Base::func();
}
```

如果子类中出现和父类同名的成员函数，子类的同名成员函数会隐藏掉父类中的所有同名成员函数。

如果想访问到父类中被隐藏的同名成员函数，需要加作用域。

总结：

* 子类对象可以直接访问到子类中同名成员
* 子类对象加作用域可以访问到父类同名成员
* 当子类与父类拥有同名的成员函数，子类会隐藏父类中的所有同名的成员函数，加作用域可以访问到父类中同名函数

### 继承同名静态成员处理方式

问题：继承中同名的静态成员在子类对象上如何进行访问?

静态成员和非静态成员出现同名，处理方式一致

* 访问子类同名成员         直接访问即可
* 访问父类同名成员         需要加作用域

```c++
//同名静态成员属性
void test()
{
    //通过对象访问
   	Son s;
    cout << s.m_A << endl; 
    cout << Son:: m_A << endl;
    cout << Base ::m_A << endl;
    //通过对象访问
    cout << s.Base::m_A << endl;
    //第一个冒号 代表通过类名方式访问  第二个冒号代表父类作用域下
    cout << Son::Base::m_A << endl; 
}

//同名静态成员函数
void test01()
{
    //通过对象访问
    Son s;
    s.func();
    s.Base::func();
    //通过类名访问
    Son ::func();
    Son::Base::func();
}
```

子类出现和父类同名静态成员函数，也会隐藏父类中所有同名成员函数

如果想访问父类中被隐藏同名成员，需要加作用域

### 多继承语法

C++允许一个类继承多个类

> 语法：	class  子类  ： 继承方式  父类1    ，继承方式   父类2 ......

多继承可能会引发父类中有同名成员出现，需要加作用域区分

C++实际开发中不建议用多继承

```c++
class Son :public Base1,public Base2
```

> 总结：多继承中如果父类中出现了同名情况，子类使用时候要加作用域.

### 菱形继承

菱形继承概念：

	两个派生类继承同一个基类
	
	又有某个同类同时继承两个派生类
	
	这种继承被称为菱形继承，或者钻石继承

**菱形继承典型案例**

![image-20240202103817906](/home/future/.config/Typora/typora-user-images/image-20240202103817906.png)

菱形继承问题：

1.羊继承了动物的数据，驼同样继承了动物的数据，当草泥马使用数据时，就会产生二义性

2.草泥马继承自动物的数据继承了两份，其实我们应该清楚，这份数据我们只需要一份就可以.

利用虚继承  解决菱形继承问题

```c++
class Animal
{
public:
    int m_Age;
};
//利用虚继承  解决菱形继承问题
//继承之前加上virtual 变为虚继承
//Animal类称为 虚基类
//羊类
class Sheep : virtual public Animal{};
class Tuo : virtual public Animal{};
class SheepTuo :public Sheep,public Tuo{};

void test01()
{
    SheepTuo st;
    st.Sheep::m_Age = 18;
    st.Tuo::m_Age = 28;
    cout << st.Sheep::m_Age << endl;
    cout << st.Tuo::m_Age << endl;
    cout << st.m_Age << endl;
}
```

总结：

* 菱形继承带来的主要问题是子类继承两份相同的数据，导致资源浪费以及毫无意义
* 利用虚继承可以解决菱形继承问题

## 多态

多态是C++面向对象三大特性之一

多态分为两类：

* 静态多态 ：函数重载和运算符重载属于静态多态，复用函数名
* 动态多态 ：派生类和虚函数实现运行时多态

区别：

* 静态多态的函数地址早绑定 -- 编译阶段确定函数地址
* 动态多态的函数地址晚绑定 -- 运行阶段确定函数地址

> 动态多态满足条件：
>
> * 有继承关系
>
> * 子类要重写父类中的虚函数（函数返回值类型  函数名  参数类表  完全相同）
>
>   使用
>
>   父类的指针或者引用	 执行子类的对象

C++允许子类父类做类型转换.

```c++
class Animal
{
public:
    //虚函数
    virtual void spaek()
    {
        cout << "speak Animal" << endl;
    }
};

class Cat :public Animal
{
public:
    void speak()
    {
        cout << "speak Cat" << endl;
    }
};
//如果想执行对应的子类函数，那么这个函数地址就不能提前绑定，需要在运行阶段进行绑定，晚绑定
void dospeak(Animal &A)
{
    A.spaek();
}

void test()
{
    Cat cat;
    dospeak(cat);
}
```

### 原理深度剖析

![image-20240203092344044](/home/future/.config/Typora/typora-user-images/image-20240203092344044.png)

```c++
class Animal
{
public:
	virtual void speak()
    {
		cout << "Animal Speak" << endl;
    }
};

void test()
{
    cout << sizeof(Animal) << endl;//8   这是一个指针的大小，当使用虚函数的时候，内部生成
    							   //一个vfptr的指针，指向函数的所在位置
}
```

### 案例--计算器类

多态的优点：

* 代码结构清晰
* 可读性强
* 立于前期和后期的拓展以及维护

### 纯虚函数和抽象类

在多态中，通常父类中函数的实现是毫无意义的，主要都是调用子类重写的内容

因此可以将虚函数改为纯虚函数

> 语法：virtual   返回值类型 函数名 (参数列表) = 0；

当类中有了纯虚函数，这个类也称为抽象类

抽象类特点:

* 无法实例化对象
* 子类必须重写抽象类中的纯虚函数，否则也属于抽象类型

  

```c++
class Base
{
public:
    //纯虚函数
    //只要有一个纯虚函数，这个类称为抽象类
    //特点：无法实例化对象      抽象类的子类  必须要重写父类中的纯虚函数，否则也属于抽象类
    virtual void func() = 0 ;
};

class Son : public Base
{
public:
    virtual void func()
    {
        cout << "实现函数" << endl;
    }
};

void test()
{
    //Base b;
    //new Base;无法实例化对象
    Son s;//子类必须重写纯虚函数
    s.func();
}
```

### 案例  --  饮料制作

```c++
class AbstractDrinking
{
public:
    virtual void Bool( ) = 0;
    virtual void Brew( ) = 0;
    virtual void PourInCup( ) = 0;
    virtual void PutSomething( ) = 0;
    void makeDrinking()
    {
        Bool( );
        Brew( );
        PourInCup();
        PutSomething( );
    }
};

class coffee :public AbstractDrinking
{
    virtual void Bool( ) 
    {
        cout << "Coffeewater" << endl;
    }
    virtual void Brew( ) 
    {
        cout << "冲泡咖啡" <<endl;
    }
    virtual void PourInCup( ) 
    {
        cout << "倒入杯中" << endl;
    }
    virtual void PutSomething( )
    {
        cout << "Put something" << endl;
    }
};

class Tea :public AbstractDrinking
{
    virtual void Bool( ) 
    {
        cout << "Teawater" << endl;
    }
    virtual void Brew( ) 
    {
        cout << "茶叶咖啡" <<endl;
    }
    virtual void PourInCup( ) 
    {
        cout << "倒入杯中" << endl;
    }
    virtual void PutSomething( )
    {
        cout << "Put something" << endl;
    }
};
```

### 虚析构和纯虚析构

多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码

解决方式：将父类中的析构函数改为虚析构或者纯虚析构

虚构和纯虚析构共性：

* 可以解决父类指针释放子类对象
* 都需要有具体的函数实现

区别

* 如果是纯虚析构，该类属于抽象类，无法实例化对象

```c++
class Animal
{
public:
    Animal()
    {
        cout << "Animal的构造函数" << endl;
    }
    // virtual ~Animal() //利用虚析构可以解决 父类指针释放子类对象时的不干净的问题
    // {
    //     cout << "Animal的析构函数" << endl;
    // }
    //需要声明 ，也需要实现
    virtual ~Animal () = 0;
    virtual void speak()=0;
};

Animal :: ~Animal()
{
    cout << "Animal的纯虚析构" << endl;
}

class Cat : public Animal
{
public:
    Cat(string name)
    {
        cout << "cat的构造函数" << endl;
        m_Name = new string(name);
    }
    virtual void speak()
    {
        cout << *m_Name << "Cat Speaking" << endl;
    }
    ~Cat()
    {
        if(m_Name!=NULL)
        {
            cout << "cat的析构函数调用" << endl;
            delete m_Name;
            m_Name = NULL;
        } 
    }
    string *m_Name;
};

void test01()
{
    Animal *a = new Cat("Tom");
    a->speak();
    //父类指针在析构的时候 ，不会调用子类中的析构函数 ，导致子类如果有属性在堆区的话 ，出现了内存泄漏
    delete a;
}
```

![image-20240203120008919](/home/future/.config/Typora/typora-user-images/image-20240203120008919.png)

总结：

* 虚析构或者纯虚析构就是用来解决通过父类指针释放子类对象
* 如果子类中没有堆区数据，可以不写
* 拥有纯虚析构函数的类也属于抽象类

### 案例3 -- 组装电脑

```c++
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
        if( m_cpu!= NULL)
        {
            delete m_cpu;
            m_cpu=NULL;
        }
        if(m_mem!=NULL)
        {
            delete m_mem;
            m_mem=NULL;
        }
        if(m_vc!=NULL)
        {
            delete m_vc;
            m_vc=NULL;
        }
    }
private:
    CPU * m_cpu;
    VideoCard *m_vc;
    Memory *m_mem;
};


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
```

# 文件

通过文件可以将数据持久化

头文件<fstream>

文件类型：

* 文本文件         -文件以文本的Ascll码形式存储在计算机中
* 二进制文件     -文件以文本的二进制形式存储在计算机中，用户一般不能直接读懂

操作三大类：

* ofstream  写操作
* ifstream   读操作
* fstream    读写操作

## 文本文件

![image-20240203181317640](/home/future/.config/Typora/typora-user-images/image-20240203181317640.png)

文件打开方式可以配合使用， 利用|操作符

总结：

* 文件操作必须包含头文件fstream
* 读文件可以利用ofstream 或者 fstream类
* 打开文件时需要指定操作文件的路径，以及打开的方式
* 利用 << 可以向文件中写数据
* 操作完毕，关闭文件

## 读文件

```c++
void test()
{
    ifstream ifs;
    ifs.open("test.txt",ios::in);
    if(!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
        return;
    }
    //接下来读取数据
    //1.first
    // char buf[1024]={0};
    // while(ifs >> buf)
    // {
    //     cout << buf << endl;
    // }
    //2.second
    // char buf[1024]={0};
    // while(ifs.getline(buf,1024))
    // {
    //     cout << buf << endl;
    // }
    //3.third
    // string buf;
    // while(getline(ifs,buf))
    // {
    //     cout << buf << endl;
    // }
    //4. fourth
    char c;
    while((c=ifs.get())!=EOF)
    {
        cout << c ;
    }
    ifs.close();
}
```

总结：

* 读文件可以利用fstream ，或者fstream类
* 利用is_open函数可以判断文件是否可以打开成功
* close关闭文件

## 二进制文件

以二进制的方式对文件进行读写操作

打开方式要指定为ios::binary

### 写文件

二进制方式写文件主要利用流对象调用成员函数write

> 函数原型 ： ofstream& write(const char *buffer ,int len)

参数解释:字符指针buffer指向内存中一段存储空间，len是读写的字节数

```c++
class Person
{
    public:
    char m_Name[64];
    int m_Age;
};

void test()
{
    // ofstream ofs;
    // ofs.open("Person.txt",ios::out|ios::binary);
    ofstream ofs("Person.txt",ios::out|ios::binary);
    Person p = { "张三" , 18 };
    ofs.write((const char *)&p,sizeof(Person));
    ofs.close();
}
```

### 读文件

二进制方式读文件主要利用流对象调用成员函数read

> 函数原型: istream& read(char *buffer , int len);

参数解释：字符指针buffer指向内存中的一段存储空间，len是读写的字节数

```c++
class Person
{
public:
    char m_Name[64];
    int m_Age;
};

void test()
{
    ifstream ifs;
    ifs.open("Person.txt",ios::in | ios::binary);
    if(!ifs.is_open())
    {
        cout << "打开失败" << endl;
    }
    Person p;
    ifs.read((char *)&p,sizeof(Person));
    cout << p.m_Name << endl;
    cout << p.m_Age << endl;
    ifs.close();
}
```

# c++提高

* 本阶段主要针对C++泛型编程和STL技术详解

## 模板

模板就是建立通用的模具，大大提高复用性

特点：

* 模板不可以直接使用，他只是一个框架
* 模板的通用并不是万能的

### 函数模板

* c++另一种编程思想为泛型编程，主要利用的技术就是模板
* c++提供两种模板机制：函数模板和类模板

```c++
template<typename T>
函数声明或定义（这里写函数）
```

解释：

* template   --- 声明创建模板
* typename  ---表明其后面的符号是一种数据类型，可以用class代替
* T  --- 通用的数据类型 ， 名称可以替换 ， 通常为大写字母

  

```c++
template <typename T>//声明一个模板，告诉编译器后面代码中紧跟着的T不要报错，T是一个通用的数据类型
void myswap(T &a, T &b) 
{
    T temp=a;
    a=b;
    b=temp;
}

int main()
{
    int a=10;
    int b=20;
    //两种方式使用函数模板
    //1.自动类型推导
    myswap(a,b);
    //2.显示指定类型
    myswap<int>(a,b);
    return 0;
}
```

**总结**：

* 函数模板利用关键字template
* 函数模板的两种使用方式：1.自动类型推导          2.显示指定类型
* 模板的目的是为了提高复用性，将数据类型参数化

#### 注意事项

* 自动类型推导，必须要推导出一致的数据类型T，才可以使用
* 模板必须要确定出T的数据类型，才可以使用

```c++
template <typename T>
void mySwap(T &a,T &b)
{
    T temp=a;
    a=b;
    b=temp;
}

int main()
{
	int a=10;
    int b=20;
    char c='c';
    //正确的mySwap(a,b);
    mySwap(a,c);//无法推导出一致的数据类型
	return 0;
}

template <class T>
void func()
{
    cout << "kjkasl"<<endl;
}

int main()
{
	func();//没有指定T,函数内部都没有用到T  
	return 0;
}
```

#### 案例

利用函数模板封装一个函数，使得函数可以对不同的数据类型排序

排序按照从小到达的顺序

可以用到不同的排序函数

```c++
template <typename T>
int partition(T *a,int i,int j)
{
    T x = a[i];
    while(i<j)
    {
        while(i<j && a[j]>=x)
        {
            j--;
        }
        if(i<j)
        {
            a[i]=a[j];
            i++;
        }
        while(i<j && a[i]<x)
        {
            i++;
        }
        if(i<j)
        {
            a[j]=a[i];
            j--;
        }
    }
    a[i] =x;
    return i;
}

template <typename T>
void mySort(T *a,int i,int j)
{
    if(i<j)
    {
        int x=partition(a,i,j);
        mySort(a,i,x-1);
        mySort(a,x+1,j);
    }
}

void test()
{
    char chararr[]= "bacdfe";
    mySort(chararr,0,5);
    cout << chararr << endl;
    int num[]={4,5,1,2,9,7,0,3,6,8};
    mySort(num,0,9);
    for(int i=0;i<(sizeof(num)/sizeof(int));i++)
    {
        cout << num[i] << "  ";
    }
    cout << endl;
}
```

#### 普通函数与函数模板的区别

区别：

* 普通函数调用时可以发生类型转换（隐式类型转换）
* 函数模板调用时，如果是自动类型推导的话，不会发生类型转换
* 如果显示指定类型的话，可以发生隐式类型转换

```c++
template <typename T>
T myadd(T a, T b) {
    return a + b;
}

int add(int a,int b)
{
    return a + b;
}

void test()
{
    int a=10;
    int b=10;
    char c='a';
    add(a,c);
    //myadd(a,c);
    //显示指定类型
    cout << myadd<int>(a,c) << endl;
}

```

**总结：建议使用显示指定类型的方式，调用函数模板，因为可以自己确定通用类型T.**

#### 普通函数和函数模板的调用规则

调用规则：

* 如果函数模板和普通函数都可以实现，优先调用普通函数
* 可以通过空函数参数列表来强制调用函数模板
* 函数模板也可以发生重载
* 如果函数模板可以产生更好的匹配，优先调用函数模板

```c++
template<typename T>
void myprint(T a,T b)
{
    cout << "函数模板" << endl;
}

void myprint(int a,int b)
{
    cout << "普通函数" << endl;
}

void test()
{
    int a = 10;
    int b = 10;
    myprint(a,b);//调用的是普通函数，规则1 ，将普普通函数注释，只有声明，会发生报错，由于都可以实现，先调普通函数，但普通函数没有实现
    myprint<>(a,b);
}
```

 总结：既然提供了函数模板，最好就不要提供普通函数，否则容易出现二义性

#### 模板的局限性

* 模板的局限性并不是万能的

```c++
template <typename T>
void f(T a,T b)
{
	a=b;
}
//如果传入的的是一个数组，就无法实现了.
template <typename T>
void f(T a,T b)
{
	if(a>b)
    {
		......
    }
}
//传入的是Person ，无法确定比较的数值

```

因此C++为了解决这种问题，提供模板的重载，可以为这些特定的类型提供具体化的模板

```c++
class Person
{
public:
    Person(string name, int age)
    {
        m_name = name;
        m_age = age;
    }
    string m_name;
    int m_age;
};

template <typename T>
bool mycompare(T &a, T &b)
{
    if(a==b)
    return true;
    else 
    return false;
}

//利用具体化Person的版本实现代码，具体化优先调用
template<>bool mycompare(Person &a,Person &b)
{
    if(a.m_name==b.m_name&&a.m_age==b.m_age)
    {
        return true;
    }
    else
    return false;
}

void test()
{
    int a=10;
    int b=20;
    cout << mycompare(a,b) << endl;//发生错误，无法比较。1.比较运算符重载   2.
}

void test01()
{
    Person p1("Tom",10);
    Person p2("Tom",10);
    cout << mycompare(p1,p2)<<endl;
}
```

总结：

* 利用具体化的模板，可以解决自定义类型的通用化
* 学习模板并不是为了写模板，而是在STL能够运用系统提供的模板

### 类模板

作用：建立一个通用的类，类中的成员  数据类型可以不具体指定，用一个虚拟的类型来代表

> 语法
>
> ```c++
> template <typename T>
> 类
> ```
>
> template    ---声明创建模板
>
> typename  ---表明其后面是一种数据类型，可以用class代替
>
> T                 ---通用的数据类型，名称可以替换，通常为大写的数据类型

类模板和函数模板的语法相似，在template后面加类，此类称为类模板.

### 类模板与函数模板的区别

* 类模板没有自动类型的推导的使用方式
* 类模板在模板参数列表中可以有默认参数(仅限于类模板)

 

```c++
template <class T1,class T2=int>//模板参数列表
class Person
{
public:
    Person(T1 name ,T2 age)
    {
        this->m_Name=name;
        this->m_Age=age;
    }
    void show()
    {
        cout << this->m_Name << endl;
        cout << this->m_Age << endl;
    }
    T1 m_Name;
    T2 m_Age;
};

//类模板在模板列表中可以有默认参数
void test01()
{
    Person<string >p1("Tom",17);
    p1.show();
}

void test()
{
    //Person p("John",18);,无类型推导的用法 
    Person<string ,int > p("John",18);
    p.show();
}
```

总结：

* 类模板使用只能显示指定类型方式
* 类模板中的模板参数列表可以有默认参数

#### 类模板中成员函数的创建时机

类模板中成员函数和普通类中成员函数创建时间是有区别的

* 普通类中的成员函数一开始就可以创建
* 类模板中的成员函数在调用时才创建

```c++
template <typename T>
class myClass
{
public:
    T obj;
    //类模板中的成员函数
    void func1()
    {
        obj.showPerson1();
    }
    void func2()
    {
        obj.showPerson2();
    }
};

class Person12
{
public:
    void showPerson2()
    {
        cout << "Person2" << endl;
    }
};

class Person1
{
public:
    void showPerson1()
    {
        cout << "Person1" << endl;
    }
};

```

总结：类模板中的成员函数并不是一开始就创建的，在调用时才去创建

#### 类模板对象做函数参数

* 类模板实例化的对象 ，向函数传参的方式

* 三种传参方式

  * 指定传入的类型   ---直接显示对象的类型

    ```c++
    void print1(Person <string,int>&p)
    {
    	p.showPerson();
    }
    
    void test01()
    {
    	Person<string,int>p("孙悟空"，100);
    }
    ```

  * 参数模板化           ---将对象中的参数变为模板进行传递

    ```c++
    template <class T1,class T2>
    void print2(Person <T1,T2>&p)
    {
        p.showPerson();
        cout << "T1的类型为: " << typeid(T1).name << endl;
        
    }
    
    void test02()
    {
        Person <string,int >p("tom",200);
        print2(p);
    }
    ```

    ![image-20240207100830094](/home/future/.config/Typora/typora-user-images/image-20240207100830094.png)

  * 整个类模板化       ---将这个对象类型  模板化进行传递

    ```c++
    template <class T>
    void print3(T &p)
    {
         p.showPerson();
    }
    
    void test03()
    {
        Person<string ,int >p("唐僧",18);
     	print3(p);   
    }
    ```

    

```c++
template <class T1 ,class T2>
class Person
{
public:
    Person(T1 name ,T2 age)
    {
		this->m_Name=name;
        this->m_Age=age;
    }
    void showPerson()
    {
        cout << this->m_Name <<endl;
        cout << this->m_Age <<endl;
    }
    
    T1 m_Name;
    T2 m_Age;
};
```

总结：

* 通过类模板创建的对象，可以有三种方式向函数中进行传参
* 使用比较广泛的是第一种：指定传入类型

#### 类模板与继承

注意：

* 当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中T的类型
* 如果不指定，编译器无法给子类分配内存
* 如果想灵活指定出父类中T的类型，子类也需要变为类模板

```c++
template <class T>
class Base
{
public:
    T m;
};

//class Son : public Base //错误的，必须要知道父类中T的数据类型，才能继承给子类
class Son : public Base <int>
{

};

//想灵活指定类模板中的类型，子类也需要变为模板

template <class T1,class T2>
class Son1 : public Base<T2>
{
public:
    Son1()
    {
        cout << typeid(T1).name << endl;
        cout << typeid(T2).name << endl;
    }
    T1 obj;
};

void test()
{
    Son s1;
}

void test01()
{
    Son1 <int ,string> s;
}
```

**如果父类是一个类模板，子类在继承的时候必须要指定出父类中T的数据类型。**

#### 类模板成员函数在类外实现

```c++
template <class T1,class T2>
class Person
{
public:
    Person(T1 name ,T2 age);
    // {
    //     this->m_Age=age;
    //     this->m_Name=name;
    // }
    void showName();
    // {
    //     cout << this->m_Age << endl;
    //     cout << this->m_Name << endl;
    // }
    T1 m_Name;
    T2 m_Age;
};

template <class T1,class T2> 
Person<T1,T2> :: Person(T1 name ,T2 age)
{
    this->m_Age=age;
    this->m_Name=name;
}

template <class T1,class T2>
void Person<T1,T2> :: showName()
{
    cout << this->m_Name << endl;
    cout << this->m_Age << endl;
}

void test()
{
    Person<string,int>p("John",18);
    p.showName();
}
```

总结：类模板中的成员函数类外实现时，要加上模板参数列表.

#### 类模板分文件编写

类模板成员函数创建实际是在调用阶段 ，导致分文件编写时链接不到

* 直接包含.cpp源文件
* 将声明和实现写到同一个文件当中，并更改后缀名为.hpp.  .hpp是约定的名称，并不是强制的

	普通类中的成员函数一开始就可以创建

	类模板中的成员函数在调用时才创建

总结：主流的解决方式是第二种，将类模板和成员函数写到一起，并将后缀名改为.hpp

#### 类模板与友元

全局函数实现 -- 直接在类内声明友元即可

全局函数类外实现 -- 提前让编译器知道全局函数的存在

```c++
template <class T1,class T2>
class Person;

//类外实现
template <class T1 ,class T2>
void printPerson2(Person<T1,T2> p)
{
    cout << p.m_Name<<endl;
    cout << p.m_Age<<endl;
}

//通过全局函数打印Person的信息
template <class T1 ,class T2>
class Person
{
    //全局函数类内实现
    friend void printPerson(Person<T1,T2> p)
    {
        cout << p.m_Name<<endl;
        cout << p.m_Age<<endl;
    }
    //全局函数类外实现
    //加空模板的参数列表
    friend void printPerson2<>(Person<T1,T2> p);
public:
    Person(T1 name ,T2 age)
    {
        this->m_Name=name;
        this->m_Age=age;
    }
private:
    T1 m_Name;
    T2 m_Age;
};

void test()
{
    Person <string ,int> p ("Hello",18);
    printPerson(p);
}

void test01()
{
    Person <string ,int>   p("ahjsd",19);
    printPerson2(p);
}

```

总结：建议全局函数做类内实现，用法简单，而且编译器可以直接识别

## STL的初识

### STL的诞生

* 长久以来，软件界一直希望建立一种可重复利用的东西
* C++的面向对象和泛型编程思想，目的就是复用性的提升
* 大多数情况下，数据结构和算法都未能有一套标准，导致被迫从事大量重复工作
* 为了建立数据结构和算法的一套标准，诞生了STL

### 概念

* STL(Standard Template Library,**标准模板库**)
* STL从广义上分为：**容器(container)算法(algorithm)迭代器(iterator)**
* **容器**和**算法**之间通过**迭代器**进行无缝连接
* STL 几乎所有的代码都采用了模板类或者模板函数

### 6大组件

STL6大组件，分别为：**容器，算法，迭代器，仿函数，适配器(配接器)，空间配置器**

> 1.容器：各种数据结构，如vector, list , deque, set, map等，用来存放数据
>
> 2.算法：各种常用的算法：如sort、find、copy、for_each等
>
> 3.迭代器：扮演了容器与算法之间的胶合剂
>
> 4.仿函数：行为类似函数，可作为算法的某种策略
>
> 5.适配器：一种用来修饰容器或者仿函数或迭代器接口的东西
>
> 6.空间配置器：负责空间的配置与管理

 ### 容器、算法、迭代器

![image-20240207161821162](/home/future/.config/Typora/typora-user-images/image-20240207161821162.png)

![image-20240207162716556](/home/future/.config/Typora/typora-user-images/image-20240207162716556.png)

![image-20240207162736409](/home/future/.config/Typora/typora-user-images/image-20240207162736409.png)

### 容器算法迭代器初始

![image-20240207163041961](/home/future/.config/Typora/typora-user-images/image-20240207163041961.png)

```c++
void myPrint(int val)
{
    cout << val << endl;
}

void test()
{
    //创建l一个vector的容器，数组
    vector<int> v;
    //向容器中插入数据
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    //通过迭代器访问容器中的数据
    // vector<int>::iterator itBegin =v.begin();//起始迭代器  指向容器中的第一个元素
    // vector<int>::iterator itEnd =v.end(); //结束迭代器 指向容器中最后一个位置的下一个位置
    // //第一种遍历方式
    // while(itBegin!=itEnd)
    // {
    //     cout << *itBegin << endl;
    //     itBegin++;
    // }
    //第二种
    // for(vector<int>::iterator it=v.begin();it!=v.end();it++)
    // {
    //     cout << *it << endl;
    // }
    //第三种 利用STL中提供的遍历算法
    for_each(v.begin(),v.end(),myPrint);;
}
```

#### 存放自定义数据类型

```c++
class Person
{
public:
    Person(string name,int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    string m_Name;
    int m_Age;
};

void test()
{
    vector<Person> v;
    Person p1("John",10);
    Person p2("Tom",11);
    Person p3("Bob",12);
    Person p4("herry",13);
    Person p5("Alice",14);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);
    for(vector<Person>::iterator it =v.begin(); it !=v.end();it++)
    {
        // cout << (*it).m_Name << " " << (*it).m_Age << endl;
        cout << it->m_Name << " " << it->m_Age << endl;
    }
}

void test01()
{
    vector<Person *> v;
    Person p1("John",10);
    Person p2("Tom",11);
    Person p3("Bob",12);
    Person p4("herry",13);
    Person p5("Alice",14);
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    v.push_back(&p5);
    for(vector<Person *>::iterator it =v.begin(); it !=v.end();it++)
    {
        // cout << (*it).m_Name << " " << (*it).m_Age << endl;
        cout << (*(*it)).m_Name << "     " << (*(*it)).m_Age << endl;
    }
}

```

#### vector容器嵌套容器

```c++
void test()
{
    vector<vector <int>>v;
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4; 
    //向小容器内添加数据
    for(int i=0;i<4;i++)
    {
        v1.push_back(i+1);
        v2.push_back(i+5);
        v3.push_back(i+9);
        v4.push_back(i+13);
    }
    //将小容器加到大容器中
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    //通过大容器，遍历所有的数据
    for(vector<vector<int>> :: iterator it=v.begin();it!=v.end();it++)
    {
        for(vector<int>::iterator is=(*it).begin();is!=(*it).end();is++)
        {
            cout << *is << "   "; 
        }
        cout << endl;
    }
}
```

## STL常用容器

### string容器

#### 概念

![image-20240207204323037](/home/future/.config/Typora/typora-user-images/image-20240207204323037.png)

#### 构造函数

![image-20240207205531434](/home/future/.config/Typora/typora-user-images/image-20240207205531434.png)

```c++
void test()
{
    string s1;//默认构造
    const char *str="Hello world!";
    string s2(str);
    cout << s2 << endl;
    string s3( s2);
    cout << s3 << endl;
    char a='b';
    string s4(10,a);
    cout << s4 << endl;
}
```

总结：string的多种构造方式没有可比性，灵活使用即可.

#### string赋值操作

![image-20240207210315823](/home/future/.config/Typora/typora-user-images/image-20240207210315823.png)

```c++
void test()
{
    string str1;
    str1="hello world!";
    cout << str1 << endl;
    string str2;
    str2=str1;
    cout << str2 << endl;
    string str3;
    str3='a';
    cout << str3 << endl;
    string str4;
    str4.assign("hello C++!");
    cout << str4 << endl;
    string str5;
    str5.assign("hello C++!",5);
    cout << str5 << endl;
    string str6;
    str6.assign(str4);
    cout << str6 << endl;
    string str7;
    str7.assign(7,'a');
    cout << str7 << endl;
}

```

#### 字符串拼接

![image-20240207213803623](/home/future/.config/Typora/typora-user-images/image-20240207213803623.png)

```c++
void test()
{
    string str1="我";
    str1+="爱玩";
    cout << str1 << endl;
    str1+=':';
    cout << str1 << endl;
    string str2="LoL";
    str1+=str2;
    cout << str1 << endl;
    string str3="I";
    str3.append(" Love ");
    cout << str3 << endl;
    str3.append("game abcde",4);
    cout << str3 << endl;
    str3.append(str1);
    cout << str3 << endl;
}
```

总结： 字符串拼接的重载版本很多，记住几种即可.

#### string的查找和替换

![image-20240208093512163](/home/future/.config/Typora/typora-user-images/image-20240208093512163.png)

rfind 是从右往左查找

find  是从左往右查找

```c++
void test()
{   
    string str1="abcdefgde";
    int pos=str1.find("de");//有的话返回对应的下标，没有返回 -1 
    cout << pos << endl;
    pos=str1.rfind("de");
    cout << pos << endl;
    //find是从左往右查找  rfind是从右往左查找
}

//替换
void test1()
{
    string str1="abcdefg";
    str1.replace(1,3,"11111");//从一号位置起  3个字符替换为 "11111"
    cout << str1 << endl;
}
```

#### string字符串比较

![image-20240208100935824](/home/future/.config/Typora/typora-user-images/image-20240208100935824.png)

总结：字符串比较主要是判断两个字符串是否相等 ，实际判断谁大谁小意义不是很大

#### string字符存取

![image-20240208101502202](/home/future/.config/Typora/typora-user-images/image-20240208101502202.png)

str.size( )返回字符串长度

![image-20240208101753374](/home/future/.config/Typora/typora-user-images/image-20240208101753374.png)

#### string插入和删除

![image-20240208101955688](/home/future/.config/Typora/typora-user-images/image-20240208101955688.png)

	![image-20240208102235017](/home/future/.config/Typora/typora-user-images/image-20240208102235017.png)

**总结**：插入和删除的起始下标都是从0开始的

#### string子串

![image-20240208102427056](/home/future/.config/Typora/typora-user-images/image-20240208102427056.png)

**总结：**灵活的运用字串的功能，可以在实际的开发中获取有效的信息

### vector容器

#### 基本概念

![image-20240208103206166](/home/future/.config/Typora/typora-user-images/image-20240208103206166.png)

![image-20240208103353737](/home/future/.config/Typora/typora-user-images/image-20240208103353737.png)

* vector容器的迭代器是支持随机访问的迭代器

#### 构造函数

![image-20240208103659589](/home/future/.config/Typora/typora-user-images/image-20240208103659589.png)

```c++
	void test()
{
    vector <int> v1;
    for(int i=0;i<10;i++)
    {
        v1.push_back(i);
    }
    print(v1);
    vector <int> v2(v1.begin(),v1.end());
    print(v2);
    vector <int> v3(10,100);
    print(v3);
    vector <int> v4(v3);
    print(v4);
}

```

构造方式没有可比性，能够灵活使用即可.

#### 赋值操作

![image-20240208104848888](/home/future/.config/Typora/typora-user-images/image-20240208104848888.png)

#### 容量和大小

![image-20240208105314718](/home/future/.config/Typora/typora-user-images/image-20240208105314718.png)

#### 插入和删除

![image-20240210101043478](/home/future/.config/Typora/typora-user-images/image-20240210101043478.png)

```c++
void test()
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    //尾部删除
    v1.pop_back();
    //插入    第一个参数是迭代器
    v1.insert(v1.begin(),100);
    v1.insert(v1.begin(),2,1000);
    //删除   第一个参数也是迭代器
    v1.erase(v1.begin());
    // v1.erase(v1.begin(),v1.end());
    v1.clear();
}
```

#### 数据存取

![image-20240210102820218](/home/future/.config/Typora/typora-user-images/image-20240210102820218.png)

```c++
void test()
{
    vector<int> v1;
    for(int i=0;i<10;i++)
    {
        v1.push_back(i);
    }
    for(int i=0;i<v1.size();i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
    //利用at方式访问成员
    for(int i=0;i<v1.size();i++)
    {
        cout << v1.at(i) << " ";
    }
    cout << endl;
    cout << "第一个元素为 :" << v1.front() << endl;
    cout << "最后一个元素为:" << v1.back() << endl;
}

```

总结：

* 处理用迭代器获取vector容器中的元素，[ ]和 at也可以
* front返回容器中第一个元素
* back返回容器中最后一个元素

#### 互换容器

![image-20240210103627655](/home/future/.config/Typora/typora-user-images/image-20240210103627655.png)

```c++
void test()
{
    vector<int> v1;
    for(int i=0;i<10;i++)
    {
        v1.push_back(i);
    }
    cout << "交换前 :" << endl;
    print(v1);
    vector<int> v2;
    for(int i=10;i>0;i--)
    {
        v2.push_back(i);
    }
    print(v2);
    cout << "交换后 :" << endl;
    //用法
    v1.swap(v2);
    print(v1);
    print(v2);
}
```

实际用途:

* 巧用swap可以收缩内存空间

  ```c++
  void test02()
  {
      vector<int>v;
      for(int i=0;i<100000;i++)
      {
          v.push_back(i);
      }
      cout << v.capacity() << endl;
      cout << v.size() << endl;
      v.resize(3);
      vector <int>(v).swap(v);
  }
  ```

总结：swap可以是两个容器互换，可以达到实用的收缩内存的效果



#### 预留空间

![image-20240210111454734](/home/future/.config/Typora/typora-user-images/image-20240210111454734.png)

总结：如果数据量较大，可以一开始利用reserve预留空间

### deque容器

#### 基本概念

功能：

* 双端数组，可以对头端进行插入删除操作

与vector区别：

* vector对头部的删除插入效率低，数据量越大，效率越低
* deque相对而言，队头不得插入删除速度会比vector快
* vector访问元素时的速度会比deque快，这和两者的内部实现有关

![image-20240210113142721](/home/future/.config/Typora/typora-user-images/image-20240210113142721.png)

![image-20240210113323378](/home/future/.config/Typora/typora-user-images/image-20240210113323378.png)

deque的迭代器也支持随机访问

#### 构造函数

![image-20240210113453147](/home/future/.config/Typora/typora-user-images/image-20240210113453147.png)

```c++
void test()
{
    deque<int> d1;
    for(int i =0;i<10;i++)
    {
        d1.push_back(i);
    }
    print(d1);
    deque<int>d2(d1.begin(),d1.end());
    print(d2);
    deque<int>d3(10,100);
    deque<int>d4(d3);
    print(d4);
    print(d3);
}
```

与vecror容器的构造方式几乎一致，灵活使用即可

#### 赋值操作

![image-20240210114436979](/home/future/.config/Typora/typora-user-images/image-20240210114436979.png)

#### 大小操作

![image-20240210114911655](/home/future/.config/Typora/typora-user-images/image-20240210114911655.png)

无容量大小的说法，所以没有获取容量大小的接口

#### 插入和删除

![image-20240210142642051](/home/future/.config/Typora/typora-user-images/image-20240210142642051.png)

```c++
void test01()
{
    deque<int> d1;
    d1.push_back(30);
    d1.push_back(40);
    d1.push_back(50);
    d1.push_front(20);
    d1.push_front(10);
    // d1.pop_back();
    // d1.pop_front();
    // print(d1);
    // insert插入
    d1.insert(d1.begin(),1);
    print(d1);
    d1.insert(d1.begin(),2,0);
    //按照区间进行插入
    deque<int>d2;
    d2.push_back(1);
    d2.push_back(2);
    d2.push_back(3);
    d1.insert(d1.begin(),d2.begin(),d2.end());
    d1.erase(d1.begin());
    d1.erase(d1.begin(),d1.end());
}
```

#### 数据存取

![image-20240210144231154](/home/future/.config/Typora/typora-user-images/image-20240210144231154.png)

#### 排序

![image-20240210144801391](/home/future/.config/Typora/typora-user-images/image-20240210144801391.png)

```c++
void test()
{
    deque<int> d;
    d.push_back(6);
    d.push_back(4);
    d.push_back(3);
    d.push_back(1);
    d.push_back(5);
    d.push_back(2);
    print(d);
    sort(d.begin(), d.end());//默认是升序
    print(d);
}
```

### Stack容器

![image-20240210151524568](/home/future/.config/Typora/typora-user-images/image-20240210151524568.png)

栈可以判断容器是否为空

栈也可以返回元素个数

![image-20240210152034660](/home/future/.config/Typora/typora-user-images/image-20240210152034660.png)

### queue容器

![image-20240210152801347](/home/future/.config/Typora/typora-user-images/image-20240210152801347.png)

![image-20240210153114612](/home/future/.config/Typora/typora-user-images/image-20240210153114612.png)

![image-20240210153212635](/home/future/.config/Typora/typora-user-images/image-20240210153212635.png)

### List容器

#### 基本概念

![image-20240210153816320](/home/future/.config/Typora/typora-user-images/image-20240210153816320.png)

![image-20240210154806609](/home/future/.config/Typora/typora-user-images/image-20240210154806609.png)

![image-20240210154848836](/home/future/.config/Typora/typora-user-images/image-20240210154848836.png)

![image-20240210154908222](/home/future/.config/Typora/typora-user-images/image-20240210154908222.png)

#### 构造函数

![image-20240210155605757](/home/future/.config/Typora/typora-user-images/image-20240210155605757.png)

```c++
void test()
{
    list<int>l1;
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);
    l1.push_back(40);
    list<int>l2(l1.begin(),l1.end());
    list<int>l3(4,3);
    list<int>l4(l3);
}
```

 #### 赋值和交换

![image-20240210161302520](/home/future/.config/Typora/typora-user-images/image-20240210161302520.png)

```c++
void test()
{
    list<int> l1;
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);
    l1.push_back(40);
    list<int> l2;
    l2=l1;
    list<int> l3;
    l3.assign(l2.begin(),l2.end());
    list<int> l4;
    l4.assign(2,4);
}

void test()
{
    list<int> l1;
    list<int> l2;
    l1.swap(l2);
}
```

#### 大小操作

![image-20240210162104405](/home/future/.config/Typora/typora-user-images/image-20240210162104405.png)

```c++
void test()
{
    list<int> l1;
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);
    l1.push_back(40);
    if(l1.empty())
    {
        cout << "Empty list" << endl;
    }
    else
    {
        cout << "不为空 " << endl;
        cout << l1.size() << endl;
    }
    l1.resize(10,1);
    l1.resize(2);
}
```

#### 插入和删除

![image-20240210173304073](/home/future/.config/Typora/typora-user-images/image-20240210173304073.png)

```
void test()
{
    list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_front(100);
    l.push_front(200);
    l.push_front(300);
    l.pop_back();
    l.pop_front();
    l.insert(l.begin(),1000);
    l.insert((l.end()),100000);
    l.erase(--l.end());
    l.push_back(10);
    l.push_back(10);
    l.remove(10);
    l.clear();
}
```

#### 数据的存取

![`image-20240210174558674`](/home/future/.config/Typora/typora-user-images/image-20240210174558674.png)

![image-20240210174939272](/home/future/.config/Typora/typora-user-images/image-20240210174939272.png)

迭代器是不支持随机访问的.

#### 翻转和排序

![image-20240210175639076](/home/future/.config/Typora/typora-user-images/image-20240210175639076.png)

 

```c++
bool mycompare(int a,int b)
{
    return a>b;
}

void test()
{
    list<int> l;
    l.push_back(2);
    l.push_back(5);
    l.push_back(3);
    l.push_back(1);
    l.push_back(6);
    l.push_back(4);
    print(l);
    l.reverse();
    print(l);
    //所有不支持随机访问迭代器的容器，不可以用标准的算法
    //不支持随机访问迭代器的容器，内部会提供一些对应的算法
    // sort(l.begin(), l.end());
    // print(l);
    l.sort();
    print(l);
    l.sort(mycompare);
    print(l);
}
```

* 对于自定义数据类型，必须要指定排序规则，否则编译器不知道如何进行排序
* 高级排序只是在排序规则上在进行一次逻辑规则制定，并不复杂

### set/multiset容器

#### 基本概念

![image-20240211084130834](/home/future/.config/Typora/typora-user-images/image-20240211084130834.png)

#### 构造和赋值

![image-20240211084331413](/home/future/.config/Typora/typora-user-images/image-20240211084331413.png)

```c++
void test()
{
    set<int> s;
    //插入数据只有insert的方式
    //set：所有元素插入时自动排序
    //set不允许插入重复的值
    s.insert(20);
    s.insert(10);
    s.insert(30);
    s.insert(40);
    set<int> s2(s);
    set <int> s3;
    s3=s2;
}

```

#### 大小和交换

![image-20240211090620356](/home/future/.config/Typora/typora-user-images/image-20240211090620356.png)

```c++
void test()
{
    set<int> s;
    s.insert(40);
    s.insert(10);
    s.insert(30);
    s.insert(20);
    if(s.empty())
    {
        cout << "Empty" << endl;
    }
    else
    {
        cout << s.size() << endl;
    }
    set<int> s1;
    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s1.insert(4);
    s1.swap(s);
}
```

#### 插入和删除

![image-20240211091046645](/home/future/.config/Typora/typora-user-images/image-20240211091046645.png)

```c++
void test()
{
    set<int> s;
    s.insert(10);
    s.insert(30);
    s.insert(40);
    s.insert(20);
    print(s);
    s.erase(s.begin());
    print(s);
    s.erase(20);
    print(s);
}
```

 #### 查找和统计

![image-20240211091506753](/home/future/.config/Typora/typora-user-images/image-20240211091506753.png)

```c++
void test()
{
    set<int> s;
    s.insert(4);
    s.insert(1);
    s.insert(2);
    s.insert(8);
    s.insert(5);
    s.insert(9);
    s.insert(7);
    s.insert(6);
    s.insert(3);
    int fin;
    cin>>fin;
    if(s.find(fin) != s.end())
    {
        cout << s.count(fin) << endl;//对于set而言count的结果非0即1
    }
    else
    {
        cout << "Error" << endl;
    }
}
```

#### set与multiset的区别

![image-20240211095737047](/home/future/.config/Typora/typora-user-images/image-20240211095737047.png)

```c++
void test()
{
    set<int> s;
    pair<set<int>::iterator,bool> ret= s.insert(10);
    if(ret.second)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Error" << endl;
    }
    ret=s.insert(10);
    if(ret.second)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Error" << endl;
    }
    multiset<int> ms;
    ms.insert(10);
    ms.insert(10);
    print(ms);
}
```

#### pair对组的创建

![image-20240211100816841](/home/future/.config/Typora/typora-user-images/image-20240211100816841.png)

```c++
void test()
{
    pair<string,int> p("hello",20);
    cout<<p.first<<endl;
    cout<< p.second<<endl;
    pair<string,int> p2 = make_pair("Tom",18);
    cout << p2.first << " " << p2.second << endl;
}
```

#### 排序

![image-20240211101326393](/home/future/.config/Typora/typora-user-images/image-20240211101326393.png)

```c++
class MyCompare
{
public:
    bool operator()(int v1, int v2) const
    {
        return v1 > v2;
    }
};

void test()
{
    set<int> s1;
    s1.insert(40);
    s1.insert(10);
    s1.insert(30);
    s1.insert(50);
    s1.insert(20);
    print(s1);
    set <int,MyCompare>s2;
    s2.insert(40);
    s2.insert(10);
    s2.insert(30);
    s2.insert(50);
    s2.insert(20);
    for(set<int,MyCompare>::iterator i = s2.begin(); i != s2.end();i++)
    {
        cout << *i << " ";
    }
    cout << endl;
}

class Person
{
public:
    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    string m_Name;
    int m_Age;
};

class mycompare
{
public:
    bool operator()(const Person &a,const Person &b)const
    {
        return a.m_Age > b.m_Age;
    }
};

void test01()
{
    //自定义数据类型  都会指定排序规则
    set <Person,mycompare> s;
    Person p1("John",23);
    Person p2("Alice",19);
    Person p3("Bob",25);
    Person p4("Tom",17);
    s.insert(p1);
    s.insert(p2);
    s.insert(p3);
    s.insert(p4);
    for(set<Person,mycompare>::iterator it =s.begin();it!=s.end();it++)
    {
        cout << it->m_Name << "  " << it->m_Age << endl;
    }
    cout << endl;
}

int main()
{
    test01();
    return 0;
}

```

### map/multimap容器

#### 概念

![image-20240211105918556](/home/future/.config/Typora/typora-user-images/image-20240211105918556.png)

#### 构造和赋值

![image-20240211110311435](/home/future/.config/Typora/typora-user-images/image-20240211110311435.png)

```c++
void test()
{
    map<int,int> m;
    m.insert(pair<int,int>(1,10));
    m.insert(pair<int,int>(2,20));
    m.insert(pair<int,int>(3,30));
    m.insert(pair<int,int>(4,40));
    map<int,int > m1 (m);
    map<int,int > m3;
    m3= m1;
}

```

map中的所有元素都是成对出现的，插入数据的时候要使用对组

#### 大小和交换

![image-20240211112514956](/home/future/.config/Typora/typora-user-images/image-20240211112514956.png)

```c++
void test()
{
    map<int,int> m;
    m.insert(pair<int,int>(1,10));
    m.insert(pair<int,int>(4,40));
    m.insert(pair<int,int>(2,20));
    m.insert(pair<int,int>(3,30));
    if(m.empty())
    {
        cout << "Empty map" << endl;
    }
    else
    {
        cout << m.size() << endl;
    }
    map<int,int> m1;
    m1.insert(pair<int,int>(1,1));
    m1.insert(pair<int,int>(4,4));
    m1.insert(pair<int,int>(2,2));
    m1.insert(pair<int,int>(3,3));
    m1.swap(m);
    print(m);
}
```

#### 插入和删除

![image-20240211113320568](/home/future/.config/Typora/typora-user-images/image-20240211113320568.png)

```c++
void test()
{
    map<int,int> m;
    //first
    m.insert(pair<int,int>(1,10));
    //second
    m.insert(make_pair(2,20));
    //third
    m.insert(map<int,int>::value_type(3,30));
    //fourth
    m[4]=40;//如果没有该键值的元素，会创建一个对应实值为0的元素
    //删除
    m.erase(m.begin());
    m.erase(3);
    m.clear();
}
```

#### 查找和统计

![image-20240211114449248](/home/future/.config/Typora/typora-user-images/image-20240211114449248.png)

#### 排序

![image-20240211115104424](/home/future/.config/Typora/typora-user-images/image-20240211115104424.png)

```c++
class MyCompare
{
public:
    bool operator()(int a,int b) const
    {
        return a>b;
    }

};

void test()
{
    map<int,int,MyCompare> m;
    m.insert(pair<int,int>(1,10));
    m.insert(pair<int,int>(2,20));
    m.insert(pair<int,int>(3,30));
    m.insert(pair<int,int>(4,40));
    m.insert(pair<int,int>(5,50));
    for(map<int,int,MyCompare>::const_iterator i = m.begin(); i != m.end();i++)
    {
        cout << i->first << " " << i->second << endl;
    }
}
```

总结：

* 利用仿函数可以指定map容器的排序规则
* 对于自定义的数据类型，map必须要指定排序的规则，同set容器一样

## STL-函数对象

### 函数对象

#### 概念

![image-20240211141005082](/home/future/.config/Typora/typora-user-images/image-20240211141005082.png)



#### 使用

![image-20240211141109572](/home/future/.config/Typora/typora-user-images/image-20240211141109572.png)

```c++
class MyAdd
{
public:
    int operator()(int v1,int v2)
    {
        return v1+v2;
	}
};

void test
{
  	MyAdd myAdd;
    cout << myAdd(10,10) << endl;
}
```

### 谓词

#### 概念

![image-20240211142012336](/home/future/.config/Typora/typora-user-images/image-20240211142012336.png)

一元谓词

```c++
class GreaterFive
{
public:
    bool operator()(int val)
    {
        return val>5;
	}
};

voit test()
{
	vector<int> v;
    for(int i=0;i<10;i++)
    {
		v.push_back(i);
    }
    //查找容器中有没有大于5的数字
    vector<int>::iterator it=
        find_if(v.begin(),v.end(),GreaterFive());//greaterFive匿名的函数对象
}

```

二元谓词

```c++
class MyCompare
{
 public:
    bool operator()(int a,int b)
    {
		return a>b;
    }
};

void test()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(20);
    v.push_back(30);
    v.push_back(50);
    sort(v.begin(),v.end(),MyCompare());
}
```

### 内建函数对象

#### 意义

![image-20240211143156563](/home/future/.config/Typora/typora-user-images/image-20240211143156563.png)

 #### 算术仿函数

![image-20240211143303077](/home/future/.config/Typora/typora-user-images/image-20240211143303077.png)

```c++
//negate 一元仿函数 
void test()
{
	negate<int> n;
    cout <<n(50)<< endl;
}
//plus
void test02()
{
	plus<int> p;
    cout << p(10,30) << endl;
    cout << p(10,n(8)) << endl;
}
```

#### 关系仿函数

![image-20240211143837661](/home/future/.config/Typora/typora-user-images/image-20240211143837661.png)

```c++
void test()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(5);
    v.push_back(4);
    v.push_back(2);
    v.push_back(3);
    sort(v.begin(),v.end(),greater<int>());
}
```

#### 逻辑仿函数

![image-20240211150816722](/home/future/.config/Typora/typora-user-images/image-20240211150816722.png)

![image-20240211151131981](/home/future/.config/Typora/typora-user-images/image-20240211151131981.png)

## STL - 常用算法

![image-20240211155328131](/home/future/.config/Typora/typora-user-images/image-20240211155328131.png)

### 遍历

#### for_each

```c++
void print01(int val)
{
	cout << val << " ";
}

class print02
{
public:
    void operator()(int val)
    {
        cout << val << " ";
    }
};

void test()
{
	vector<int> v;
    for(int i=0;i<10;i++)
    {
        v.push_back(i);
	}
    for_each(v.begin(),v.end(),print01);
    cout << endl;
    for_each(v.begin(),v.end(),ptint02());
}
```

#### transform

![image-20240211160255878](/home/future/.config/Typora/typora-user-images/image-20240211160255878.png)

```c++
class Transform
{
public:
    int operator()( int val)
    {
		return v;
    }
}

void test()
{
	vector<int>v;
    for(int i=0;i<10;i++)
    {
		v.push_back(i);
    }
    vector<int> v2;
    v2.resize(v,size());
    transform(v.begin(),v.end(),v1.begin(),Transform());
}
```

**总结**：搬运的目标容器必须要提前开辟空间，否则无法正常搬运

### 查找

![image-20240211160932065](/home/future/.config/Typora/typora-user-images/image-20240211160932065.png)

#### find

![image-20240211161049431](/home/future/.config/Typora/typora-user-images/image-20240211161049431.png)

![image-20240211161305571](/home/future/.config/Typora/typora-user-images/image-20240211161305571.png)

对于自定义数据类型，我们需要在类内部重载  == 号，才可以正确寻找   find的底层是判断相等

#### find_if

![image-20240211163117148](/home/future/.config/Typora/typora-user-images/image-20240211163117148.png)

#### adjacent_find

![image-20240211174604176](/home/future/.config/Typora/typora-user-images/image-20240211174604176.png)

```c++
void test()
{
    vector<int> v;
    v.push_back(0);
    v.push_back(2);
    v.push_back(0);
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
    v.push_back(3);
    v.push_back(3);
    cout << *(adjacent_find(v.begin(),v.end())) << endl;
}
```

总结：如果出现查找相邻重复元素 ，记得使用STL中的adjacent_find算法

#### binary_search

![image-20240211175151252](/home/future/.config/Typora/typora-user-images/image-20240211175151252.png)

总结：二分查找查找的效率很高，但必须容器中的元素是有序的

#### count 

![image-20240211175600782](/home/future/.config/Typora/typora-user-images/image-20240211175600782.png)

![image-20240211175755968](/home/future/.config/Typora/typora-user-images/image-20240211175755968.png)

自定义数据类型，也需要重载 == 运算符

![image-20240211180237816](/home/future/.config/Typora/typora-user-images/image-20240211180237816.png)



![image-20240211180039931](/home/future/.config/Typora/typora-user-images/image-20240211180039931.png)

#### count_if

![image-20240211180518854](/home/future/.config/Typora/typora-user-images/image-20240211180518854.png)

![image-20240211180727096](/home/future/.config/Typora/typora-user-images/image-20240211180727096.png)



![image-20240211180740777](/home/future/.config/Typora/typora-user-images/image-20240211180740777.png)



### 排序

![image-20240211181230339](/home/future/.config/Typora/typora-user-images/image-20240211181230339.png)

#### sort

![image-20240211182108157](/home/future/.config/Typora/typora-user-images/image-20240211182108157.png)

```c++
void print(int val)
{
    cout << val << " ";
}

class compare
{
public:
    bool operator()(int a,int b) const
    {
        return a > b;
    }
};

void test()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);
    v.push_back(5);
    v.push_back(4);
    sort(v.begin(), v.end());
    for_each(v.begin(), v.end(), print);
    cout << endl;
    sort(v.begin(), v.end(),compare());
    for_each(v.begin(), v.end(), print);
    cout << endl;
}
```

#### random_shuffle

![image-20240211182735550](/home/future/.config/Typora/typora-user-images/image-20240211182735550.png)

```c++
void test()
{
	vector<int> v;
    for(int i=0;i<10;i++)
    {
		v.push_back(i);
    }
    random_shuffle(v.begin(),v.end());
}
```

**总结：**random_shuffle洗牌算法比较实用，但使用时记得加上随机数种子

#### merge

![image-20240211183135703](/home/future/.config/Typora/typora-user-images/image-20240211183135703.png)

```c++
void test()
{
	vector<int> v1;
    vector<int> v2;
    for(int i=0;i<10;i++)
    {
		v1.push_back(i);
        v2.push_back(i+2);
    }
    vector<int> v3;
    v3.resize(v1.size()+v2.size());
    merge(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());
}
```

#### reverse

![image-20240211183945834](/home/future/.config/Typora/typora-user-images/image-20240211183945834.png)

### 常用拷贝和替换

![image-20240211184216459](/home/future/.config/Typora/typora-user-images/image-20240211184216459.png)

#### copy

![image-20240211184259681](/home/future/.config/Typora/typora-user-images/image-20240211184259681.png)

```c++
void test()
{
	vector<int> v;
    for(int i=0;i<10;i++)
    {
		v.push_back(i);
    }
    vector<int> v2;
    v2.resize(v.size());
    copy(v.begin(),v.end(),v2.begin());
}
```

#### replace

![image-20240211184601187](/home/future/.config/Typora/typora-user-images/image-20240211184601187.png)

```c++
void test()
{
    vector<int> v;
    v.push_back(20);
    v.push_back(30);
    v.push_back(50);
    v.push_back(40);
    v.push_back(30);
    v.push_back(20);
    v.push_back(10);
    v.push_back(20);
    replace(v.begin(),v.end(),20,200);
}
```

#### replace_if

![image-20240211185014619](/home/future/.config/Typora/typora-user-images/image-20240211185014619.png)

```c++
class compare
{
public:
    bool operator()(int val)
    {
		return val>20;
    }
};

void myprint(int val)
{
	cout << val << " ";
}

void test()
{
 	vector<int> v;
    v.push_back(30);
    v.push_back(10);
    v.push_back(40);
    v.push_back(20);
    v.push_back(10);
    v.push_back(60);
    v.push_back(70);
    v.push_back(90);
    for_each(v.begin(),v.end(),myprint);
    replace_if(v.begin(),v.end(),compare(),200);
}
```

#### swap

![image-20240211185855791](/home/future/.config/Typora/typora-user-images/image-20240211185855791.png)

**总结：**交换的容器要是相同种类的.

### 常用算术生成算法

![image-20240211190321244](/home/future/.config/Typora/typora-user-images/image-20240211190321244.png)

#### accumulate

![image-20240211190553605](/home/future/.config/Typora/typora-user-images/image-20240211190553605.png)

```c++
void test()
{
    vector<int> v;
    for(int i = 0 ;i<= 100 ;i++)
    {
        v.push_back(i);
    }
    cout << accumulate(v.begin(),v.end(),0) << endl;//参数3是一个起始的加值，相当于结果加上参数3的值
}
```

#### fill

![image-20240211191050843](/home/future/.config/Typora/typora-user-images/image-20240211191050843.png)

```c++
void test()
{
    vector<int> v;
    v.resize(10);
    fill(v.begin(),v.end(),100);
}
```

### 常用集合算法

![image-20240211193144556](/home/future/.config/Typora/typora-user-images/image-20240211193144556.png)

#### set_intersection

```c++
void print(int val)
{
    cout << val << " ";
}

void test()
{
    vector<int> v;
    for(int i = 0; i<10;i++)
    {
        v.push_back(i);
    }
    vector<int> v1;
    for(int i =4;i<=7;i++)
    {
        v1.push_back(i);
    }
    vector<int> v2;
    v2.resize(min(v.size(),v1.size()));
    //返回交集结束的迭加器
    vector<int>:: iterator it=set_intersection(v.begin(),v.end(),v1.begin(),v1.end(),v2.begin());
    for_each(v2.begin(),it,print);
    cout << endl;
}
```

总结：

* 求交集的两个集合必须得是有序序列
* 目标容器开辟空间从两个容器中取小值
* 返回值是交集最后一个元素的位置

#### set_union

![image-20240211201720726](/home/future/.config/Typora/typora-user-images/image-20240211201720726.png)

```c++
void test()
{
    vector<int> v1;
    vector<int> v2;
    for(int i = 0; i < 10;i++) 
    {
        v1.push_back(i);
        v2.push_back(i+10);
    }
    vector<int> v3;
    v3.resize(v1.size()+v2.size());
    vector<int>::iterator it =set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());
    for_each(v3.begin(),it,print);
    cout << endl;
}

```

总结：

* 求并集的两个集合必须是有序序列
* 目标容器开辟空间需要两个容器相加
* set_union返回值是并集最后一个元素的迭加器

#### set_difference

![image-20240211202532244](/home/future/.config/Typora/typora-user-images/image-20240211202532244.png)

![image-20240211202644412](/home/future/.config/Typora/typora-user-images/image-20240211202644412.png)

  

```c++
void print(int val)
{
    cout << val << " ";
}

void test()
{
    vector<int> v1;
    vector<int> v2;
    for(int i =0;i<10;i++)
    {
        v1.push_back(i);
        v2.push_back(i+5);
    }
    vector<int> v3;
    v3.resize(max(v1.size(),v2.size()));
    vector<int>::iterator it =set_difference(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());
    for_each(v3.begin(),it,print);
    cout << endl;
}
```

总结：

* 求差集的两个集合必须是有序序列
* 目标容器开辟空间需要从两个容器取较大值
  * set_difference返回值即是差集中最后一个元素
