#include "boss.hpp"

Boss :: Boss(int id,string name,int Did)
{
    this->m_ID=id;
    this->m_Name=name;
    this->m_DeptId=Did;
}

void Boss::showInfo()
{
     cout << "职工编号： " << this->m_ID << endl;
    cout << "\t职工姓名: " << this->m_Name<<endl;
    cout << "\t岗位：" << this->getDeptName() <<endl;
    cout << "\t岗位职责: 摸大鱼"<<endl;
}

string Boss ::getDeptName()
{
    return string("老板");
}