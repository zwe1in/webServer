#include "Server.h"

void handleTimeout(int sig)
{
    int msg = sig;
    send(pipefd[1], (char*)&msg, 1, 0);
}

Server::Server(int maxRlease)
    : acceptor(Socket::TCP), stop(false), tickTime(false), threadPond(32), maxReleaseTime(maxRlease)
{
    root = getcwd(nullptr, 256);
    root.append("/../resources");
}

Server::~Server()
{
    if(!stop)
        stop = true;
}

void Server::start(InetAddress &address)
{
    if(socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd) == -1)
    {
        LOG_FATAL("Pipe initialize fail");
        exit(EXIT_FAILURE);
    }
    fcntl(pipefd[1], F_SETFL, fcntl(pipefd[1], F_GETFL) | O_NONBLOCK);
    poller.addFd(pipefd[0], EPOLLIN | EPOLLET);
    signal(SIGALRM, handleTimeout);

    acceptor.setReuseAddr(true);
    acceptor.setNodelay(true);
    acceptor.Bind(address);
    acceptor.Listen();
    LOG_INFO("Server initialized successfully");

    int listenFd = acceptor.getFd();
    poller.addFd(listenFd, EPOLLIN);
    // alarm(1);
    while(!stop)
    {
        int n = poller.wait();
        for(int i = 0; i < n; ++i)
        {
            epoll_event ev = poller.getEvent(i);
            int callFd = ev.data.fd;
            if(callFd == listenFd)
            {
                handleAccept();
                // threadPond.add(std::bind(&Server::handleAccept, this));
            }
            else if(ev.events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
            {
                close(callFd);
            }
            else if((pipefd[0] == callFd) && (ev.events & EPOLLIN))
            {
                handlePipe();
            }
            else if(ev.events & EPOLLIN)
            {
                // handleRead(callFd);
                threadPond.add(std::bind(&Server::handleRead, this, callFd));
            }
            else if(ev.events & EPOLLOUT)
            {
                // handleWrite(callFd);
                threadPond.add(std::bind(&Server::handleWrite, this, callFd));
            }
        }
        // tick
        if(tickTime)
        {
            timeWheel.tick();
            tickTime = false;
            alarm(1);
        }
    }
}

void Server::handleAccept()
{
    int clnFd = acceptor.Accept();
    Socket *clnSock = new Socket(clnFd);
    clnSock->setNonblocking();
    connPtr shrCont = std::make_shared<HttpConn>(&poller, clnSock, root);
    connections[clnFd] = connWeakPtr(shrCont);
    timeWheel.addTimer(maxReleaseTime, connections[clnFd]);
    poller.addFd(clnFd, EPOLLIN | EPOLLET | EPOLLONESHOT);
}

void Server::handleRead(int callFd)
{
    if(connections[callFd].lock())
    {
        timeWheel.addTimer(maxReleaseTime, connections[callFd]);
        connections[callFd].lock()->handleRead();
    }
}

void Server::handleWrite(int callFd)
{
    if(connections[callFd].lock())
    {
        connections[callFd].lock()->handleWrite();
        timeWheel.addTimer(maxReleaseTime, connections[callFd]);
    }
}

void Server::handlePipe()
{
    char buf[1024];
    int ret = read(pipefd[0], buf, sizeof(buf));
    if(ret <= 0)
    {
        LOG_FATAL("Pipe receive fail.");
        return;
    }
    else
    {
        for(int i = 0; i < ret; ++i)
        {
            if(buf[i] == SIGALRM)
            {
                tickTime = true;
            }
            else if(buf[i] == SIGTERM)
            {
                stop = true;
            }
        }
    }

}