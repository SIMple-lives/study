#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Worker.hpp"

class Employee : public Worker 
{
public:
    Employee(int id,string name,int Did);
    virtual void  showInfo();
    virtual string getDeptName();
};