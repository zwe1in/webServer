#include "TimeWheel.h"

TimeWheel::TimeWheel()
    : bucket(SLOTNUM), curSlot(0)
{}

TimeWheel::~TimeWheel()
{
    for(int i = 0; i < SLOTNUM; ++i)
    {
        Timer *head = bucket[i];
        while(head)
        {
            Timer *tmp = head->next;
            tmp->prev = nullptr;
            delete head;
            head = tmp;
            bucket[i] = head;
        }
    }
}

Timer* TimeWheel::addTimer(time_t expire, connWeakPtr wptr)
{
    std::unique_lock<std::mutex> lock(mt);
    int slot = (curSlot + expire % (SLOTNUM * SI)) % (SLOTNUM * SI);
    int rotation = expire / (SLOTNUM * SI);
    Timer *res = new Timer(wptr, rotation, slot);
    if(!bucket[slot])
        bucket[slot] = res;
    else
    {
        bucket[slot]->prev = res;
        res->next = bucket[slot];
        bucket[slot] = res;
    }
    return res;
}

void TimeWheel::removeTimer(Timer *tm)
{
    std::unique_lock<std::mutex> lock(mt);
    int slotN = tm->slot_num;
    Timer *head = bucket[slotN];

    while(head)
    {
        if(tm == head)
        {
            if(head == bucket[slotN])
            {
                bucket[slotN] = head->next;
                if(bucket[slotN])
                    bucket[slotN]->prev = nullptr;
                delete tm;
            }
            else
            {
                tm->prev->next = tm->next;
                if(tm->next)
                    tm->next->prev = tm->prev;
                delete tm;
            }
            break;
        }
        head = head->next;
    }
}

void TimeWheel::tick()
{
    std::unique_lock<std::mutex> lock(mt);
    Timer *head = bucket[curSlot];
    while(head)
    {
        if(head->rotation)
        {
            head->rotation--;
            head = head->next;
        }
        else
        {
            if(head == bucket[curSlot])
            {
                bucket[curSlot] = head->next;
                delete head;
                head = bucket[curSlot];
                if(head)
                    head->prev = nullptr;
            }
            else
            {
                head->prev->next = head->next;
                if(head->next)
                    head->next->prev = head->prev;
                Timer *tmp = head->next;
                delete head;
                head = tmp;
            }
        }
    }
    curSlot = ++curSlot % SLOTNUM;
}