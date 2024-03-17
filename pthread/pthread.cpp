#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <condition_variable>
#include <functional>
#include <atomic>

template <class T>
class SafeQueue
{
public:
    SafeQueue(){};
    SafeQueue(SafeQueue && other)=default;//移动构造函数，默认实现.
    ~SafeQueue(){};
    bool empty()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }
    int count()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.size();
    }
    void enqueue(T &value)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.emplace_back(value);
    }
    bool dequeue(T &ret)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if(m_queue.empty())
        return false;
        ret=std::move(m_queue.front());
        m_queue.pop_front();
        return true;
    }
private:
    std::mutex m_mutex;
    std::queue<T> m_queue;
};

class ThreadPool
{
private:
    class ThreadWork
    {
        private:
            int m_id;
            ThreadPool * m_pool;
        public:
            ThreadWork(ThreadPool * pool,const int id):m_pool(pool),m_id(id){}
            void operator()()
            {
                std::function<void()> func;
                bool dequeued;
                while(!m_pool->m_shutdown)//线程池关闭，线程退出
                {
                    {
                        std::unique_lock<std::mutex> lock(m_pool->m_mutex);
                        //判断任务队列是否为空
                        if(m_pool->m_queue.empty())
                        {
                            m_pool->m_conditional_lock.wait(lock);
                        }
                        //从队列中取出一个任务
                        dequeued=m_pool->m_queue.dequeue(func);
                    }
                    if(dequeued)
                    {
                        func();
                    }
                }
            }
    };
    bool m_shutdown;
    SafeQueue<std::function<void()>> m_queue;
    std::vector<std::thread> m_threads;
    std::mutex m_mutex;
    std::condition_variable m_conditional_lock;
    std::atomic<bool> m_needAdjustment;
    std::atomic<int> m_maxThreads;
    std::atomic<int> m_minThreads;
public:
    ThreadPool(const int n_threads =4): m_threads(std::vector<std::thread>(n_threads)),m_shutdown(false){}
    
    //删除拷贝构造函数，且不能通过赋值来初始化另外一个对象
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool &operator=(const ThreadPool& other) = delete;

    ThreadPool (ThreadPool&& other) = delete;
    ThreadPool &operator=(ThreadPool&& other) = delete;

    void init()
    {
        for(int i=0;i<m_threads.size();i++)
        {
            m_threads.at(i)=std::thread(ThreadWork(this,i));
        }
    }
    void shutdown()
    {
        m_shutdown=true;
        m_conditional_lock.notify_all();
        for(int i=0;i<m_threads.size();i++)
        {
            if(m_threads.at(i).joinable())
            {
                m_threads.at(i).join();
            }
        }
    }
    
    template<typename T,typename ... Args>
    auto submit(T &&t,Args&&... args) -> std::future<decltype(t(args...))>
    {
        std::function<decltype(t(args...))> func = std::bind(std::forward<T>(t),std::forward<Args>(args)...);
        auto task_ptr = std::make_unique<std::packaged_task<decltype(t(args...)) ()>> (func);
        std::function<void()> queue_func = [](){
            (*task_ptr)();
        };
        m_queue.enqueue(queue_func);
        m_conditional_lock.notify_one();
        m_needAdjustments.store(true);
        return task_ptr->get_future();
    }

    void adjustThreadPool() {
        if(m_shutdown) return;
        int currentTaskCount = m_queue.count();
        int currentThreadCount = m_threads.size();
        if(currentTaskCount > currentThreadCount) {
            int newThreadCount = std::min(currentTaskCount, m_maxThreads.load());
            int AddThreadCount = newThreadCount - currentThreadCount;
            for(int i=0; i<AddThreadCount; i++) {
                m_threads.emplace_back(ThreadWork(this,i));
            }
        }
    }
};  
// template <typename T ,typename ... Args>
// //函数返回值为一个std::future对象      尾部返回类型推导，将t的返回值作为std::future的类型.  future中存储的类型为f(args)
// auto submit (T &&t, Args &&...args) -> std::future<decltype(t(args...))>
// {
//     std::function<decltype(t(args...))> func=std::bind(std::forward<T>(t),std::forward<Args>(args)...);
//     auto task_ptr = std::make_shared<std::packaged_task<decltype(t(args...)) ()>> (func);
//     //将package_task封装成一个不接受参数，也无返回值的函数，方便放入队列中
//     std::function<void()> queue_func = [task_ptr]() 
//     {
//         (*task_ptr)();
//     };
//     m_queue.enqueue(queue_func);
//     m_conditional_lock.notify_one();
//     return task_ptr->get_future();
// }

int main()
{

    return 0;
}