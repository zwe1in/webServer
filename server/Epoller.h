#ifndef EPOLLER_H
#define EPOLLER_H
#include "../log/Log.h"
#include <sys/epoll.h>
#include <unistd.h>
#include "../utils/Common.h"
class Epoller : nonCopyable{
public:
    Epoller(int max_event=1024);
    ~Epoller();
    bool addFd(int fd, uint32_t event);
    bool modFd(int fd, uint32_t event);
    bool delFd(int fd);
    int wait(int timeout=-1);
    const epoll_event& getEvent(size_t idx) const;
private:
    int max_event_count;
    epoll_event* events;
    int epfd;
};


#endif