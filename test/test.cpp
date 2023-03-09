#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>

static int pipefd[2];
void handleTimeout(int sig)
{
    int msg = sig;
    send(pipefd[1], (char*)&msg, 1, 0);
    printf("%d\n", msg==SIGALRM);
}

int main()
{
    if(socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd) == -1)
    {
        exit(EXIT_FAILURE);
    }
    fcntl(pipefd[1], F_SETFL, fcntl(pipefd[1], F_GETFL) | O_NONBLOCK);
    signal(SIGALRM, handleTimeout);
    alarm(1);
    int epfd = epoll_create1(0);
    epoll_event ev;
    ev.data.fd = pipefd[0];
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, pipefd[0], &ev);
    epoll_event events[20];
    while(1)
    {
        int n = epoll_wait(epfd, events, 20, -1);
        printf("n: %d\n", n);
        for(int i = 0; i < n; ++i)
            if(events[i].data.fd == pipefd[0])
            {
                printf("timeout\n");
            }
    }
    return 0;
}