# eventfd

[详解](https://juejin.cn/post/6989608237226000391)

是一个Linux系统调用，也是一种进程间通信(IPC)机制，主要通过**使用文件描述符**生成和使用事件通知.

提供了一种在不同进程之间或同一进程内的线程之间的同步事件的方法.

# 异常处理

异常是程序在执行期间产生的问题。c++异常是指在程序运行时发生的特殊情况.

异常提供了一种转移程序控制权的方式。C++ 异常处理涉及到三个关键字：**try、catch、throw**

关键字：**try、catch、throw**。

- **throw:** 当问题出现时，程序会抛出一个异常。这是通过使用 **throw** 关键字来完成的。

* **catch:** 在您想要处理问题的地方，通过异常处理程序捕获异常。**catch** 关键字用于捕获异常

* **try:** **try** 块中的代码标识将被激活的特定异常。它后面通常跟着一个或多个 catch 块

```c++
try
{
   // 保护代码
}catch( ExceptionName e1 )
{
   // catch 块
}catch( ExceptionName e2 )
{
   // catch 块
}catch( ExceptionName eN )
{
   // catch 块
}
```

# nlohmann::json

[链接](https://readdevdocs.com/blog/tech/C++%20nlohmann%20json%E5%BA%93%E4%BD%BF%E7%94%A8%E6%95%99%E7%A8%8B.html#google_vignette)

# SIGPIPE

`SIGPIPE` 是一种信号，当一个进程尝试向一个已经关闭的或不可写的管道或套接字写数据时，会触发这个信号。默认情况下，接收到 `SIGPIPE` 信号的进程会终止。这在网络编程中会导致一些问题，因为如果客户端断开连接，服务器进程在写入数据时会因为这个信号而意外退出。

在网络编程中，特别是使用套接字进行通信时，忽略 `SIGPIPE` 信号是一个常见的做法。这样可以防止进程因为 `SIGPIPE` 信号而意外终止。相反，程序可以通过检测 `send` 或 `write` 操作的返回值来处理错误，从而使程序更加健壮。