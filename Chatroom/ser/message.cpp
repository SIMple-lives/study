#include "../ser/message.hpp"
#include "../redis/redis.hpp"

void Msg::send_off(std::vector<std::string> &offline)
{
    if(offline.size() == 0)
    {
        Sen s;
        s.send_ok(this->m_source,NOOFFLINEMSG);
        //s.send_cil(this->m_dest,offline);
        std::cout << "没有离线消息" << std::endl;
    }
    else 
    {
        nlohmann::json j = {{"off_msg",offline}};
        Sen s;
        s.send_ok(this->m_source,SUCCESS);
        s.send_cil(this->m_source,j.dump());
        std::cout <<"离线消息发送成功 " << std::endl;
    }    
}

void Msg::run(std::string &message)
{
    //int fd = m_dest;
    redisAsyncContext redis;
    //std::cout << "dsadjlasjd" << std::endl;
    std::string friend_source = redis.HashGet("id_name", id_s);
    std::string friend_dest = redis.HashGet("id_name", id_d);
    std::cout << friend_source << std::endl;
    std::cout << friend_dest << std::endl;
    
        int status_b ;
        if(redis.Zstatus(id_d,id_s,status_b))
        {
            if(status_b ==BLOCK)
            {
                std::cout << "对方已屏蔽你" << std::endl;
                Sen s;
                nlohmann::json j = {
                    {"send","!"+message}
                };
                s.send_cil(this->m_source,j.dump());
                return;
            }
        }
        //std::vector<std::string> offline;
        //offline = redis.Lrange(friend_source+"offline", 0, -1);
        //this->send_off(offline);
        //while(1)
        //{
        std::cout << "接收到 " <<friend_source << " 发送给 " << friend_dest << " 的消息 " << message << std::endl;
        std::string send = friend_source +message;
        std::cout << send << std::endl;
        nlohmann::json j = {
            {"send",send}};
        redis.Lpush(friend_dest+friend_source + "Message", j.dump());
        //std::cout << j.dump() << "    kashdkjaws" << std::endl;
        // std::cout << id_d << "               kashdkashdkj" << std::endl;
        std::string status;
        if (redis.Ifexit("online", id_d)) 
        {
            if (redis.Zstatus("chat", id_d,status)) 
            {
                std::cout << "Status found: " << status << std::endl;
                if (status == id_s) 
                {
                    Sen s;
                    std::cout << "直接发送" << std::endl;
                    s.send_cil(this->m_dest, j.dump());
                } 
                else 
                {
                    std::cout << "对方没有和你在聊天 " << std::endl;
                    redis.Lpush(friend_dest+friend_source + "offline", j.dump());
                    Sen s;
                    std::string message = "好友" + id_s + "给你发送了一条消息 !" ;
                    nlohmann::json ja = {
                        {"send",message}
                    };
                    s.send_cil(this->m_dest, ja.dump());
                    
                   // redis.Lpush(friend_dest + "offline", j.dump());
                    int status ;
                    if(redis.Zstatus(id_d+"chat",id_s,status))
                    {
                        status += 1;
                        redis.Zadd(id_d+"chat",status,id_s);
                    }
                    else
                    {
                        redis.Zadd(id_d + "chat",1,id_s);
                    }
                }
            }
            else 
            {
                std::cout << "对方在初始界面 " << std::endl;
                std::cout << "Adding to offline messages" << std::endl;
                redis.Lpush(friend_dest+friend_source + "offline", j.dump());
                Sen s;
                std::string message = "好友" + id_s + "给你发送了一条消息 !" ;
                nlohmann::json ja = {
                    {"send",message}
                };
                //s.send_cil(this->m_dest, ja.dump());
                //本来是要直接发送过去，但是没有线程接收
                redis.Lpush(friend_dest+friend_source + "offline", j.dump());
                // redis.Lpush(friend_dest + "online",j.dump());
                int status ;
                if(redis.Zstatus(id_d+"chat",id_s,status))
                {
                    status += 1;
                    redis.Zadd(id_d+"chat",status,id_s);
                }
                else
                {
                    redis.Zadd(id_d+ "chat",1,id_s);
                }
            }
        } 
        else 
        {
            std::cout << "Adding to offline messages" << std::endl;
            redis.Lpush(friend_dest+friend_source + "offline", j.dump());
            if(redis.Zstatus(id_d+"chat",id_s,status))
            {
                status += 1;
                redis.Zadd(id_d+"chat",status,id_s);
            }
            else
            {
                redis.Zadd(id_d+ "chat",1,id_s);
            }
        }
        //  while (true) 
        //  {
        //     int len = r.recv_cil(this->m_source, message);
        //     if (len > 0) 
        //     {
        //         std::cout << "接收发送消息" << std::endl;
        //         std::cout << friend_source << " 发送给 " << friend_dest << " 的消息 " << message << std::endl;
        //         // Handle sending message to destination here
        //     } 
        //     else if (len == -1) 
        //     {
        //         if (errno == EAGAIN || errno == EWOULDBLOCK) 
        //         {
        //             // No data available now, continue the loop to retry
        //             continue;
        //         } 
        //         else 
        //         {
        //             std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
        //             break;
        //         }
        //     } 
        //     else 
        //     {
        //         std::cerr << "Client disconnected or error occurred: " << strerror(errno) << std::endl;
        //         break;
        //     }
        // }

        // std::cerr << "File descriptor is no longer valid: " << this->m_source << std::endl;
        // close(this->m_source);
    
}

void Msg::run_Group(std::string &message,std::string &id)
{
    redisAsyncContext redis;
    //std::cout << "dsadjlasjd" << std::endl;
    
    std::string friend_source = redis.HashGet("id_name", id_s);
    std::string friend_dest = redis.HashGet("id_name", id);
    std::cout << friend_source << std::endl;
    std::cout << friend_dest << std::endl;
    int status_b ;
    if(redis.Zstatus(id_d,id_s,status_b))
    {
        if(status_b ==NOTSPEAK)
        {
            std::cout << "你已被禁言" << std::endl;
            Sen s;
            nlohmann::json j = {
                {"send","!"+message}
            };
            s.send_cil(this->m_source,j.dump());
            return;
        }
    }
    std::cout << "接收到 " <<friend_source << " 发送给 " << friend_dest << " 的消息 " << message << std::endl;
    std::string send = friend_source +message;
    std::cout << send << std::endl;
    nlohmann::json j = {
        {"send",send}};
       
    std::string status;
    if (redis.Ifexit("online", id)) 
    {
        std::cout << "dsaklsdj" << std::endl;
        if (redis.Zstatus("chat", id,status)) 
        {
            std::cout << "1" << std::endl;
            std::cout << "Status found: " << status << std::endl;
            if (status == id_d) 
            {
                Sen s;
                std::cout << "直接发送" << std::endl;
                s.send_cil(this->m_dest, j.dump());
            } 
            else  
            {
                std::cout << "对方没有在该群聊 " << std::endl;
                redis.Lpush(friend_dest + "offline", j.dump());
                Sen s;
                std::string message = "群聊" + id_d + "给你发送了一条消息 !" ;
                nlohmann::json ja = {
                    {"send",message}
                };
                s.send_cil(this->m_dest, ja.dump());
                    
                   // redis.Lpush(friend_dest + "offline", j.dump());
                int status ;
                if(redis.Zstatus(id+"Gchat",id_d,status))
                {
                    status += 1;
                    redis.Zadd(id+"Gchat",status,id_d);
                }
                else
                {
                    redis.Zadd(id + "Gchat",1,id_d);
                }
            }
        }
        else 
        {
            std::cout << "对方在初始界面 " << std::endl;
            std::cout << "Adding to offline messages" << std::endl;
            redis.Lpush(friend_dest + "offline", j.dump());
            Sen s;
            std::string message = "好友" + id_s + "给你发送了一条消息 !" ;
            nlohmann::json ja = {
                {"send",message}
            };
                //s.send_cil(this->m_dest, ja.dump());
                //本来是要直接发送过去，但是没有线程接收
            redis.Lpush(friend_dest + "offline", j.dump());
                // redis.Lpush(friend_dest + "online",j.dump());
            int status ;
            if(redis.Zstatus(id+"Gchat",id_d,status))
            {
                status += 1;
                redis.Zadd(id+"Gchat",status,id_d);
            }
            else
            {
                redis.Zadd(id+ "Gchat",1,id_d);
            }
        }
    } 
    else 
    {
        std::cout << "Adding to offline messages" << std::endl;
        redis.Lpush(friend_dest + "offline", j.dump());
        if(redis.Zstatus(id+"Gchat",id_d,status))
        {
            status += 1;
            redis.Zadd(id+"Gchat",status,id_d);
        }
        else
        {
            redis.Zadd(id+ "Gchat",1,id_d);
        }
    }
}
