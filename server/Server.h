#ifndef SERVER_H
#define SERVER_H
#include "../utils/Common.h"
#include "../tcp/Socket.h"
#include "../tcp/InetAddress.h"
#include "../http/HttpConn.h"
#include "../thread/ThreadPool.h"
#include "../utils/Buffer.h"
#include "../time/TimeWheel.h"
#include "Epoller.h"
#include <sys/uio.h>
#include <unordered_map>
#include <functional>
#include <memory>
#include <errno.h>
#include <signal.h>

static int pipefd[2];
void handleTimeout(int sig);

class Server : nonCopyable{
public:
    Server(int maxRlease=200);
    ~Server();
    void start(InetAddress &address);

private:
    void handleAccept();
    void handleRead(int callFd);
    void handleWrite(int callFd);
    void handlePipe();
private:
    int maxReleaseTime;     // 每个链接无活动下，最大生存时间
    TimeWheel timeWheel;    // 时间轮
    Socket acceptor;    // 负责监听并连接的fd
    std::unordered_map<int, connWeakPtr> connections;   // 目前所有客户连接
    Epoller poller;
    std::string root;   // 根目录
    bool stop;
    bool tickTime;  // 定时是否到时，该tick
    BalancePool threadPond; // 线程池
    
};

#endif