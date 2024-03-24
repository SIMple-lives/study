#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>

class calculate_time
{
public:
    calculate_time()
    {
        start = std::chrono::steady_clock::now();
    }
    ~calculate_time()
    {
        end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "持续的时间为: " << duration.count() << " microseconds" << std::endl;
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
};

class TaskQueue 
{
public:
    TaskQueue() {}
    TaskQueue(TaskQueue &&other) = default ;
    ~TaskQueue() {}

    bool isEmpty() 
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    void enqueue(std::packaged_task<boost::multiprecision::cpp_int(int)> &&t) 
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(std::move(t));
    }

    int size() 
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    bool dequeue(std::packaged_task<boost::multiprecision::cpp_int(int)> &t) 
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_queue.empty()) 
        {
            return false;
        }
        t = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

private:
    std::queue<std::packaged_task<boost::multiprecision::cpp_int(int)>> m_queue;
    std::mutex m_mutex;
};

class ThreadPool 
{
public:
    ThreadPool(const int n_threads = 5)
        : m_threads(n_threads), m_shutdown(false) {}

    //删除对线程池的拷贝与赋值操作
    ThreadPool(const ThreadPool &other) = delete;
    ThreadPool& operator=(const ThreadPool & other) = delete;
    //删除对线程池的移动操作
    ThreadPool(ThreadPool && other) = delete;
    ThreadPool& operator= (ThreadPool && other) = delete;

    ~ThreadPool() {}

    void init() 
    {
        for (size_t i = 0; i < m_threads.size(); i++) 
        {
            m_threads[i] = std::thread(ThreadWork(this, i));
        }
    }

    void shutdown() 
    {
        m_shutdown = true;
        m_condition.notify_all();
        for (size_t i = 0; i < m_threads.size(); i++) 
        {
            if (m_threads[i].joinable()) 
            {
                m_threads[i].join();
            }
        }   
    }

    std::future<boost::multiprecision::cpp_int> submit(std::function<boost::multiprecision::cpp_int(int)> f) 
    {
        std::packaged_task<boost::multiprecision::cpp_int(int)> task(std::move(f));
        std::future<boost::multiprecision::cpp_int> res = task.get_future();
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_task.enqueue(std::move(task));
        }
        m_condition.notify_one();
        return res;
    }

    void AdjustThreads()
    {
        if(m_shutdown) return ;
        int currentTask = m_task.size();
        int currentThread = m_threads.size();
        if(currentTask > currentThread && currentTask < m_maxthreads.load())
        {
            int newThread = std::min(currentTask, m_maxthreads.load());
            int addThread = newThread - currentThread;
            for(int i=0;i<addThread;i++)
            {
                m_threads.emplace_back(ThreadWork(this,currentThread+i));
            }
        }
        else if(currentThread > m_minthreads.load() && currentThread/2>currentTask)
        {
            int newthread=std::max(currentTask, m_minthreads.load());
            int deleteThread = currentThread - newthread;
            for(int i=0;i< deleteThread;i++)
            {
                int lastindex = m_threads.size()-1;
                if(m_threads.at(lastindex).joinable())
                {
                    m_threads.at(lastindex).join();
                }
                m_threads.pop_back();
            }
        }
    }
private:
    class ThreadWork 
    {
    public:
        ThreadWork(ThreadPool *pool, int id) : m_pool(pool), m_id(id) {}
        void operator()() {
            std::packaged_task<boost::multiprecision::cpp_int(int)> func;
            bool dequeued;
            while (!m_pool->m_shutdown) 
            {
                {
                    std::unique_lock<std::mutex> lock(m_pool->m_mutex);
                    if (m_pool->m_task.isEmpty()) 
                    {
                        m_pool->m_condition.wait(lock);
                    }  
                    dequeued = m_pool->m_task.dequeue(func);
                }
                if (dequeued) 
                {
                    func(m_id);
                }
            }
        }
    private:
        ThreadPool *m_pool;
        int m_id;
    };

    std::vector<std::thread> m_threads;
    bool m_shutdown;
    std::condition_variable m_condition;
    std::mutex m_mutex;
    TaskQueue m_task;
    std::atomic<bool> m_needAdjust;
    std::atomic<int> m_maxthreads;
    std::atomic<int> m_minthreads;
};

boost::multiprecision::cpp_int factorial(int n) 
{
    boost::multiprecision::cpp_int result = 1;
    for (int i = 1; i <= n; ++i) 
    {
        result *= i;
    }
    //std::cout << "Thread Id " << std::this_thread::get_id() << "\t(" <<n << ")" << result << std::endl;
    std::cout << "Thread Id " << std::this_thread::get_id() << "\t";
    return result;
}

void task()
{
    ThreadPool pool(4);
    pool.init();
    std::vector<int> Num;
    int n_Num;
    std::cout << "请输入需要计算的数量: " << std::endl;
    std::cin >> n_Num;
    Num.resize(n_Num);
    for(int i=0;i<n_Num;i++)
    {
        std::cout << "请输入第" << i+1 << "个数字: " << std::endl;
        std::cin >> Num[i];
    }
    calculate_time time;
    for(size_t i=0;i<Num.size();i++)
    {
        std::function<boost::multiprecision::cpp_int(int)> func=std::bind(factorial,Num[i]);
        std::future<boost::multiprecision::cpp_int> res=pool.submit(func);
        std::cout << "result(" << Num[i] << ") = " << res.get() << std::endl;
    }
    pool.shutdown();
}

boost::multiprecision::cpp_int factorial1(int n) 
{
    boost::multiprecision::cpp_int result = 1;
    for (int i = 1; i <= n; ++i) 
    {
        result *= i;
    }
    return result;
}

void task1()
{
    int n_Num;
    std::cout << "请输入需要计算的数量: " << std::endl;
    std::cin >> n_Num;
    std::vector<int> Num(n_Num);
    for(int i=0;i<n_Num;i++)
    {
        std::cout << "请输入第" << i+1 << "个数字: " << std::endl;
        std::cin >> Num[i];
    }
    calculate_time time;
    for(size_t i=0;i<Num.size();i++)
    {
        std::cout << "result(" << Num[i] << ") = " << factorial1(Num[i]) << std::endl;
    }
}

int main() 
{
    task();
    task1();
    return 0;
}