#include <iostream>
#include <mutex>
#include <queue>
#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <algorithm>

class calculate_time
{
public:
    calculate_time()
    {
        start_time = std::chrono::steady_clock::now();
    }
    ~calculate_time()
    {
        end_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time); 
        std::cout << "Calculating time : " << duration.count() << " microseconds" << std::endl;
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    std::chrono::time_point<std::chrono::steady_clock> end_time;
};

// Thread safe implementation of a Queue using a std::queue
template <typename T>
class SafeQueue
{
private:
    std::queue<T> m_queue; //利用模板函数构造队列​
    std::mutex m_mutex; // 访问互斥信号量

public:
    SafeQueue() {}
    SafeQueue(SafeQueue &&other) {}
    ~SafeQueue() {}
    bool empty() // 返回队列是否为空
    {
        std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变
        return m_queue.empty();
    }
    int size()
    {
        std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变
        return m_queue.size();
    }

    // 队列添加元素
    void enqueue(T &t)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.emplace(t);
    }

    // 队列取出元素
    bool dequeue(T &t)
    {
        std::unique_lock<std::mutex> lock(m_mutex); // 队列加锁​
        if (m_queue.empty())
            return false;
        t = std::move(m_queue.front()); // 取出队首元素，返回队首元素值，并进行右值引用
        m_queue.pop(); // 弹出入队的第一个元素​
        return true;
    }
};

class 
ThreadPool
{
private:
    class ThreadWorker // 内置线程工作类
    {
    private:
        int m_id; // 工作id​
        ThreadPool *m_pool; // 所属线程池
    public:
        // 构造函数
        ThreadWorker(ThreadPool *pool, const int id) : m_id(id),m_pool(pool) {}
        // 重载()操作
        void operator()()
        {
            std::function<void()> func; // 定义基础函数类func
            bool dequeued; // 是否正在取出队列中元素
            while (!m_pool->m_shutdown)
            {
                {
                    // 为线程环境加锁，互访问工作线程的休眠和唤醒
                    std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);
                    // 如果任务队列为空，阻塞当前线程
                    if (m_pool->m_queue.empty())
                    {
                        m_pool->m_conditional_lock.wait(lock); // 等待条件变量通知，开启线程
                    }
                    // 取出任务队列中的元素
                    dequeued = m_pool->m_queue.dequeue(func);
                }
                // 如果成功取出，执行工作函数
                if (dequeued)
                    func();
            }
        }
    };

    bool m_shutdown; // 线程池是否关闭
    SafeQueue<std::function<void()>> m_queue; // 执行函数安全队列，即任务队列
    std::vector<std::thread> m_threads; // 工作线程队列
    std::mutex m_conditional_mutex; // 线程休眠锁互斥变量
    std::condition_variable m_conditional_lock; // 线程环境锁，可以让线程处于休眠或者唤醒状态
    std::atomic<bool> m_needAdjust; // 是否需要调整线程数量
    std::atomic<int> m_maxThreads; // 最大线程数量
    std::atomic<int> m_minThreads; // 最小线程数量
public:
    // 线程池构造函数
    ThreadPool(const int n_threads = 4)
        : m_shutdown(false),m_threads(std::vector<std::thread>(n_threads)){}//之前的警告是由于成员变量的初始化顺序与他们在类中
        //声明的顺序不匹配而引起的.c++中，成员变量的初始化顺序是按照他们在类中声明的顺序来执行的.而不是初始化列表的顺序

    //删除拷贝构造函数，且不能通过赋值来初始化另外一个对象
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;
    // 初始化线程池
    void init()
    {
        for (size_t i = 0; i < m_threads.size(); ++i)
        {
            m_threads.at(i) = std::thread(ThreadWorker(this, i)); // 分配工作线程
        }
    }

    //关闭线程池
    void shutdown()
    {
        m_shutdown = true;
        m_conditional_lock.notify_all(); // 通知，唤醒所有工作线程

        for (size_t i = 0; i < m_threads.size(); ++i)
        {
            if (m_threads.at(i).joinable()) // 判断线程是否在等待
            {
                m_threads.at(i).join(); // 将线程加入到等待队列
            }
        }
    }

    // 向线程池中添加任务
    template <typename T, typename... Args>
    auto submit(T &&t, Args &&...args) -> std::future<decltype(t(args...))>
    {
        // Create a function with bounded parameter ready to execute
        std::function<decltype(t(args...))()> func = std::bind(std::forward<T>(t), std::forward<Args>(args)...); // 连接函数和参数定义，特殊函数类型，避免左右值错误

        // Encapsulate it into a shared pointer in order to be able to copy construct
        auto task_ptr = std::make_shared<std::packaged_task<decltype(t(args...))()>>(func);

        // Warp packaged task into void function
        std::function<void()> queue_func = [task_ptr]()
        {
            (*task_ptr)();
        };

        // 队列通用安全封包函数，并压入安全队列
        m_queue.enqueue(queue_func);

        // 唤醒一个等待中的线程
        m_conditional_lock.notify_one();
        //将线程池状态设置为需要调整
        m_needAdjust.store(true);

        // 返回先前注册的任务指针
        return task_ptr->get_future();
    }
    void adjust_threads()
    {
        if(m_shutdown)
        {
            return ;
        }
        int current_threads = m_threads.size();
        int current_tasks = m_queue.size();
        if(current_tasks>current_threads && current_tasks < m_maxThreads.load())
        {
            int new_threads = std::min(current_tasks,m_maxThreads.load());
            int add_threads = new_threads-current_threads;
            for(int i=0;i<add_threads;i++)
            {
                m_threads.emplace_back(ThreadWorker(this, current_threads+i));
            }
        }
        else if(current_threads>m_minThreads.load() && current_tasks<current_threads/2)
        {
            int new_threads = std::max(current_tasks,m_minThreads.load());  
            int del_threads = current_threads-new_threads;
            for(int i=0;i<del_threads;i++)
            {
                int last_index = m_threads.size() - 1;
                if (m_threads[last_index].joinable())
                {
                    m_threads[last_index].join();
                }
                m_threads.pop_back(); 
            }
        }
    }
};
