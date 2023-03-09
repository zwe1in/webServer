#ifndef SOCKET_H
#define SOCKET_H
#include "InetAddress.h"
#include "../log/Log.h"
#include "../utils/Common.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
class Socket : nonCopyable{
public:
    enum Protocal{
        TCP,
        UDP
    };
    Socket() : fd(-1){}
    Socket(Protocal type)
    {
        if(type == TCP)
            fd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
        else if(type == UDP)
            fd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
        else
        {
            LOG_FATAL("Unknown protocal type.");
            exit(EXIT_FAILURE);
        }
            
    }
    Socket(int fd_) : fd(fd_) {}
    Socket(Socket&& other)
        : fd(-1)
    {
        std::swap(fd, other.fd);
        if(fd == -1)
        {
            LOG_FATAL("Move an invalid socket.");
            exit(EXIT_FAILURE);
        }
    }
    Socket& operator= (Socket&& other)
    {
        if(this != &other)
        {
            std::swap(fd, other.fd);
            other.fd = -1;
        }
        return *this;
    }

    void Bind(InetAddress& address)
    {
        sockaddr_in addr = address.getAddr();
        int ret = bind(fd, (sockaddr*)&addr, sizeof(addr));
        if(ret == -1)
        {
            LOG_FATAL("Bind error.");
            exit(EXIT_FAILURE);
        }
    }
    void Listen()
    {
        if(listen(fd, 1024) == -1)
        {
            LOG_FATAL("Listen error.");
            exit(EXIT_FAILURE);
        }
    }
    int Accept()
    {
        InetAddress address;
        socklen_t len = sizeof(address.getAddr());
        int clnFd = accept(fd, (sockaddr*)&(address.getAddr()), &len);
        if(clnFd == -1)
        {
            LOG_FATAL("Accept error.");
            exit(EXIT_FAILURE);
        }
        LOG_INFO("New connection from %s", address.toIpPort().c_str());
        return clnFd;
    }
    void Connect(InetAddress& address)
    {
        sockaddr_in addr = address.getAddr();
        int ret = connect(fd, (sockaddr*)&addr, sizeof(addr));
        if(ret == -1)
        {
            LOG_FATAL("Connect error.");
            exit(EXIT_FAILURE);
        }    
    }
    void shutdownWrite()
    {
        shutdown(fd, SHUT_WR);
    }
    void setNonblocking()
    {
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
    }
    void setReuseAddr(bool on)
    {
        int val = on?1:0;
        int ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        if(ret < 0)
            LOG_FATAL("Set ReuseAddr error.");
    }
    void setNodelay(bool on)
    {
        int val = on?1:0;
        int ret = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val));
        if(ret < 0)
            LOG_FATAL("Set Tcp-nodelay error.");
    }
    int getFd() const { return fd; }
    int read(void* buf, int len) 
    {
        return ::read(fd, buf, len);
    }
    int write(void* buf, int len)
    {
        return ::write(fd, buf, len);
    }
    ~Socket()
    {
        if(fd != -1)
        {
            close(fd);
            fd = -1;
        }
    }
private:
    int fd;
};

#endif