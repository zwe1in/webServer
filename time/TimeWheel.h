#ifndef TIMEWHEEL_H
#define TIMEWHEEL_H
#include "../http/HttpConn.h"
#include "../log/Log.h"
#include <memory>
#include <vector>
#include <mutex>

typedef std::shared_ptr<HttpConn> connPtr;
typedef std::weak_ptr<HttpConn> connWeakPtr;

/**
 * @brief 计时器节点，以双向链表的结构存储，每个定时器存放一个连接的共享指针，当所有该连接的
 *          定时器都释放了，就会对该连接进行断开。 
 **/
struct Timer{
    int rotation;
    int slot_num;
    connPtr cont;
    Timer *prev;
    Timer *next;
    Timer(connPtr cont_) : rotation(0), slot_num(0), cont(cont_), prev(nullptr), next(nullptr){}
    Timer(connWeakPtr cont_, int rotation_, int slot_)
        : rotation(rotation_), slot_num(slot_), prev(nullptr), next(nullptr)
    {
        if(cont_.lock())
            cont = cont_.lock();
    }
    Timer(connWeakPtr cont_, int rotation_, int slot_, Timer *prev_, Timer *next_)
        : rotation(rotation_), slot_num(slot_), prev(prev_), next(next_)
    {
        if(cont_.lock())
            cont = cont_.lock();
    }
};

/**
 * @brief 时间轮，60个槽，每个槽表示1s
 * */
class TimeWheel{
public:
    TimeWheel();
    ~TimeWheel();
    Timer* addTimer(time_t expire, connWeakPtr wptr);
    void removeTimer(Timer *tm);
    void tick();
private:
    int curSlot;
    std::vector<Timer*> bucket;
    std::mutex mt;
    static const int SLOTNUM = 60;
    static const int SI = 1;
};



#endif