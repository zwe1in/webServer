#pragma once
#ifndef SQLCONNPOOL_H
#define SQLCONNPOOL_H
#include <mysql/mysql.h>
#include <string>
#include <list>
#include <mutex>
#include <condition_variable>
#include "../log/Log.h"
#include "SQLConnection.h"

class SQLConnPool{
public:
    static SQLConnPool* getInstance()
    {
        static SQLConnPool pool;
        return &pool;
    }
    bool init(
        const std::string& host_, 
        const std::string& name_,
        const std::string& password_,
        const std::string& dbName_,
        unsigned int port_);
    
    bool acquire(SQLConnection& cont);
    bool release(SQLConnection&& cont);

private:
    SQLConnPool(int maxNum_=50, int initialNum=5);
    ~SQLConnPool();
private:
    int maxNum;
    int curNum;
    int busyNum;
    bool stop;
    std::mutex mt;
    std::condition_variable cond;
    std::list<SQLConnection> freeQue;
    std::string host;
    std::string name;
    std::string password;
    std::string dbName;
    unsigned int port;
};

#define SQLPoolInit(host, name, password, dbName, port) SQLConnPool::getInstance()->init(host, name, password, dbName, port)
#define SQLAcquire(cont) SQLConnPool::getInstance()->acquire(cont)
#define SQLRelease(cont) SQLConnPool::getInstance()->release(cont)

#endif