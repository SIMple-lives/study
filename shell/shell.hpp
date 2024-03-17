#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <unistd.h>
#include <csignal>
#include <algorithm>
#include <termios.h>
#include <cstdlib>
#include <wait.h>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>

class Shell
{
public:
    void print();
    void setlinebuf();
    string retlinebuf();
    void setsignal();
    bool isempty();
    void addHistory(const string& line);
    void setEOF();
    void printHistory();
    void searchAndReplay(const string &keyword);
    void mycd(vector<string> &s);
    void executeCommand(vector<string> &command);
    void parse(string &s);
private:
    string linebuf;
    vector<string> history;
};