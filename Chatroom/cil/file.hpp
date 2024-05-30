#include "../head/head.hpp"
#include "../head/define.hpp"
#include "../cil/user_work.hpp"

class File 
{
public:
    File() = default ;
    File(int fd,std::string id)
    {
        m_id = id;
        m_fd = fd;
    }
    void Menu();
    void Run();
    void Send_file();
    void Receive_file();
    void Message_file();
    void get_info();
private:
    std::string m_id;
    int m_fd;
};