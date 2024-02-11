#include <iostream>
using namespace std;
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include <numeric>

//set_diffence
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

int main()
{
    test();
    return 0;
}

//set_union
// void print(int val)
// {
//     cout << val << " ";
// }

// void test()
// {
//     vector<int> v1;
//     vector<int> v2;
//     for(int i = 0; i < 10;i++) 
//     {
//         v1.push_back(i);
//         v2.push_back(i+10);
//     }
//     vector<int> v3;
//     v3.resize(v1.size()+v2.size());
//     vector<int>::iterator it =set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());
//     for_each(v3.begin(),it,print);
//     cout << endl;
// }
  
// int main()
// {
//     test();
//     return 0;
// }

//ser_intersection
// void print(int val)
// {
//     cout << val << " ";
// }

// void test()
// {
//     vector<int> v;
//     for(int i = 0; i<10;i++)
//     {
//         v.push_back(i);
//     }
//     vector<int> v1;
//     for(int i =4;i<=7;i++)
//     {
//         v1.push_back(i);
//     }
//     vector<int> v2;
//     v2.resize(min(v.size(),v1.size()));
//     vector<int>:: iterator it=set_intersection(v.begin(),v.end(),v1.begin(),v1.end(),v2.begin());
//     for_each(v2.begin(),it,print);
//     cout << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//accumulate
// void test()
// {
//     vector<int> v;
//     for(int i = 0 ;i<= 100 ;i++)
//     {
//         v.push_back(i);
//     }
//     cout << accumulate(v.begin(),v.end(),0) << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//replace_if
// class compare
// {
// public:
//     bool operator()(int val)
//     {
// 		return val>20;
//     }
// };

// void myprint(int val)
// {
// 	cout << val << " ";
// }

// void test()
// {
//  	vector<int> v;
//     v.push_back(30);
//     v.push_back(10);
//     v.push_back(40);
//     v.push_back(20);
//     v.push_back(10);
//     v.push_back(60);
//     v.push_back(70);
//     v.push_back(90);
//     for_each(v.begin(),v.end(),myprint);
//     cout << endl;
//     replace_if(v.begin(),v.end(),compare(),200);
//     for_each(v.begin(),v.end(),myprint);
//     cout << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//merge
// void print(int val)
// {
//     cout << val << " ";
// }

// void test()
// {
//     vector<int>v1;
//     vector<int>v2;
//     for(int i=0;i<10;i++)
//     {
//         v1.push_back(i);
//         v2.push_back(i+3);
//     }
//     vector<int> v3;
//     v3.resize(v1.size()+v2.size());
//     merge(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());
//     for_each(v3.begin(),v3.end(),print);
//     cout << endl;
//     random_shuffle(v1.begin(),v1.end());
//     for_each(v1.begin(),v1.end(),print);
//     cout << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//sort
// void print(int val)
// {
//     cout << val << " ";
// }

// class compare
// {
// public:
//     bool operator()(int a,int b) const
//     {
//         return a > b;
//     }
// };

// void test()
// {
//     vector<int> v;
//     v.push_back(1);
//     v.push_back(3);
//     v.push_back(2);
//     v.push_back(5);
//     v.push_back(4);
//     sort(v.begin(), v.end());
//     for_each(v.begin(), v.end(), print);
//     cout << endl;
//     sort(v.begin(), v.end(),greater<int>());
//     for_each(v.begin(), v.end(), print);
//     cout << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//adjacent_find
// void test()
// {
//     vector<int> v;
//     v.push_back(0);
//     v.push_back(2);
//     v.push_back(0);
//     v.push_back(3);
//     v.push_back(1);
//     v.push_back(4);
//     v.push_back(3);
//     v.push_back(3);
//     cout << *(adjacent_find(v.begin(),v.end())) << endl;
// }

// int main()
// {
//     test();
//     return 0;
// }

//find_if
// class GreaterFive
// {
// public:
//     bool operator()(int val)
//     {
//         return val>5;
//     }
// };

// void test01()
// {
//     vector<int> v;
//     for(int i=0;i<10;i++)
//     {
//         v.push_back(i);
//     }
//     if(find_if(v.begin(),v.end(),GreaterFive())!=v.end())
//     {
//         cout << *(find_if(v.begin(),v.end(),GreaterFive())) << endl;
//     }
//     else
//     {
//         cout << "没有找到" << endl;
//     }
// }

// class Person
// {
// public:
//     Person(string name ,int age)
//     {
//         this->m_Name=name;
//         this->m_Age=age;
//     }
//     string m_Name;
//     int m_Age;
// };

// class Greater20
// {
// public:
//     bool operator()(Person &a)
//     {
//         return a.m_Age >20;
//     }
// };

// void test02()
// {
//     vector<Person> v;
//     Person p1("aaa",10);
//     Person p2("bbb",20);
//     Person p3("ccc",30);
//     Person p4("ddd",40);
//     v.push_back(p1);
//     v.push_back(p2);
//     v.push_back(p3);
//     v.push_back(p4);
//     if(find_if(v.begin(),v.end(),Greater20())!=v.end())
//     {
//         cout << find_if(v.begin(),v.end(),Greater20())->m_Name << " " << find_if(v.begin(),v.end(),Greater20())->m_Age << endl;
//     }
//     else
//     {
//         cout << "没有找到" << endl;
//     }
// }

// int main()
// {
//     test02();
//     return 0;
// }

//Find
// class Person
// {
// public:
//     Person(string name,int age)
//     {
//         this->m_Name=name;
//         this->m_Age=age;
//     }
//     bool operator==(const Person &o)
//     {
//         if(this->m_Name==o.m_Name && this->m_Age==o.m_Age) 
//         return true;
//         return false;
//     }
//     string m_Name;
//     int m_Age;
// };

// void test()
// {
//     vector<Person> v;
//     Person p1("aaa",10);
//     Person p2("abb",20);
//     Person p3("baa",30);
//     Person p4("bbb",40);
//     v.push_back(p1);
//     v.push_back(p2);
//     v.push_back(p3);
//     v.push_back(p4);
//     Person p5("bbb",50);
//     if(find(v.begin(),v.end(),p5)==v.end())
//     {
//         cout << "没找到" << endl;
//     }
//     else
//     {
//         cout << find(v.begin(),v.end(),p2)->m_Name <<" " << find(v.begin(),v.end(),p2)->m_Age << endl;
//     }
// }

// int main()
// {
//     test();
//     return 0;
// }