#include "SQLConnPool.h"

SQLConnPool::SQLConnPool(int maxNum_, int initialNum)
    : maxNum(maxNum_), curNum(initialNum), busyNum(0), stop(false)
{}

SQLConnPool::~SQLConnPool()
{
    std::unique_lock<std::mutex> lock(mt);
    stop = true;
    cond.wait(lock, [this]{
        return busyNum == 0;
    });
    
    while(!freeQue.empty())
        freeQue.pop_front();
}

bool SQLConnPool::init(
        const std::string& host_, 
        const std::string& name_,
        const std::string& password_,
        const std::string& dbName_,
        unsigned int port_)
{
    host = host_;
    name = name_;
    password = password_;
    dbName = dbName_;
    port = port_;
    for(int i = 0; i < curNum; ++i)
        freeQue.emplace_back(name.c_str(), password.c_str(), dbName.c_str(), host.c_str(), port);
}

bool SQLConnPool::acquire(SQLConnection& cont)
{
    std::lock_guard<std::mutex> lock(mt);
    if(stop)
    {
        LOG_INFO("Connection pool is closing.");
        return false;
    }
    if(curNum == busyNum)
    {
        if(curNum < maxNum)
        {
            cont = SQLConnection(name.c_str(), password.c_str(), dbName.c_str(), host.c_str(), port);
            ++curNum;
            ++busyNum;
        }
        else
        {
            LOG_INFO("No free link for use.");
            return false;
        }
    }
    else
    {
        cont = std::move(freeQue.front());
        freeQue.pop_front();
        ++busyNum;
    }
    
    return true;
}

bool SQLConnPool::release(SQLConnection&& cont)
{
    std::lock_guard<std::mutex> lock(mt);
    try{
        freeQue.emplace_back(std::move(cont));
        --busyNum;
        cond.notify_all();
    }
    catch(int i)
    {
        LOG_FATAL("SQL release fail.");
        return false;
    }
    return true;
}

