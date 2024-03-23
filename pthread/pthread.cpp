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

class ThreadPool
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

        // 返回先前注册的任务指针
        return task_ptr->get_future();
    }
};

boost::multiprecision::cpp_int calculate(int n)
{
    boost::multiprecision::cpp_int num=1;
    for(int i = 1;i<=n;i++)
    {
        num*=i;
    }
    std::cout << "thread ID " << std::this_thread::get_id() << " ";
    return num;
}

void task()
{
    int count ;
    std::cout << "请输入打算计算的数量 :" << std::endl;
    std::cin>>count;
    std::vector<int> calNum;
    calNum.resize(count);
    for(int i=0;i<count;i++)
    {
        std::cout << "请输入第" << i+1 << "个数字:" << std::endl;
        std::cin>>calNum[i];
    }
    ThreadPool pool(4);
    pool.init();
    for(int n:calNum)
    {
        auto future1 = pool.submit(calculate,n);
        boost::multiprecision::cpp_int result = future1.get();
        std::cout << "result( "<< n << " ) = " << result << std::endl;
    }
    pool.shutdown();
}

int main()
{
    task();
    return 0;
}