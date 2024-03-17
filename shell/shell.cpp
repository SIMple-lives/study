#include "func.cpp"

int main()
{
    int num = 1;
    Shell mysh;
    mysh.setsignal();   
    mysh.setEOF();
    while(num)
    {
        mysh.print();
        mysh.setlinebuf();
        string t = mysh.retlinebuf();
        if(t.empty())
        {
            cout << "No input" << endl;
        }
        else if(t.rfind("exit")!=string::npos)
        {
            break;
        }
        else if(t.find("!")==0)
        {
            string keyword = t.substr(1); //获取去除感叹号的关键字
            mysh.searchAndReplay(keyword);
        }
        else if(t.find("clear")==0)
        {
            mysh.addHistory(t);
            // cout << "\033[2J\033[1;1H";//通过转义序列清除终端，但只能清楚当次的命令
            system("clear");
            num++;
        }
        else
        {
            mysh.addHistory(t);
            num++;
        }
        mysh.parse(t);
        if(num%3==0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
            cout << " History Order :" << endl;
            mysh.printHistory();
        }
    }
    return 0;
}