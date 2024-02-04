#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Worker.hpp"

class Manger : public Worker
{
public:
    Manger(int id,string name,int Did);
    virtual void showInfo();
    virtual string getDeptName();
};