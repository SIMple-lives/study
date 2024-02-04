#pragma once
#include <iostream>
#include <string>
#include "Worker.hpp"
using namespace std;

class Boss :public Worker
{
public:
    Boss(int id,string name,int Did);
    virtual void showInfo();
    virtual string getDeptName();
};