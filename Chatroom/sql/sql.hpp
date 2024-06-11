#include "../head/head.hpp"
#include "../head/define.hpp"
class Sql 
{
public:
    Sql() : connection(nullptr) 
    {
        this->connection = mysql_init(nullptr);
        if (this->connection == nullptr) 
        {
            std::cerr << "mysql: init failed" << std::endl;
            return;
        }

        if (!mysql_real_connect(this->connection, "localhost", "root", "123456", "chat", 3306, nullptr, 0)) 
        {
            std::cerr << "mysql: connect failed" << mysql_error(this->connection) << std::endl;
            mysql_close(this->connection);
            return;
        }
         
        if(!creatable())
        {
            std::cerr << "mysql: create table failed" << std::endl;
            mysql_close(this->connection);
            return;
        }
        
    }

    bool insertChat(const std::string &sender_id, const std::string &receiver_id, const std::string &message_text)
    {
        std::string query = "INSERT INTO chat_history(sender_id, receiver_id, message_text) VALUES('" + sender_id + "','" + receiver_id + "','" + message_text + "')";
        if(mysql_query(this->connection, query.c_str()))
        {
            std::cerr << "mysql: insert failed" << mysql_error(this->connection) << std::endl;
            return false;
        }
        return true;   
    }
    
    
    ~Sql() 
    {
        if (this->connection != nullptr) 
        {
            mysql_close(this->connection);
        }
    }
private:
    MYSQL *connection; // 数据库连接

    bool creatable()
    {
        const char * query=R"(CREATE TABLE IF NOT EXISTS chat_history(
            id INT AUTO_INCREMENT PRIMARY KEY,
            sender_id VARCHAR(50) NOT NULL,
            receiver_id VARCHAR(50) NOT NULL,
            message_text TEXT,
            timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        ))";
        if(mysql_query(this->connection,query))
        {
            std::cerr << "mysql: table creation failed " << mysql_error(this->connection) << std::endl;
            return false;
        }
        return true;
    }
};


