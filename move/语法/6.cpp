#include <iostream>
using namespace std;
#include <string>
#include <fstream>

//二进制读文件
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

int main()
{
    test();
    return 0;
}

//二进制写文件
// class Person
// {
//     public:
//     char m_Name[64];
//     int m_Age;
// };

// void test()
// {
//     // ofstream ofs;
//     // ofs.open("Person.txt",ios::out|ios::binary);
//     ofstream ofs("Person.txt",ios::out|ios::binary);
//     Person p = { "张三" , 18 };
//     ofs.write((const char *)&p,sizeof(Person));
//     ofs.close();
// }

// int main()
// {
//     test();
//     return 0;
// }

//读文件
// void test()
// {
//     ifstream ifs;
//     ifs.open("test.txt",ios::in);
//     if(!ifs.is_open())
//     {
//         cout << "文件打开失败" << endl;
//         return;
//     }
//     //接下来读取数据
//     //1.first
//     // char buf[1024]={0};
//     // while(ifs >> buf)
//     // {
//     //     cout << buf << endl;
//     // }
//     //2.second
//     // char buf[1024]={0};
//     // while(ifs.getline(buf,1024))
//     // {
//     //     cout << buf << endl;
//     // }
//     //3.third
//     // string buf;
//     // while(getline(ifs,buf))
//     // {
//     //     cout << buf << endl;
//     // }
//     //4. fourth
//     char c;
//     while((c=ifs.get())!=EOF)
//     {
//         cout << c ;
//     }
//     ifs.close();
// }

// int main()
// {
//     test();
//     return 0;
// }

//写文件
// void test()
// {
//     //创建流对象
//     ofstream ofs;
//     //指定打开方式    
//     ofs.open("test.txt",ios::app);
//     //写内容
//     ofs << "张三" << endl;
//     ofs << "男" << endl;
//     ofs << "18" << endl;
//     ofs.close();
// }

// int main()
// {
//     test();
//     return 0;
// }