#include <iostream>
using namespace std;

// struct student
// {
//     char name[100];
//     int grade;

// };

class student
{
public:
    student pa();
    student()
    {
        cout << "默认构造" << endl;
    }
    student(int a)
    {
        grade= a;
    }
    student (const student &a)
    {
        grade = a.grade;
        cout << "拷贝构造" << endl;
    }
    
    void print()
    {
        if(grade>90)
        {
            cout << "A" << endl;
        }
    }
    ~student()
    {
        cout << "析构函数" <<endl;
    }
    int grade;
    string name;
};
int main()
{
    student s(100);
    cout << s.grade << endl;
    student s1(s);
    cout << s1.grade << endl;
    return 0;
}