#include <iostream>
using namespace std;
#include <string>



int main()
{

    return 0;
}

//字符串的查找和替换
//查找
// void test()
// {   
//     string str1="abcdefgde";
//     int pos=str1.find("de");//有的话返回对应的下标，没有返回 -1 
//     cout << pos << endl;
//     pos=str1.rfind("de");
//     cout << pos << endl;
//     //find是从左往右查找  rfind是从右往左查找
// }

// //替换
// void test1()
// {
//     string str1="abcdefg";
//     str1.replace(1,3,"11111");//从一号位置起  3个字符替换为 "11111"
//     cout << str1 << endl;
// }

// int main()
// {
//     test1();
//     return 0;
// }

//string 字符串拼接
// void test()
// {
//     string str1="我";
//     str1+="爱玩";
//     cout << str1 << endl;
//     str1+=':';
//     cout << str1 << endl;
//     string str2="LoL";
//     str1+=str2;
//     cout << str1 << endl;
//     string str3="I";
//     str3.append(" Love ");
//     cout << str3 << endl;
//     str3.append("game abcde",4);
//     cout << str3 << endl;
//     str3.append(str1);
//     cout << str3 << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//string 赋值操作
// void test()
// {
//     string str1;
//     str1="hello world!";
//     cout << str1 << endl;
//     string str2;
//     str2=str1;
//     cout << str2 << endl;
//     string str3;
//     str3='a';
//     cout << str3 << endl;
//     string str4;
//     str4.assign("hello C++!");
//     cout << str4 << endl;
//     string str5;
//     str5.assign("hello C++!",5);
//     cout << str5 << endl;
//     string str6;
//     str6.assign(str4);
//     cout << str6 << endl;
//     string str7;
//     str7.assign(7,'a');
//     cout << str7 << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//string 的构造函数
// void test()
// {
//     string s1;//默认构造
//     const char *str="Hello world!";
//     string s2(str);
//     cout << s2 << endl;
//     string s3( s2);
//     cout << s3 << endl;
//     char a='b';
//     string s4(10,a);
//     cout << s4 << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }