#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <ncurses.h>

int main() {
    // 初始化 ncurses
    initscr();
    cbreak(); // 禁用行缓冲
    noecho(); // 禁用回显 
    keypad(stdscr, TRUE); // 启用功能键捕获

    // 创建 epoll 实例
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        return 1;
    } 

    // 添加标准输入文件描述符到 epoll 实例中，监听读取事件
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        perror("epoll_ctl");
        return 1;
    }

    constexpr int MAX_EVENTS = 10;
    struct epoll_event events[MAX_EVENTS];

    while (true) {
        // 等待事件发生
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1) {
            perror("epoll_wait");
            return 1;
        }

        // 处理事件
        for (int i = 0; i < num_events; ++i) {
            if (events[i].data.fd == STDIN_FILENO) {
                // 如果是标准输入上的事件，读取输入并打印
                char buffer[1024];
                int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
                if (bytes_read == -1) {
                    perror("read");
                    return 1;
                }
                std::cout << "Read from stdin: " << std::string(buffer, bytes_read)<<std::endl;

                // 检查是否按下 ESC 键
                if (buffer[0] == 27) { // 27 是 ESC 键的 ASCII 码
                    endwin(); // 结束 ncurses
                    close(epoll_fd); // 关闭 epoll 实例
                    return 0; // 退出程序
                }
            }
        }
    }

    // 关闭 epoll 实例
    close(epoll_fd);

    return 0;
}
