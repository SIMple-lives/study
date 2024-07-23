#include "../head/define.hpp"
#include "../head/head.hpp"
#include "../sen_rec/sen_rec.hpp"

class Prich
{
public:
    Prich() = default;
    Prich(int fd, std::string friend_id, std::string id) : m_fd(fd), m_friend(friend_id), m_id(id) {}
    ~Prich() = default;
    
    // 获取fd
    int getFd() const { return m_fd; }
    // 获取id
    std::string getId() const { return m_id; }

    // 设置fd
    void setFd(int fd) { m_fd = fd; }
    // 设置id
    void setId(std::string id) { m_id = id; }

    void run();
    void run_Group();

    int getTerminalWidth()
    {
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        return size.ws_col;
    }

    void printRightAligned(const std::string& str, int terminalWidth)
    {
        int padding = terminalWidth - str.length();
        if (padding > 0)
        {
            std::cout << std::string(padding, ' ') << "" << str << std::endl;
        }
        else
        {
            std::cout << str << std::endl;
        }
    }

    std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time_t);
        std::ostringstream oss;
        oss << std::put_time(&now_tm, "%Y-%m-%d+%H:%M:%S");
        return oss.str();
    }

private:
    std::vector<std::string> GetOfflineMsg();
    int m_fd;
    std::string m_friend;
    std::string m_id;
    std::thread messageReceiverThread;
    bool exitRequested = false; // Flag to signal exit from chat interface

    void receiveMessagesFromServer()
    {
        while (!exitRequested)
        {
            try
            {
                std::string message;
                Rec r;
                int count = r.recv_cil(m_fd, message);
                if (count <= 0)
                {
                    // 错误处理
                }
                else
                {
                    nlohmann::json parse = nlohmann::json::parse(message);
                    int terminalWidth = getTerminalWidth();
                    printRightAligned(parse["send"], terminalWidth);
                    if (parse["send"] == "exit")
                    {
                        exitRequested = true;
                        return;
                    }
                    if (exitRequested)
                    {
                        return;
                    }
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error receiving message: " << e.what() << std::endl;
            }
        }
    }

    void startMessageReceiver()
    {
        messageReceiverThread = std::thread(&Prich::receiveMessagesFromServer, this);
    }
};

inline std::vector<std::string> Prich::GetOfflineMsg()
{
    try
    {
        Rec r;
        std::string off_msg;
        int status = r.recv_ok(m_fd);
        if (status == SUCCESS)
        {
            r.recv_cil(m_fd, off_msg);
            nlohmann::json j = nlohmann::json::parse(off_msg);
            std::vector<std::string> v = j["off_msg"];
            return v;
        }
        else if (status == NOOFFLINEMSG)
        {
            //std::cout << "无历史消息 " << std::endl;
            return std::vector<std::string>();
        }
        else
        {
            std::cerr << "recv error" << std::endl;
            return std::vector<std::string>();
        }
    }
    catch (const nlohmann::json::parse_error& e)
    {
        std::cerr << "Failed to parse offline messages JSON: " << e.what() << std::endl;
        return std::vector<std::string>();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error in GetOfflineMsg: " << e.what() << std::endl;
        return std::vector<std::string>();
    }
}




// int epoll_fd = epoll_create1(0);
        // struct epoll_event event;
        // struct epoll_event events[20];

        // event.events = EPOLLIN;
        // event.data.fd = m_fd;
        // epoll_ctl(epoll_fd, EPOLL_CTL_ADD, m_fd, &event);
// int n = epoll_wait(epoll_fd, events, 20, -1);
            // for (int i = 0; i < n; i++)
            // {
            //     if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
            //     {
            //         // 错误处理
            //     }
            //     else
            //     {
                    
                // }
            // }

            // for (ssize_t i = 0; i < count; ++i) 
                        // {
                        //     if (isprint(static_cast<unsigned char>(buffer[i]))) 
                        //     {
                        //         std::cout << buffer[i]; // 只打印可打印字符
                        //     } 
                        //     else 
                        //     {
                        //         std::cout << '.'; // 打印点来表示不可打印字符
                        //     }
                        // }
                        // std::cout << std::endl;
                        // 处理接收到的数据
                        //message.assign(buffer, count);
                        //std::cout << message << std::endl;
                        // message.insert(0, buffer + 4, count - 4); // 从第五个字符开始，拷贝剩余的字符
                        // std::cout << "Message from buffer: " << message << std::endl;
                        // std::cout << message << std::endl;
                        // nlohmann::json send = nlohmann::json::parse(message);
                        // int terminalWidth = getTerminalWidth();
                        // printRightAligned(send["send"],  terminalWidth);
                        //std::cout << a<<std::endl;