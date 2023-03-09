#pragma once
#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H
#include <atomic>
#include <vector>

template<class T, size_t N=1024>
class LockFreeQueue{
public:
    struct Element
    {
        std::atomic<bool> full_;
        T data;
    };
    
    LockFreeQueue() : datas_(N)
    {
        readIdx_ = 0;
        writeIdx_ = 0;
    }

    bool push(T& elem);
    bool pop(T& elem);
    ~LockFreeQueue(){}
private:
    std::vector<Element> datas_;
    std::atomic<size_t> readIdx_;
    std::atomic<size_t> writeIdx_;
};

template<class T, size_t N>
bool LockFreeQueue<T, N>::push(T& elem)
{
    size_t writeIdx = 0;
    Element *e = NULL;
    do{
        writeIdx = writeIdx_.load(std::memory_order_relaxed);
        if(writeIdx >= readIdx_.load(std::memory_order_relaxed) +  N)
        {
            printf("Queue has been full.\n");
            return false;
        }
        size_t index = writeIdx % N;
        e = datas_[index];
        if(e->full_.load(std::memory_order_relaxed))
            return false;
    }while(writeIdx_.compare_exchange_weak(writeIdx, writeIdx + 1, std::memory_order_release, std::memory_order_relaxed));
    
    e->data = std::move(elem);
    e->full_.store(true, std::memory_order_release);
    return true;
}

template<class T, size_t N>
bool LockFreeQueue<T, N>::pop(T& elem)
{
    size_t readIdx = 0;
    Element* e = NULL;
    do{
        readIdx = readIdx_.load(std::memory_order_relaxed);
        if(readIdx >= writeIdx_.load(std::memory_order_relaxed))
        {
            printf("Queue is empty.\n");
            return false;
        }
        size_t index = readIdx % N;
        e = datas_[index];
        if(!e->full_.load(std::memory_order_relaxed))
            return false;
    }while(readIdx_.compare_exchange_weak(readIdx, readIdx + 1, std::memory_order_release, std::memory_order_relaxed));
    elem = std::move(e->data);
    e->full_.store(false, std::memory_order_release);
    return true;
}

#endif