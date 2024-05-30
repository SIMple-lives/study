#include "../head/head.hpp"
#include "../head/define.hpp"
#include "../cil/file.hpp"

void Users::Update(const std::string& id, const std::string& username, const std::string& password, const std::string& questions, const std::string& que_ans, const std::string& telephone)
{
    this->setid(id);
    this->setusername(username);
    this->setpassword(password);
    this->setquestions(questions);
    this->setque_ans(que_ans);
    this->settelephone(telephone);
    this->setstatus(OFFLINE);
}
void Users::Singup(int fd) 
{
    bool registered = false;
    while (!registered) 
    {
        std::string username, password, questions, que_ans, telephone;
        std::cout << "请输入用户名 :" << std::endl;
        std::cin >> username;
        std::cout << "请输入密码 :" << std::endl;
        std::cin >> password;
        std::cout << "请输入你的密保问题 :" << std::endl;
        std::cin >> questions;
        std::cout << "请输入密保答案 :" << std::endl;
        std::cin >> que_ans;
        std::cout << "请输入电话号码 :" << std::endl;
        std::cin >> telephone;
        nlohmann::json sign_request = 
        {
            {"username", username},
            {"password", password},
            {"questions", questions},
            {"que_ans", que_ans},
            {"telephone", telephone},
            {"status", OFFLINE},
            {REQUEST,SIGNUP}
        };
        Sen s;
        s.send_cil(fd, sign_request.dump());
        std::cout << "注册中..." << std::endl;
        Rec r;
        int status = r.recv_ok(fd);
        std::cout << "status : " << status << std::endl;
        if (status == SUCCESS) 
        {
            registered = true;
            std::cout << "注册成功" << std::endl;
            registered = true;
            std::string id;
            r.recv_cil(fd, id);
            std::cout << "\033[31m你的账号id为 : " << id << "\033[0m "<< std::endl;
            Update(id, username, password, questions, que_ans, telephone);
            int ok;
            do {
                std::cout << "\033[31m请确认注册信息是否记住 : \033[0m" << std::endl;
                std::cout << "\033[31m用户名 : " << username << "\033[0m" << std::endl;
                std::cout << "\033[31m密码 : " << password << "\033[0m" << std::endl;
                std::cout << "\033[31mid: " << id << "\033[0m" << std::endl;
                std::cout << "Are You Remember ?";
                std::cin >> ok;
            }while (!ok);
            system("clear");
        } 
        else if(status == FAILURE) 
        {
            std::cout << "注册失败，请重新尝试" << std::endl;
        }
        else 
        {
            std::cout << "用户名已存在 !" << std::endl;
        }
    }
}

std::string getPasswordFromConsole()
{
    struct termios oldt, newt;
    std::string password;

    // 获取当前终端属性
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // 禁止回显和缓冲
    newt.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);

    // 应用新的终端属性
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // 从标准输入读取密码，以*显示
    char ch;
    while (1)
    {
        if (read(STDIN_FILENO, &ch, 1) < 0)
            break;
        if (ch == '\n' || ch == '\r')
            break;
        password += ch;
        std::cout << '*';
        std::cout.flush();
    }

    // 恢复终端属性
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl; // 手动换行，因为输入密码时没有回显，需要手动换行

    return password;
}

void Users::Login(int fd)
{
    std::string id;
    std::cout << "请输入你的账号id : " << std::endl;
    std::cin >> id;
    std::string password;
    std::cout << "请输入你的密码 : " << std::endl;
    password = getPasswordFromConsole();
    nlohmann::json login_request = {
        {"id",id},
        {"password", password},
        {REQUEST,LOGIN}};
    Sen s;
    s.send_cil(fd, login_request.dump()); 
    Rec r;
    int status = r.recv_ok(fd);
    std::cout << "\033[31mstatus : " << status << "\033[0m " <<std::endl;
    if(status == SUCCESS)
    {
        std::cout << "登陆成功 " << std::endl;
        std::string info;
        r.recv_cil(fd, info);
        nlohmann::json info_json = nlohmann::json::parse(info);
        Update(id, info_json["username"], info_json["password"], info_json["questions"],info_json["que_ans"], info_json["telephone"]) ;
        this->Work(fd);
    }
    else if(status == NEXIST) 
    {
        std::cout << "账号不存在" << std::endl;
    }
    else if ( status == ALREADYLOGIN)
    {
        std::cout << "账号已登录" << std::endl;
    }
    else if(status == PASSWORDERROR)
    {
        std::cout << status << std::endl;
        std::cout << "密码错误" << std::endl;
        //system("clear");
        system("echo \"IF FIND\" | figlet | boxes | lolcat");
        int ok;
        std::cin>>ok;
        if(ok)
        {
            Find(fd,id);
        }
    }
    else 
    {
        std::cout << status << std::endl;
        std::cout << "其他问题 , 重新登陆" << std::endl;
    }
}

void Users::Logout(int fd)
{
    std::string id;
    std::cout << "请输入你的账号id : " << std::endl;
    std::cin >> id;
    std::string password;
    std::cout << "请输入你的密码 : " << std::endl;
    password = getPasswordFromConsole();
    nlohmann::json login_request = {
        {"id", id},
        {"password", password},
        {REQUEST,LOGOUT}};
    Sen s;
    s.send_cil(fd, login_request.dump()); 

    Rec r;
    int status = r.recv_ok(fd);
    std::cout << status << std::endl;
    if(status == SUCCESS)
    {
        system("clear");
        system("echo \"SUCCESS\" | figlet | boxes -d c | lolcat") ;
    }
    else if(status == NEXIST) 
    {
        std::cout << "账号不存在" << std::endl;
    }
    else if(status == ALREADYLOGIN)
    {
        std::cout << "账号已登录" << std::endl;
    }
    else if(status == PASSWORDERROR) 
    {
        std::cout << "密码错误" << std::endl;
    }
    else 
    {
        std::cout << "其他问题 , 重新注销" << std::endl;
    }
}

void Users::Find(int fd,std::string id)
{
    nlohmann::json find_request = {
        {"id", id},
        {REQUEST,FINDPASSWORDSA}};
    Sen s;
    s.send_cil(fd, find_request.dump()); 

    Rec r;
    int status = r.recv_ok(fd);
    
    if(status == SUCCESS)
    {
        std::string questions;
        r.recv_cil(fd, questions);
        std::cout << "密保问题 : " << questions << std::endl;
        std::string que_ans;
        std::cout << "请输入密保答案 : " << std::endl;
        std::cin >> que_ans;
        nlohmann::json Find_request = {
            {"id", id},
            {"que_ans", que_ans},
            {REQUEST,FINDPASSWORDSB}};
        s.send_cil(fd, Find_request.dump());
        int status = r.recv_ok(fd);
        std::cout << "\033[31mstatus : " << status << "\033[0m" << std::endl;
        if(status == SUCCESS)
        {
            std::cout << "密保答案正确" << std::endl;
            std::string password;
            r.recv_cil(fd, password);
            std::cout << "密码 : " << password << std::endl;
        }
        else if(status == PASSWORDERROR)
        {
            std::cout << "密保答案错误" << std::endl;
        }
    }
}

void Users::Exit(int fd)
{
    nlohmann::json exit_request = {
        {REQUEST,EXIT}};
    Sen s;
    s.send_cil(fd, exit_request.dump());
}



void Users::Work(int fd)
{
    int choice =0;
    User_work user_work(fd,this->id);
    do 
    {
        this->showUser();
        std::cin >> choice;
        switch (choice)
        {
            case 1:
                user_work.AddFriend();
                break;
            case 2:
                user_work.ViewFriendRequest();
                break;
            case 3:
                user_work.PrivateChat();
                break;
            case 4:
                user_work.ViewFriends();
                break;
            case 5:
                user_work.ViewFriendInfo();
                break;
            case 6:
                user_work.BlockFriend();
                break;
            case 7:
                user_work.ViewBlockedList();
                break;
            case 8:
                user_work.DeleteFriend();
                break;
            case 9:
                user_work.ViewPersonalInfo();
                std::cout << "dsadasda" << std::endl;
                break;
            case 10:
                user_work.GroupChat();
                break;
            case 11:
                user_work.Refresh();
                break;
            case 12:
            {
                // user_work.ViewFriends();
                // user_work.List_Group(this->id, fd);
                File f(fd,this->id);
                f.Run();
                break;
            }
            case 13: 
                user_work.Quit();
                return;
            default:
                //system("clear");
                std::cout << "Invalid choice" << std::endl;
                std::cout << "IF YOU WANT TO EXIT ?" << std::endl;
                int ok;
                std::cin >> ok;
                if(ok)
                {
                    choice = 0;
                    user_work.Quit();
                }
                break;
        }
    }while (choice);
}