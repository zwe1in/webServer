#include "Epoller.h"

Epoller::Epoller(int max_event)
    : epfd(-1), max_event_count(max_event)
{
    events = new epoll_event[max_event];
    epfd = epoll_create1(0);
    if(epfd == -1)
    {
        LOG_FATAL("Epoller create fail");
        exit(EXIT_FAILURE);
    }
}

Epoller::~Epoller()
{
    delete events;
    if(epfd != -1)
    {
        close(epfd);
        epfd = -1;
    }
}

bool Epoller::addFd(int fd, uint32_t event)
{
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    return epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == 0;
}

bool Epoller::modFd(int fd, uint32_t event)
{
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    return epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == 0;
}

bool Epoller::delFd(int fd)
{
    return epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) == 0;
}

int Epoller::wait(int timeout)
{
    int nfds = epoll_wait(epfd, events, max_event_count, timeout);
    return nfds;
}
const epoll_event& Epoller::getEvent(size_t idx) const
{
    return events[idx];
}