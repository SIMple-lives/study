#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) 
    {
        std::cerr << "Failed to create pipe." << std::endl;
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) 
    {
        std::cerr << "Failed to fork." << std::endl;
        return 1;
    } 
    else if (pid1 == 0) 
    { // Child process 1
        close(pipefd[0]); // Close the read end of the pipe

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // Close the write end of the pipe

        // Execute the command
        execlp("ls", "ls", "-l", NULL);

        // If execlp fails, the following code will be executed
        std::cerr << "Failed to execute command." << std::endl;
        return 1;
    }

    pid_t pid2 = fork();
    if (pid2 == -1) 
    {
        std::cerr << "Failed to fork." << std::endl;
        return 1;
    } 
    else if (pid2 == 0) 
    { // Child process 2
        close(pipefd[1]); // Close the write end of the pipe

        // Redirect stdin to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // Close the read end of the pipe

        // Execute the command
        execlp("grep", "grep", "list", NULL);

        // If execlp fails, the following code will be executed
        std::cerr << "Failed to execute command." << std::endl;
        return 1;
    }

    close(pipefd[0]); // Close the read end of the pipe
    close(pipefd[1]); // Close the write end of the pipe

    // Wait for both child processes to finish
    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);

    return 0;
}

// class Shell 
// {
// public:
//     void print();
//     void setlinebuf();
//     std::string retlinebuf();
//     void addHistory(const std::string& line);
//     void handleArrowKey(int key);
//     void printHistory();
//     void initindex();
// private:
//     std::string linebuf;
//     std::vector<std::string> history;
//     int historyIndex;
// };

// void Shell::initindex() 
// {
//     historyIndex = history.size(); // Set history index to the end of history
// }

// void Shell::handleArrowKey(int key) 
// {
//     if (key == KEY_UP) 
//     { // Up arrow
//         if (historyIndex > 0) 
//         {
//             historyIndex--;
//         }
//     } 
//     else if (key == KEY_DOWN) 
//     { // Down arrow
//         if (historyIndex < history.size()) {
//             historyIndex++;
//         }
//     }

//     // Display the corresponding history entry
//     if (historyIndex < history.size()) 
//     {
//         linebuf = history[historyIndex];
//     } 
//     else 
//     {
//         linebuf = "";
//     }
// }

// void Shell::printHistory() 
// {
//     for (const std::string& line : history) 
//     {
//         std::cout << line << std::endl;
//     }
// }

// void Shell::addHistory(const std::string& line) 
// {
//     history.push_back(line);
// }

// std::string Shell::retlinebuf() {
//     return linebuf;
// }

// void Shell::setlinebuf() {
//     std::getline(std::cin, linebuf);
// }

// void Shell::print() {
//     std::cout << "$ ";
//     std::cout.flush();
// }

// int main() {
//     Shell mysh;
//     mysh.initindex(); // Initialize history index to an invalid value
//     initscr();
//     keypad(stdscr, TRUE); // Enable keypad mode for capturing arrow keys
//     noecho(); // Don't print input characters
//     curs_set(0); // Hide the cursor

//     while (true) {
//         mysh.print();
//         int key = getch(); // Read a character

//         if (key == KEY_UP || key == KEY_DOWN) {
//             mysh.handleArrowKey(key);
//         } else if (key == '\n') {
//             std::string input = mysh.retlinebuf();
//             if (!input.empty()) {
//                 mysh.addHistory(input);
//                 mysh.initindex(); // Reset history index
//             }
//             mysh.setlinebuf();
//         } else {
//             mysh.setlinebuf();
//         }

//         clear(); // Clear the screen
//     }

//     endwin(); // End ncurses mode
//     mysh.printHistory();
//     return 0;
// }

// #include <iostream>
// using namespace std;
// #include <unistd.h>
// #include <sys/types.h>
// #include <wait.h>
// #include <sys/wait.h>
// #include <string>
// #include <string.h>
// #include <sstream>
// #include <vector>
// #include <ctime>
// #include <chrono>
// #include <readline/readline.h>
// #include <stdlib.h>

// int main()
// {
//     char *input=readline("input");
//     if(input!=NULL)
//     {
//         cout << input << endl;
//     }
//     else
//     {
//         cout << "Error: " << endl;
//     }
//     return 0;
// }

// void print()
// {
//     cout << "\033[32m           ___                                                     ___" << endl;
//     cout << "\033[32m  ______  /  /___       ______  _____  ___   ___       ____  _____/  /___" << endl;
//     cout << "\033[32m /  __  \\/  __   \\     /  ___ - ___  \\/  /  /  /     /_   / /  __/  __   \\" << endl;
//     cout << "\033[32m/  /_/  /  /  /  /    /  /  /  /  /  /  /__/  /       /  /_(__  )  /  /  /" << endl;
//     cout << "\033[32m\\______/__/  /__/    /__/  /__/  /__/\\____,  /       /____/____/__/  /__/" << endl;
//     cout << "\033[32m                                    /_______/" << endl;
//     char cwd [1024];
//     auto now = chrono::system_clock::now();//返回当前的时间
//     time_t time = chrono::system_clock::to_time_t(now);//将time_t point转换为time_t类型
//     tm* timeinfo = std::localtime(&time);//将time_t转换为本地时间年月日,并存储在timeinfo中
//     char timeStr[9];
//     strftime(timeStr, sizeof(timeStr), "%H:%M:%S", timeinfo);
//     //std::strftime()将std::tm结构的时间信息格式化为字符串，并将结果存储在指定的字符数组中。这里使用"%H:%M:%S"作为格式字符串
//     //，它表示小时、分钟和秒的格式。timeStr是目标字符数组，sizeof(timeStr)用于指定数组的大小，
//     //timeinfo是包含时间信息的std::tm结构的指针。
//     cout << "# future @ future-arch in " << getcwd(cwd,1024) << " [" << timeStr << "]" << endl;
//     cout << "$ " ;
// }

// void parse(string &s)
// {
//     istringstream iss(s);
//     string token;
//     vector<string> tokens;
//     while(getline(iss,token,' '))
//     {
//         tokens.push_back(token);
//     }
//     for(vector<string>::iterator it = tokens.begin(); it != tokens.end();it++)
//     {
//         cout <<*it << endl;
//     }
// }

// int main()
// {   
//     string linebuf ;
//     while(1)
//     {   
//         print();
//         if(getline(cin,linebuf))
//         {
//             parse(linebuf);
//         }
//         else
//         {
//             break;
//         }
//     }
//     return 0;
// }

// int main()
// {
//     while(1)
//     {
//         print();//打印提示
//         getline();//获取命令
//         parse();//解析命令
//         if()//判断内外部命令
//         {

//         }
//         else
//         {
//             fork()
//         }
//     }
//     return 0;
// }

// int main()
// {
//     cout << "Begin!" << endl;
//     fflush(NULL);
//     pid_t pid = fork();
//     int status ;
//     if(pid<0)
//     {
//         perror("fork");
//         exit(1);
//     }
//     if(pid==0)
//     {
//         execl("/bin/sleep","sleep","100",NULL);
//         perror("exec");
//         exit(1);
//     }
//     wait(&status);
//     cout << "End" << endl;
//     return 0;
// }

// int main()
// {
//     cout << "Begin!" << endl;
//     fflush(NULL);
//     pid_t pid = fork();
//     int status ;
//     if(pid<0)
//     {
//         perror("fork");
//         exit(1);
//     }
//     if(pid==0)
//     {
//         execl("/bin/date","date","+%s",NULL);
//         perror("exec");
//         exit(1);
//     }
//     wait(&status);
//     cout << "End" << endl;
//     return 0;
// }

// int main()
// {
//     cout << "Begin!" << endl;
//     fflush(NULL);
//     execl("/bin/date","date","+%s",NULL);
//     perror("execl()");
//     exit(1);
//     cout << "End " << endl;
//     return 0;
// }

// int main()
// {
//     cout << getenv("PATH") << endl;
//     return 0;
// }

// extern char ** environ;
// int main()
// {
//     for(int i=0;environ[i]!=NULL;i++)
//     {
//         cout << environ[i] << endl;
//     }
//     return 0;
// }

// void f1()
// {
//     cout << "================" << endl;
// }

// void f2()
// {
//     cout << "f2 is working " << endl;
// }

// void f3()
// {
//     cout << "f3 is working " << endl;
// }

// int main()
// {
//     cout << "Welcome" << endl;
//     atexit(f1);
//     atexit(f2);
//     atexit(f3);
//     cout << "End" << endl;
//     return 0;
// }

// int main()
// {
//     pid_t pid ;
//     int i,j,mark;
//     for(i=3000000;i<3000200;i++)
//     {
//         pid = fork();
//         if(pid<0)
//         {
//             perror("fork");
//         }
//         if(pid==0)
//         {
//             mark=1;
//             for(j=2;j<i/2;j++)
//             {
//                 if(i%j==0)
//                 {
//                     mark=0;
//                     break;
//                 }
//             }
//             if(mark==1)
//             {
//                 cout << i <<endl;
//             }

//             exit(0);
//         }
//     }
    // int st;
    // for(int i=3000000;i<3000200;i++)
    // {
    //     wait(&st);
    // }
//     return 0;
// }

// int main()
// {
//     int n;
//     int fd[2];
//     pid_t pid;
//     char line[1024];
//     if(pipe(fd)<0)
//     {
//         cout << "Error" << endl;
//     }
    
//     if((pid=fork())<0)
//     {
//         perror("fork");
//     }
//     else if(pid>0)
//     {
//         close (fd[0]);
//         write(fd[1],"hello world!" ,13);
//     }
//     else
//     {
//         close (fd[1]);
//         n=read(fd[0],line,1024);
//         write(STDOUT_FILENO,line,n);
//         cout << endl;
//         cout << line << endl;
//     }
//     return 0;
// }

// int main()
// {
//     cout << system("ls -lR") << endl;
//     return 0;
// }