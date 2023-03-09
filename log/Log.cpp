#include "Log.h"

void Log::init(LOGTARGET target_, bool async, const char* file)
{
    target = target_;
    isAsync = async;
    buffer = new char[LOGBUFSIZE];
    if(target == LOGTARGET::FILE || target == LOGTARGET::BOTH)
        ofile.open(file, std::ios::app | std::ios::out);
    if(isAsync)
    {
        stop = false;
        que = new BlockQueue<std::string>();
        std::thread t(&Log::asyncWrite, getInstance());
        writeThread = std::move(t);
    }
}

void Log::writeLog(LOGLEVEL level, 
                    const char* fileName, 
                    const char* funcName, 
                    int line, 
                    const char* format, ...)
{
    time_t t = time(NULL);
    struct tm *today = localtime(&t);
    
    char s[16];
    switch (level)
    {
    case INFO:
        strcpy(s, "[INFO]:");
        break;
    case DEBUG:
        strcpy(s, "[DEBUG]:");
        break;
    case WARN:
        strcpy(s, "[WARN]:");
        break;
    case FATAL:
        strcpy(s, "[FATAL]:");
        break;
    default:
        break;
    }

    va_list valst;
    va_start(valst, format);
    std::string logMsg;
    {
        bzero(buffer, LOGBUFSIZE);
        std::unique_lock<std::mutex> lock(mt);
        int n = snprintf(buffer, LOGBUFSIZE - 1, "%d-%02d-%02d %02d:%02d:%06d %s [file: %s ][function: %s ][line %d ] ",
                        today->tm_year + 1900, today->tm_mon + 1, today->tm_mday, today->tm_hour, today->tm_min, today->tm_sec,
                        s, fileName, funcName, line);
        int m = vsnprintf(buffer + n, LOGBUFSIZE - 1, format, valst);
        buffer[m + n] = '\n';
        buffer[m + n + 1] = '\0';
        logMsg = buffer;
    }
    va_end(valst);
    if(isAsync)
        que->push(logMsg);
        // while(!que->push(logMsg));
    else
        flush(logMsg);
}

void Log::asyncWrite()
{
    std::string msg;
    while(!stop || !que->isEmpty())
    {
        // if(que->pop(msg))
            // flush(msg);
        que->pop(msg);
        flush(msg);
    }
}

void Log::flush(std::string& msg)
{
    std::unique_lock<std::mutex> lock(mt);
    switch(target)
    {
        case LOGTARGET::FILE:
            ofile << msg;
            break;
        case LOGTARGET::CONSOLE:
            std::cout << msg;
            break;
        case LOGTARGET::BOTH:
            ofile << msg;
            std::cout << msg;
            break;
        default:
            break;
    }
}