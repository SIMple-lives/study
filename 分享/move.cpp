#include <iostream>
using namespace std;
#include <cstring>
#include <vector>

class MiniString
{
public:
    static size_t kbsize;
    static size_t movesize;
    static size_t Fkbsize;
    static size_t Fmovesize;
    MiniString(const char *str)
    {
        if(str)
        {
            // cout << "gzhs" << endl;
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
        m_data=new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
        // cout << "kb" << kbsize << endl;
    } 
    MiniString(MiniString &&other)
    {
        m_data=other.m_data;
        movesize ++;
        other.m_data=NULL;
    }
    MiniString &operator=(const MiniString &other)
    {
        Fkbsize ++;
        if(this==&other)
        {
            return *this;
        }
        delete[] m_data;
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
        return *this;
    }
    MiniString &operator=(MiniString && other)
    {
        Fmovesize++;
        if(this==&other)
        {
            return *this;
        }
        delete[] m_data;
        m_data=other.m_data;
        other.m_data=NULL;
        return *this;
    }
    ~MiniString()
    {
        delete[] m_data;
    }
private:
    char *m_data;
};

size_t MiniString::kbsize =0;
size_t MiniString::movesize=0;
size_t MiniString::Fkbsize=0;
size_t MiniString::Fmovesize=0;

int main()
{
    vector<MiniString> v;
    v.reserve(1000);
    for(int i=0; i<1000; i++)
    {   
        v.push_back(MiniString("hello world!"));
    }
    cout <<"kbsize\t"<< MiniString::kbsize << endl;
    cout <<"Fkbsize\t"<< MiniString::Fkbsize << endl;
    cout <<"movesize\t"<< MiniString::movesize << endl;
    cout <<"Fmovesize\t"<< MiniString::Fmovesize << endl;

    MiniString::kbsize =0;
    MiniString::movesize=0;
    MiniString::Fkbsize=0;
    MiniString::Fmovesize=0;
    vector<MiniString> v1;
    v1.reserve(1000);
    for(int i=0; i<1000; i++)
    {   
        MiniString other("hello world!");
        v1.push_back(move(other));
    }
    cout <<"kbsize\t"<< MiniString::kbsize << endl;
    cout <<"Fkbsize\t"<< MiniString::Fkbsize << endl;
    cout <<"movesize\t"<< MiniString::movesize << endl;
    cout <<"Fmovesize\t"<< MiniString::Fmovesize << endl;
    return 0;
}