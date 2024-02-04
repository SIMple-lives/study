#include "workmanger.hpp"

WorkManger::WorkManger()
{
    //1.文件不存在
    ifstream ifs;
    ifs.open("empfile.txt",ios::in);
    if(!ifs.is_open())
    {
        //cout << "文件不存在" << endl;
        this->m_EmpNum=0;
        this->m_EmpArray=NULL;
        this->m_FileIsEmpty=true;
        ifs.close();
    }
    //文件存在，但为空,没有数据
    char ch;
    ifs>>ch;
    if(ifs.eof())
    {
        //cout << "文件为空" << endl;
        this->m_EmpNum=0;
        this->m_EmpArray=NULL;
        this->m_FileIsEmpty=true;
        ifs.close();
    }
    //3.文件存在，并前记录数据
    int num=this->get_EmpNum();
    //cout << "职工人数为： " << num <<endl;
    this->m_EmpNum=num; 
    this->m_EmpArray=new Worker*[this->m_EmpNum];
    this->InitEmp();
}

WorkManger::~WorkManger()
{
    if(this->m_EmpArray!=NULL)
    {
        for(int i=0;i<this->m_EmpNum;i++)
        {
            if(this->m_EmpArray[i]!=NULL)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i]=NULL;
            }
        }
        delete[] this->m_EmpArray;
    }
}

void WorkManger ::Show_Menu()
{
    cout << " —————————————————————————————————"<<endl;
    cout << "|********************************|"<<endl;
    cout << "\033[31m|***** 欢迎使用职工管理系统 *****|"<<endl;
    cout << "|*****       \033[32m0.Exit         *****|"<<endl;
    cout << "|*****        \033[33m1.Add         *****|"<<endl;
    cout << "|*****       \033[34m2.Show         *****|"<<endl;
    cout << "|*****      \033[35m3.Delete        *****|"<<endl;
    cout << "|*****      \033[36m4.Fix           *****|"<<endl;
    cout << "|*****       \033[36m5.Find         *****|"<<endl;
    cout << "|*****       \033[35m6.Sort         *****|"<<endl;
    cout << "|*****     \033[34m7.Alldelete      *****|"<<endl;
    cout << "\033[33m|********************************|"<<endl;
    cout << "\033[32m|********************************|"<<endl;
    cout << " —————————————————————————————————"<<endl;
}

void WorkManger ::ExitSystem()
{
    cout << "Exit system"<<endl;
    cout << "Welcome to next using" << endl;
    exit(0);
}

void WorkManger :: Add_Emp()
{
    cout << "Input add Num";
    int addnum=0;
    cin >> addnum;
    if(addnum>0)
    {
        int newSize=this->m_EmpNum+addnum;
        Worker ** newspace=new Worker*[newSize];
        if(this->m_EmpArray!=NULL)
        {
            for(int i=0;i<this->m_EmpNum;i++)
            {
                newspace[i]=this->m_EmpArray[i]; 
            }
        }
        for(int i=0;i<addnum;i++)
        {
            int id;
            string name;
            int Did;
            cout << "请输入第 " << i+1 << "员工的编号 " <<endl;
            cin>>id;
            cout << "请输入第" << i+1 << "员工的姓名" <<endl;
            cin>>name;
            cout << "请选择该" << i+1 << "员工的岗位" <<endl;
            cout << "1.普通员工" <<endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin>>Did;
            Worker *worker=NULL;
            switch(Did)
            {
                case 1:
                worker=new Employee(id,name,Did);
                break;
                case 2:
                worker=new Manger(id,name,Did);
                break; 
                case 3:
                worker=new Boss(id,name,Did);
                break;
                default :
                break;
            }
            newspace[this->m_EmpNum+i] = worker;
        }
            delete[] this->m_EmpArray;
            this->m_EmpArray=newspace;
            this->m_EmpNum=newSize;
            this->m_FileIsEmpty=false;
            cout << "Add suncess  " << addnum <<"  Worker"<<endl;
            this->save();
    }
    else
    {
        cout <<"Input Error" << endl;
    }
    system("clear");//清空屏幕
}

void WorkManger::save()
{   
    ofstream ofs;
    ofs.open("empfile.txt",ios::out);
    for(int i=0;i<this->m_EmpNum;i++)
    {
        ofs<<this->m_EmpArray[i]->m_ID<<endl;
        ofs<<this->m_EmpArray[i]->m_Name<<endl;
        ofs<<this->m_EmpArray[i]->m_DeptId<<endl;
    }
    ofs.close();
}

void WorkManger :: Show_Info()
{
    if(this->m_FileIsEmpty)
    {
        cout << "File is empty" << endl;
    }
    else
    {
        for(int i=0;i<this->m_EmpNum;i++)
        {
            this->m_EmpArray[i]->showInfo();
        }
    }
}

int WorkManger::get_EmpNum() 
{
    ifstream ifs;
    ifs.open("empfile.txt",ios::in);
    int id;
    string name;
    int Did;
    int num;
    while(ifs>>id&&ifs>>name&&ifs>>Did)
    {
        num++;
    }
    return num;
}

void WorkManger::InitEmp()
{
    ifstream ifs;
    ifs.open("empfile.txt",ios::in);
    int id;
    string name;
    int Did;
    int index=0;
    while (ifs>>id&&ifs>>name&&ifs>>Did)
    {
        Worker *worker=NULL;
        if(Did==1)
        {
            worker=new Employee(id,name,Did);
        }
        else if(Did==2)
        {
            worker=new Manger(id,name,Did);
        }
        else if(Did==3)
        {
            worker=new Boss(id,name,Did);
        }
        this->m_EmpArray[index++]=worker;
    }
    ifs.close();
}

int WorkManger::IsExit(int id) 
{
    int index=-1;
    for(int i=0;i<this->m_EmpNum;i++)
    {
        if(id==this->m_EmpArray[i]->m_ID)
        {
            index=i;
        }
    }
    return index;
}

void WorkManger ::Del_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "File is empty" << endl;
    }
    else
    {
        cout << "Input work^s id"<<endl;
        int id;
        cin>>id;
        int index=this->IsExit(id);
        if(index==-1)
        {
            cout << "People are dead" << endl;
        }
        else
        {
            Worker ** newspace=new Worker*[this->m_EmpNum-1];
            int j=0;
            for(int i=0;i<this->m_EmpNum;i++)
            {
                if(i==index)
                continue;
                newspace[j++]=this->m_EmpArray[i];
            }
            delete[] this->m_EmpArray;
            this->m_EmpArray=newspace;
            this->m_EmpNum=j;
            this->save();
            cout << "Delete   Success" << endl;
        }
    }
}

void WorkManger ::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在" << endl;
    }
    else
    {
        cout << "请输入修改职工的编号: " <<endl;
        int id;
        cin>>id;
        int index=this->IsExit(id);
        if(index==-1)
        {
            cout << "查无此人" << endl;
        }
        else
        {
            delete this->m_EmpArray[index];
            int newid;
            string name;
            int Did;
            cout << "查找到 ：" << id << " 号职工 ，请输入新的职工编号: "<<endl;
            cin>>newid;
            cout << "请输入新的姓名: "<< endl;
            cin >> name;
            cout << "请输入岗位： " << endl;
            cout << "1.普通员工" <<endl;
            cout << "2.经理" <<endl;
            cout << "3.老板" <<endl;
            cin>>Did;
            Worker *worker=NULL;
            switch(Did)
            {
                case 1:
                worker =new Employee(newid,name,Did);
                break;
                case 2:
                worker =new Manger(newid,name,Did);
                break;
                case 3:
                worker =new Boss(newid,name,Did);
            }
            this->m_EmpArray[index]=worker;
            cout << "Success" <<endl;
            this->save();
        }
    }
}

void WorkManger ::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "File is empty" << endl;
    }
    else
    {
        cout << "请输入查找的方式 :"<<endl;
        cout << "1.按照编号查找" << endl;
        cout << "2.按照姓名查找" << endl;
        int choice ;
        cin >> choice;
        bool flag=false;
        if(choice==1)
        {
            int findid=0;
            cout << "请输入查找人的编号" << endl;
            cin >> findid;
            for(int i=0;i<this->m_EmpNum;i++)
            {
                if(findid==this->m_EmpArray[i]->m_ID)
                {
                    this->m_EmpArray[i]->showInfo();
                    flag=true;
                }
            }
            if(flag==false)
            {
                cout << "查无此人"  << endl;
            }
        }
        else if(choice==2)
        {
            string findname;
            cout << "请输入查找人的姓名:  " << endl;
            cin>>findname;
            for(int i=0;i<this->m_EmpNum;i++)
            {
                if(findname==this->m_EmpArray[i]->m_Name)
                {
                    this->m_EmpArray[i]->showInfo();
                    flag=true;
                }
            }
             if(flag==false)
            {
                cout << "查无此人"  << endl;
            }
        }
        else 
        {
            cout << "选择错误 " << endl;
        }
    }
}

int partition(Worker **arr,int i,int j,int mod)
{
    Worker *work=arr[0];
    int x=arr[0]->m_ID;
    while(i<j)
    {
        if(mod==1)
        {
            while(i<j&&arr[j]->m_ID>=x)
            {
                j--;
            }
            if(i<j)
            {
                arr[i]=arr[j];
                i++;
            }
            while(i<j&&arr[i]->m_ID<x)
            {
                i++;
            }
            if(i<j)
            {
                arr[j]=arr[i];
                j--;
            }
        }
        else 
        {
            while(i<j&&arr[j]->m_ID<x)
            {
                j--;
            }
            if(i<j)
            {
                arr[i]=arr[j];
                i++;
            }
            while(i<j&&arr[i]->m_ID>=x)
            {
                i++;
            }
            if(i<j)
            {
                arr[j]=arr[i];
                j--;
            }
        }
    }
    arr[i]=work;
    return i;
}

void QuickSort(Worker ** arr,int i,int j,int mod)
{
    if(i<j)
    {
        int index = partition(arr,i,j,mod);
        QuickSort(arr,i,index-1,mod);
        QuickSort(arr,index+1,j,mod);
    }
}

void WorkManger ::sort_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "File is empty" << endl;
    }
    else
    {
        cout << "请选择排序的方式 ：" << endl;
        cout << "1. 升序            2.降序" <<endl;
        int choice=0;
        cin>>choice;
        if(choice==1)
        {
            QuickSort(this->m_EmpArray,0,this->m_EmpNum-1,choice);
        }
        else if(choice==2)
        {
            QuickSort(this->m_EmpArray,0,this->m_EmpNum-1,choice);
        }
        else
        {
            cout << "选择错误，请重新选择" << endl;
        }
        this->save();
        cout << "Success" << endl;
    }
}

void WorkManger ::Clear_Emp()
{
    cout << "确认清空 ????" << endl;
    cout << "1. 确认" << endl;
    cout << "2. 否  " << endl;
    int choice =0;
    cin >> choice;
    if(choice==1)
    {
        ofstream ofs;
        ofs.open("empfile.txt",ios::trunc);
        ofs.close();
        if(this->m_EmpArray!=NULL)
        {
            for(int i=0;i<this->m_EmpNum;i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i]=NULL;
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray=NULL;
        this->m_EmpNum=0;
        this->m_FileIsEmpty=true;
        cout << "Success"<< endl;
    }
}