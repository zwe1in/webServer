#ifndef LOCKFREEQUEUE
#define LOCKFREEQUEUE
#include <atomic>
#include <vector>

/**
 * @brief 基于原子量的无锁队列 
 **/
template<class T, int N=1024>
class LockFreeQueue{
public:
    struct Elem
    {
        T data;
        std::atomic<bool> used;
    };

    LockFreeQueue() : datas(N), readIdx_(0), writeIdx_(0){}

    bool push(const T& elem);
    bool pop(T& elem);
    bool isEmpty() { return writeIdx_.load(std::memory_order_relaxed) == writeIdx.load(std::memory_order_relaxed); }
private:
    std::vector<Elem> datas;
    std::atomic<size_t> readIdx_;
    std::atomic<size_t> writeIdx_;
};

template<class T, int N>
bool LockFreeQueue<T, N>::push(const T& elem)
{
    size_t writeIdx = 0;
    Elem* e = NULL;
    do{
        writeIdx = writeIdx_.load(std::memory_order_relaxed);
        if(writeIdx >= readIdx_.load(std::memory_order_relaxed) + N)
            return false;
        size_t index = writeIdx % N;
        e = &datas[index];
        if(e->used.load(std::memory_order_relaxed))
            return false;       
    }while(!writeIdx_.compare_exchange_weak(writeIdx, writeIdx + 1, std::memory_order_release, std::memory_order_relaxed));
    e->data = std::move(elem);
    e->used.store(true, std::memory_order_release);
    return true;
}

template<class T, int N>
bool LockFreeQueue<T, N>::pop(T& elem)
{
    size_t readIdx = 0;
    Elem* e = NULL;
    do{
        readIdx = readIdx_.load(std::memory_order_relaxed);
        if(readIdx >= writeIdx_.load(std::memory_order_relaxed))
            return false;
        size_t index = readIdx % N;
        e = &datas[index];
        if(!e->used.load(std::memory_order_relaxed))
            return false;       
    }while(!readIdx_.compare_exchange_weak(readIdx, readIdx + 1, std::memory_order_release, std::memory_order_relaxed));
    elem = std::move(e->data);
    e->used.store(false, std::memory_order_release);
    return true;
}

#endif