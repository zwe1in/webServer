#ifndef THREAD_H
#define THREAD_H
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "SpinLock.h"
#include "Task.h"

class SmartThread{
private:
    using ID = std::thread::id;
    using native_handle_type = std::thread::native_handle_type;

public:
    SmartThread() = default;
    template<typename F, typename... Args>
    SmartThread(F&& f, Args&&... args) 
        : thread_(std::forward<F>(f), std::forward<Args>(args)...){}
    SmartThread(SmartThread&) = delete;
    SmartThread(const SmartThread&) = delete;
    SmartThread& operator= (const SmartThread&) = delete;
    SmartThread(SmartThread&& other)
    {
        std::thread tmp = std::move(other.thread_);
        other.thread_ = std::move(thread_);
        thread_ = std::move(tmp);
    }

    SmartThread& operator=(SmartThread&& other)
    {
        if(&other != this)
            SmartThread(std::move(other)).swap(*this);
        return *this;
    }

    ~SmartThread()
    {
        if(thread_.joinable())
            thread_.join();
    }

    void swap(SmartThread& other)
    {
        std::swap(other.thread_, thread_);
    }

    friend void swap(SmartThread& lhs, SmartThread& rhs)
    {
        std::swap(lhs.thread_, rhs.thread_);
    }

    bool joinable() const { return thread_.joinable(); }
    ID getId() const { return thread_.get_id(); }
    native_handle_type getHandleType() { return thread_.native_handle(); }
    static unsigned hardware_concurrency(){ return std::thread::hardware_concurrency(); }

    void join() { thread_.join(); }
    void detach() { thread_.detach(); }

private:
    std::thread thread_;
};


class ThreadBase{
public:
    ThreadBase() : waiting(false), task_num(0){}
    virtual ~ThreadBase() = default;
    int getTaskNum() const { return task_num.load(std::memory_order_relaxed); }
    bool isFree() const { return !task_num; }
    bool isWaiting() const
    {
        return waiting; 
    }
    bool join() 
    { 
        if(woker.joinable())
        {
            woker.join();
            return true;
        }
        return false; 
    }

    void setJob(SmartThread&& other)
    {
        woker = std::move(other);
    }
    
    void waitForTasks()
    {
        std::unique_lock<std::mutex> lock(mt);
        waiting = true;
        complete_cond.wait(lock, [this](){ return isFree(); });
    }

    void cleanWaitingFlag() 
    { 
        std::unique_lock<std::mutex> lock(mt);
        waiting = false;
    }

    void notifyComplete()
    {
        std::unique_lock<std::mutex> lock(mt);
        complete_cond.notify_one();
    }
    
protected:
    bool waiting;
    SmartThread woker;
    std::atomic<int> task_num;
    std::mutex mt;
    std::condition_variable complete_cond;

};


/**
 * @brief 单队列线程
*/
class OqThread : public ThreadBase{
public:
    OqThread() = default;
    ~OqThread() override = default;
    void runTask()
    {
        lock.lock();
        if(!taskQueue.empty())
        {
            task = std::move(taskQueue.front());
            taskQueue.pop();
        }
        lock.unlock();
        task();
        task_num--;
    }

    bool tryGiveTask(OqThread& other)
    {
        if(lock.tryLock())
        {
            if(!taskQueue.empty())
            {
                other.task = std::move(taskQueue.front());
                taskQueue.pop();
                lock.unlock();
                task_num--;
                other.task_num++;
                return true;
            }
            else
            {
                lock.unlock();
                return false;
            }
        }
        return false;
    }

    template<typename T>
    void addTask(T&& t)
    {
        lock.lock();
        taskQueue.emplace(std::forward<T>(t));
        task_num++;
        lock.unlock();
    }

    template<typename Container>
    void addTasks(Container& container, size_t size)
    {
        lock.lock();
        for(size_t i = 0; i < size; ++i)
        {
            taskQueue.emplace(std::move(container[i]));
            task_num++;
        }
        lock.unlock();
    }
private:
    std::queue<Task> taskQueue;
    Task task;
    SpinLock lock;
};

/**
 * @brief 双队列线程
 * */
class DqThread : public ThreadBase{
public:
    void runTask()
    {
        while(!ready_tasks.empty())
        {
            ready_tasks.front()();
            ready_tasks.pop();
            task_num--;
        }
    }

    bool loadTask()
    {
        lock.lock();
        public_tasks.swap(ready_tasks);
        lock.unlock();
        return !ready_tasks.empty();
    }

    bool tryGiveTask(DqThread &t)
    {
        if(lock.tryLock())
        {
            if(!public_tasks.empty())
            {
                int num = public_tasks.size();
                public_tasks.swap(t.ready_tasks);
                lock.unlock();
                task_num -= num;
                t.task_num += num;
                return true;
            }
            else
            {
                lock.unlock();
                return false;
            }
        }
        return false;
    }

    template<typename T>
    void addTask(T&& t)
    {
        lock.lock();
        public_tasks.emplace(std::forward<T>(t));
        task_num++;
        lock.unlock();
    }

    template<typename Container>
    void addTasks(Container& c, size_t size)
    {
        lock.lock();
        for(int i = 0; i < size; ++i)
        {
            public_tasks.emplace(std::move(c[i]));
            task_num++;
        }
        lock.unlock();
    }
private:
    std::queue<Task> public_tasks;
    std::queue<Task> ready_tasks;
    SpinLock lock;
};
#endif