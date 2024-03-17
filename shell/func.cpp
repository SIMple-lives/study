#include "shell.hpp"

void Shell::print()
{   cout << "----------------------------------------------------------------------------" << endl;
    cout << "           ___                                                     ___" << endl;
    cout << "  ______  /  /___       ______  _____  ___   ___       ____  _____/  /___" << endl;
    cout << " /  __  \\/  __   \\     /  ___ - ___  \\/  /  /  /     /_   / /  __/  __   \\" << endl;
    cout << "/  /_/  /  /  /  /    /  /  /  /  /  /  /__/  /       /  /_(__  )  /  /  /" << endl;
    cout << "\\______/__/  /__/    /__/  /__/  /__/\\____,  /       /____/____/__/  /__/" << endl;
    cout << "                                    /_______/" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    char cwd [1024];
    auto now = chrono::system_clock::now();//返回当前的时间
    time_t time = chrono::system_clock::to_time_t(now);//将time_t point转换为time_t类型
    tm* timeinfo = std::localtime(&time);//将time_t转换为本地时间年月日,并存储在timeinfo中
    char timeStr[9];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", timeinfo);
    //std::strftime()将std::tm结构的时间信息格式化为字符串，并将结果存储在指定的字符数组中。这里使用"%H:%M:%S"作为格式字符串
    //，它表示小时、分钟和秒的格式。timeStr是目标字符数组，sizeof(timeStr)用于指定数组的大小，
    //timeinfo是包含时间信息的std::tm结构的指针。
    cout << "# future @ future-arch in " << getcwd(cwd,1024) << " [" << timeStr << "]" << endl;
    cout << "$ " ;
    fflush(stdout);
}

void Shell ::setlinebuf()
{
    getline(cin,this->linebuf);
}

string Shell::retlinebuf ()
{
    return this->linebuf;
}

void Shell:: setsignal()
{
    signal(SIGINT, SIG_IGN);//忽略ctrl+c的操作
}

bool Shell ::isempty() 
{
    if(this->linebuf.empty())
    {
        return true;
    }
    return false;
}

void Shell::addHistory(const string& line)
{
    for(vector<string>::iterator it = history.begin(); it != history.end();it++)
    {
        if((*it).compare(line) == 0)
        return ;
    }
    history.push_back(line);
}

void Shell ::setEOF()
{
    struct termios term;//存储终端的相关信息
    tcgetattr(STDIN_FILENO, &term);//获取相关信息，并存入结构体
    term.c_cc[VEOF] = _POSIX_VDISABLE;//禁止使用EOF
    tcsetattr(STDIN_FILENO, TCSANOW, &term);//将设置存入终端
}

void Shell::printHistory()
{
    for(vector<string>::iterator it = this->history.begin(); it != this->history.end();it++)
    {
        cout << *it << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
}

void Shell::searchAndReplay(const string& keyword)
{
    for (const string& line : history)
    {
        if (line.find(keyword) != string::npos)
        {
            cout << "Replaying: " << line << endl;
            linebuf = line;
            break;
        }
    }
}

void Shell::parse(string& s)
{
    vector<vector<string>> tokens;
    istringstream iss(s);//可方便的从字符串中读取数据
    string root;
    while (getline(iss, root, '|'))//将s以|分割开
    {
        istringstream root_iss(root);
        vector<string> root_tokens;
        string token;
        while (root_iss >> token)//将单个命令以空格分隔开
        {
            root_tokens.push_back(token);
        }

        tokens.push_back(root_tokens);
    }
    if (tokens.size() == 1)
    {
        vector<string>& command = tokens[0];
        if (command[0] == "cd")
        {
            mycd(command);
        }
        else
        {
            executeCommand(command);
        }
    }
    else if (tokens.size() > 1)
    {
        int numPipes = tokens.size() - 1;
        vector<int> pipefds(2 * numPipes, 0); // 用于存储管道的文件描述符
        for (int i = 0; i < numPipes; ++i)
        {
            if (pipe(pipefds.data() + i * 2) < 0)//挨个创建管道
            {
                perror("pipe()");
                exit(1);
            }
        }
        int commandIndex = 0;
        for (auto& command : tokens)
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("fork()");
                exit(1);
            }
            if (pid == 0)
            {
                // 子进程
                if (commandIndex != 0) // 不是第一个命令，读取前一个管道的输出
                {
                    if (dup2(pipefds[(commandIndex - 1) * 2], STDIN_FILENO) < 0)
                    {
                        perror("dup2()");
                        exit(1);
                    }
                }
                if (commandIndex != numPipes) // 不是最后一个命令，将输出写入下一个管道
                {
                    if (dup2(pipefds[commandIndex * 2 + 1], STDOUT_FILENO) < 0)
                    {
                        perror("dup2()");
                        exit(1);
                    }
                }
                // 关闭所有管道的文件描述符
                for (int i = 0; i < 2 * numPipes; ++i)
                {
                    close(pipefds[i]);
                }
                if (command[0] == "cd")
                {
                    mycd(command);
                }
                else
                {
                    executeCommand(command);
                }
                exit(0);
            }
            else
            {
                // 父进程
                ++commandIndex;
            }
        }
        // 关闭所有管道的文件描述符
        for (int i = 0; i < 2 * numPipes; ++i)
        {
            close(pipefds[i]);
        }

        // 等待所有子进程结束
        for (size_t i = 0; i < tokens.size(); ++i)
        {
            wait(NULL);
        }
    }
}

void Shell::mycd(vector<string>& s)
{
    if (s.size() > 2)
    {
        cout << "cd: 函数调用参数过多" << endl;
        return;
    }
    else if (s.size() == 1 || s[1].compare("~") == 0)
    {
        const char* homeDir = getenv("HOME");
        if (homeDir)
        {
            if (chdir(homeDir) == -1)
            {
                perror("chdir()");
            }
        }
        else
        {
            cout << "cd: 无法获取家目录路径" << endl;
            return;
        }
    }
    else if (s[1].compare("-") == 0)
    {
        const char* lastDir = getenv("OLDPWD");
        if (lastDir)
        {
            if (chdir(lastDir) == -1)
            {
                perror("chdir()");
            }
        }
        else
        {
            cout << "cd: 无法找到上一个路径" << endl;
        }
    }
    else
    {
        const char* path = s[1].c_str();
        if (chdir(path) == -1)
        {
            perror("chdir()");
        }
    }
    // 更新环境变量 OLDPWD
    char* currentDir = get_current_dir_name();//获取当前工作目录的路径
    if (currentDir)
    {
        if (setenv("OLDPWD", currentDir, 1) == -1)//设置环境变量
        {
            perror("setenv()");
        }
        free(currentDir);
    }
    else
    {
        perror("get_current_dir_name()");
    }
}

void Shell::executeCommand(vector<string>& command)
{
    pid_t pid;
    fflush(NULL);
    pid = fork();
    if (pid < 0)
    {
        perror("fork()");
    }
    bool success = false;
    if(command.back()=="&")
    {
        command.pop_back();
        success = true;
    }
    if (pid == 0)
    {
        vector<char*> args;
        vector<int> outputFds; // 存储输出文件描述符的容器
        for (size_t i = 0; i < command.size(); ++i)
        {
            if (command[i] == ">") // 输出重定向：覆盖写入文件
            {
                int fd = open(command[i + 1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror("open()");
                    exit(1);
                }
                outputFds.push_back(fd); // 将新的文件描述符添加到容器中
                dup2(fd, STDOUT_FILENO);
                close(fd);
                i++;
            }
            else if (command[i] == ">>") // 输出重定向：追加写入文件
            {
                int fd = open(command[i + 1].c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1)
                {
                    perror("open()");
                    exit(1);
                }
                outputFds.push_back(fd); // 将新的文件描述符添加到容器中
                dup2(fd, STDOUT_FILENO);
                close(fd);
                i++;
            }
            else if (command[i] == "<") // 输入重定向
            {
                int fd = open(command[i + 1].c_str(), O_RDONLY);
                if (fd == -1)
                {
                    perror("open()");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                i++;
            }
            else if (command[i] == "<<") // Here文档
            {
                string delimiter = command[i + 1];
                string inputText;

                while (getline(cin, inputText))
                {
                    if (inputText == delimiter)
                        break;
                    inputText += "\n";
                    write(STDIN_FILENO, inputText.c_str(), inputText.size());
                }

                i++;
            }
            else
            {
                args.push_back(const_cast<char*>(command[i].c_str()));
            }
        }

        args.push_back(nullptr); // execvp 需要以 nullptr 结尾的参数数组
        execvp(args[0], args.data());

        // execvp 执行失败时才会执行到这里
        perror("execvp()");
        exit(1);
    }
    else
    {
        bool runInBackground = false;
        if (!command.empty() && success==true)
        {
            runInBackground = true;
            vector<string> commandWithoutAmpersand(command.begin(), command.end());
            commandWithoutAmpersand.shrink_to_fit();
            cout << "Child process ID: " << pid << endl;
            return;
        }
        wait(NULL); // Wait for the child process to finish
    }
}
