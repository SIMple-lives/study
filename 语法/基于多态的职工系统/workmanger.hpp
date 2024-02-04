#pragma onece
#include <iostream>
#include <string>
using namespace std;
#include "Worker.hpp"
#include "manger.hpp"
#include "boss.hpp"
#include "employee.hpp"

#include <fstream>



//管理类
//1.与用户沟通
//2.对职工进行增删改查
//3.与文件的读写交互
class WorkManger
{
public:
    WorkManger();
    void Show_Menu();
    void ExitSystem();  
    //记录人数
    int m_EmpNum;
    Worker ** m_EmpArray;
    void Add_Emp();
    void save();
    void Show_Info();
    bool m_FileIsEmpty;
    int get_EmpNum();
    void InitEmp();
    void Del_Emp();
    int IsExit(int id);
    void Mod_Emp();
    void Find_Emp();
    void sort_Emp();
    void Clear_Emp();
    ~WorkManger();
};

