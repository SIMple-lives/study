#include "pthread.hpp"
#include <filesystem>

struct SearchConfig
{
    std::string root_path;    //要搜索的根目录
    std::string file_type;    //要搜索的文件类型，如 ".txt"、".cpp" 等
    int max_concurrency;      // 最大并发数
    int max_depth;            // 最大搜索深度
    bool skip_hidden;         // 是否跳过隐藏文件或目录
    std::vector<std::string> skip_paths;   // 要跳过的目录或文件的路径
};

class Searcher
{
    friend void task1();
public:
    Searcher(){};
    Searcher(const SearchConfig&other)
    {
        this->s=other;
    }
    void set_config()
    {
        std::cout << "root_path is ? " << std::endl;
        std::cin>>s.root_path;
        std::cout << "file_type is? " << std::endl;
        std::cin>>s.file_type;
        std::cout << "max_concurrency is? " << std::endl;
        std::cin>>s.max_concurrency;
        std::cout << "max_depth is? " << std::endl;
        std::cin>>s.max_depth;
        std::cout << "skip_hidden is? " << std::endl;
        std::cin>>s.skip_hidden;
        std::cout << "skip_paths is? " << std::endl;
        std::string skip_path;
        while (std::cin >> skip_path && skip_path != "done") 
        {
            s.skip_paths.push_back(skip_path);
        }
    }
    void searchfiles()
    {
        std::cout << "Starting search" << std::endl;
        recursiveSearch(s.root_path, s.file_type, s.max_depth);
    }
private:
    struct SearchConfig s;
    void recursiveSearch(std::string &root_path, std::string &file_type, int max_depth)
    {
        if(max_depth == 0)//递归推出条件
        {
            return ;
        }
        for(const std::filesystem::directory_entry&entry : std::filesystem::directory_iterator(root_path))//类目录迭代器
        {
            if(std::filesystem::is_directory(entry))//判断是否是目录
            {
                std::string currentDir=entry.path().string();//获取当前路径
                if(std::find(s.skip_paths.begin(), s.skip_paths.end(), currentDir)!= s.skip_paths.end())
                //判断是否是要跳过的目录
                {
                    continue;
                }

                if(s.skip_hidden && currentDir[0]=='.')
                {
                    continue;
                }
                recursiveSearch(currentDir, file_type, max_depth-1);
            }
            //entension()是文件的扩展名
            else if(std::filesystem::is_regular_file(entry)&&entry.path().extension()==file_type)//是否为搜索的文件
            {
                std::cout << "Found " << entry.path().string() << std::endl;
            }
        }
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

void task1()
{
    Searcher s;
    // 设置搜索器的配置信息
    s.set_config();
    // 初始化线程池，设置最大并发数
    ThreadPool pool(s.s.max_concurrency);
    pool.init();
    // 提交搜索任务到线程池
    pool.submit([&s](){
        s.searchfiles();
    });
    // 等待搜索任务完成
    

    // 关闭线程池
    pool.shutdown();
}

int main() {
    task1();
    return 0;
}

// int main()
// {
//     task();
//     return 0;
// }