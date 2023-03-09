#ifndef LOG_H
#define LOG_H
#include <time.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <cstdarg>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
// #include "../utils/LockFreeQueue.h"
#include "../utils/BlockQueue.h"
#include <string>
#include <string.h>

#define LOGBUFSIZE 8192
enum LOGLEVEL{
    INFO, DEBUG, WARN, FATAL
};

enum class LOGTARGET{
    FILE, CONSOLE, BOTH
};

class Log{
public:
    static Log* getInstance()
    {
        static Log instance;
        return &instance;
    }
    void init(LOGTARGET target_, bool async, const char* file);
    void writeLog(LOGLEVEL level, const char* fileName, const char* funcName, int line, const char* format, ...);
    void flush(std::string& msg);
private:
    Log(){}
    ~Log()
    {
        stop = true;
        if(writeThread.joinable())
            writeThread.join();
    }
    void asyncWrite();
private:
    LOGTARGET target;
    std::ofstream ofile;
    char* buffer;
    bool isAsync;
    bool stop;
    BlockQueue<std::string> *que;
    std::mutex mt;
    std::thread writeThread;
};

#define LOG_INFO(format, ...) Log::getInstance()->writeLog(INFO, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) Log::getInstance()->writeLog(DEBUG, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) Log::getInstance()->writeLog(WARN, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) Log::getInstance()->writeLog(FATAL, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#endif