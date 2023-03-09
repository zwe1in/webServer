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
    int maxReleaseTime;
    TimeWheel timeWheel;
    Socket acceptor;
    std::unordered_map<int, connWeakPtr> connections;
    Epoller poller;
    std::string root;
    bool stop;
    bool tickTime;
    BalancePool threadPond;
    
};

#endif