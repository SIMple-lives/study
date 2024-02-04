#include <iostream>
#include "workmanger.cpp"
#include "employee.cpp"
#include "boss.cpp"
#include "manger.cpp"

int main()
{
    //实例化管理者对象
    WorkManger w;
    int input = 0;
    while(true)
    {
        w.Show_Menu();
        cout << "Enter input" << endl;
        cin>>input;
        switch(input)
        {
            case 0:
            w.ExitSystem(); break;
            return 0;
            case 1://Add
            w.Add_Emp(); 
            break;
            case 2://show
            w.Show_Info();
            break;
            case 3://delete
            w.Del_Emp();
            break;
            case 4://fix
            w.Mod_Emp();
            break;
            case 5://Find
            w.Find_Emp();
            break;
            case 6://Sort
            w.sort_Emp();
            break;
            case 7://Alldelete
            w.Clear_Emp();
            break;
            default:
            cout << "Error input    " << input << endl;
            break;
        }
    }
    return 0;