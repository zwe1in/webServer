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
    void handleRead();      // 处理请求解析
    void handleWrite();     // 发送响应

private:
    bool readNoBlock();     // 非阻塞读取

private:
    HttpRequest request;    // Http 请求
    HttpResponse response;  // Http 响应
    Buffer readBuffer;      // 读缓冲区
    Buffer writeBuffer;     // 写缓冲区
    Epoller *poller;        // 总epoller
    Socket *sock;           // 当前连接的socket
    std::string rootPath;   // 根路径
    struct iovec iov_[2];   // 分散内存，文件和响应头内存不连续
    int iov_count;
};

#endif