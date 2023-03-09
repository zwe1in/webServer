#pragma once
#ifndef HTTPCONN_H
#define HTTPCONN_H
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "../server/Epoller.h"
#include "../tcp/Socket.h"
#include <sys/mman.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string>
#include <errno.h>
#include "../utils/Buffer.h"
#include "../log/Log.h"

class HttpConn{
public:
    HttpConn(Epoller *poller_, Socket *sock_, const std::string& root);
    ~HttpConn();
    void handleRead();
    void handleWrite();

private:
    bool readNoBlock();

private:
    HttpRequest request;
    HttpResponse response;
    Buffer readBuffer;
    Buffer writeBuffer;
    Epoller *poller;
    Socket *sock;
    std::string rootPath;
    struct iovec iov_[2];   // 分散内存，文件和响应头内存不连续
    int iov_count;
};

#endif