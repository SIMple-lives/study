#include <iostream>
using namespace std;
#include <cstring>
#include <vector>

class MiniString
{
public:
    static size_t kbsize;
    MiniString(const char *str)
    {
        if(str)
        {
            //cout << "gzhs" << endl;
            m_data = new char[strlen(str) + 1];
            strcpy(m_data, str);
        }
        else
        {
            m_data = new char[1];
            *m_data = '\0';
        }
    }
    MiniString(const MiniString &other)
    {
        kbsize ++;
        cout << "kbsize" << endl;
        m_data=new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
        //cout << "kb" << kbsize << endl;
    }   
    MiniString &operator=(const MiniString &other)
    {
        if(this==&other)
        {
            return *this;
        }
        delete[] m_data;
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
        return *this;
    }
    ~MiniString()
    {
        if(m_data)
        {
            delete[] m_data;
        }
    }
private:
    char *m_data;
};

size_t MiniString::kbsize =0;

int main()
{
    vector<MiniString> v;
    v.reserve(1000);
    for(int i=0; i<1000; i++)
    {
        v.push_back(MiniString("hello world!"));
    }
    cout << MiniString::kbsize << endl;

    return 0;
}