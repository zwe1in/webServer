#ifndef SPINLOCK_H
#define SPINLOCK_H
#include <atomic>

class SpinLock{
public:
    SpinLock() : flag(ATOMIC_FLAG_INIT){}
    ~SpinLock() = default;
    void lock()
    {
        while(flag.test_and_set(std::memory_order_acquire));
    }
    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
    bool tryLock()
    {
        return !flag.test_and_set();
    }
private:
    std::atomic_flag flag;
};

#endif