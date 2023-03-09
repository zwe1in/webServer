#include "HttpConn.h"

HttpConn::HttpConn(Epoller *poller_, Socket *sock_, const std::string& root)
    : poller(poller_), sock(sock_), rootPath(root), iov_count(2)
{}

HttpConn::~HttpConn()
{
    delete sock;
    printf("Release sock\n");
}

void HttpConn::handleRead()
{
    if(!readNoBlock()) return ;
    request.reset();
    if(request.parse(readBuffer))   // 请求解析成功
        response.init(rootPath, 200, std::move(request));
    else
        response.init(rootPath, 400, std::move(request));
    response.makeResponse(writeBuffer);
    
    iov_[0].iov_base = const_cast<char*>(writeBuffer.beginRead());
    iov_[0].iov_len = writeBuffer.readableBytes();
    iov_[1].iov_base = response.getFile();
    iov_[1].iov_len = response.fileLen();
    poller->modFd(sock->getFd(), EPOLLOUT | EPOLLET | EPOLLONESHOT);
}

bool HttpConn::readNoBlock()
{
    char buf[1024];
    while(true)
    {
        bzero(buf, sizeof(buf));
        int size = sock->read(buf, sizeof(buf));
        if(size > 0)
        {
            LOG_INFO("Real: %s", buf);
            readBuffer.append(buf, size);
        }
        else if(size == -1)
        {
            if(errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            return false;
        }
        else if(size == 0)
        {
            LOG_INFO("Client with fd: %d disconnected", sock->getFd());
            close(sock->getFd());
            return false;
        }
    }
    return true;
}

void HttpConn::handleWrite()
{
    int fd = sock->getFd();
    while(true)
    {
        ssize_t len = writev(sock->getFd(), iov_, iov_count);
        if(len == -1)
        {
            if(errno == EAGAIN)
                poller->modFd(sock->getFd(), EPOLLOUT | EPOLLET | EPOLLONESHOT);
            else
                LOG_FATAL("Writing error.");
            return ;
        }
        
        if(len == iov_[0].iov_len + iov_[1].iov_len)
        {
            writeBuffer.retrieveAll();
            // std::cout << writeBuffer.retrieveAllToStr() << std::endl;
            break;
        }
        else if(iov_[0].iov_len < len)
        {
            size_t res_len = len - iov_[0].iov_len;
            iov_[1].iov_len -= res_len;
            iov_[1].iov_base = static_cast<char*>(iov_[1].iov_base) + res_len;
            iov_[0].iov_len = 0;
            writeBuffer.retrieveAll();
        }
        else
        {
            iov_[0].iov_len -= len;
            writeBuffer.retrieve(len);
        }
    }
    poller->modFd(sock->getFd(), EPOLLIN | EPOLLET | EPOLLONESHOT);
}