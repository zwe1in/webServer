#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "Thread.h"
#include <memory>
#include <assert.h>
#include <future>

template<typename Th>
class PoolBase{
public:
    PoolBase(bool steal, int thread_num=0, int task_cap=0)
        : curIdx(0), threads(nullptr), stop(false), isSteal(steal) 
    {
        assert(thread_num > 0);
        assert(task_cap > 0);
        
        threadNum = thread_num;
        if(task_cap > thread_num)
            threadCap = task_cap / thread_num;
        else
            threadCap = 1;

        moveStepOnce = getBestMoveStep();
    }

    virtual ~PoolBase()
    {
        if(!stop)
        {
            stop = true;
            for(int i = 0; i < threadNum; ++i)
                threads[i].join();
        }
    }

    /**
     * @brief 获取线程数
     * @return 线程数
    */
    int getThreadNum() const { return threadNum; }
    
    /**
     * @brief 设置线程间可以相互夺取任务
     * @param max_num 每个线程可偷取的线程范围，右边的max_num个线程
    */
    void enableSteal(int max_num=0) 
    { 
        assert(max_num < threadNum);
        if(max_num == 0)
        {
            max_num = std::max(threadNum / 4, 1);
            max_num = std::min(max_num, 8);
        }
        maxSteal = max_num;
        isSteal = true;
    }
    /**
     * @brief 关闭线程偷取
    */
    void disableSteal()
    {
        isSteal = false;
    }
    /**
     * @brief 获取池内目前所有的任务数量
    */
    int getTasksNum() const
    {
        int ret = 0;
        for(int i = 0; i < threadNum; ++i)
        {
            ret += threads[i].getTaskNum();
        }
        return ret;
    }

    /**
     * @brief 添加任务
     * @param foo 任务函数
     * @return 返回是否添加成功
    */
    template<typename F>
    bool add(F&& foo)
    {
        if(!hasSpace(1))
        {
            printf("The pool has been full.\n");
            return false;
        }
        toLeastBusyIdx();
        // std::cout << "Add a task." << std::endl;
        threads[curIdx].addTask(std::forward<F>(foo));
        return true;
    }

    /**
     * @brief 添加带有返回值的任务
     * @param foo 任务函数
     * @return 返回future
    */
    template<typename F>
    auto addReturnable(F&& foo) -> std::future<typename std::result_of<F()>::type>
    {
        if(!hasSpace(1))
        {
            printf("The pool has been full.\n");
            return NULL;
        }
        using result_type = typename std::result_of<F()>::type;
        std::packaged_task<result_type()> task = std::forward<F>(foo);
        std::future<result_type> result = task.get_future();
        toLeastBusyIdx();
        threads[curIdx].addTask(std::move(task));
        return result;
    }

    /**
     * @brief 添加批量任务
     * @param foo 任务函数队列
     * @return 返回成功添加的任务数量
    */
    template<typename Container>
    int addSomeTasks(Container& container, size_t size)
    {
        if(hasSpace(size))
        {
            toLeastBusyIdx();
            threads[curIdx].addTasks(container, size);
        }
        else
        {
            for(size_t i = 0; i < size; ++i)
            {
                if(!hasSpace(1))
                    return i;
                else
                {
                    toLeastBusyIdx();
                    threads[curIdx].addTask(std::move(container[i]));
                }
            }
        }
        return size;
    }

protected:
    /**
     * @brief 每次寻找的寻找范围
    */
    int getBestMoveStep()
    {
        int tmp = threadNum / 4;
        tmp = tmp > 1 ? tmp : 1;
        return tmp < 4 ? tmp : 4;
    }

    /**
     * @brief 位置指针循环游走
    */
    void recycyleMove(int &x)
    {
        x = (++x) % threadNum;
    }

    /**
     * @brief 在"寻找范围内"找最空闲的线程
    */
    void toLeastBusyIdx()
    {
        int res = curIdx;
        for(int i = 0; i < moveStepOnce; ++i)
        {
            if(!threads[curIdx].getTaskNum()) return;
            recycyleMove(res);
            if(threads[res].getTaskNum() < threads[curIdx].getTaskNum())
                curIdx = res;
        }
    }

    /**
     * @brief 判断是否有足够的空间添加任务的线程，并将位置指针移动它该线程
     * @param taskNum 要添加的任务数量
    */
    bool hasSpace(int taskNum)
    {
        int tmp = curIdx;
        auto spare = [this, &taskNum](){ return threads[curIdx].getTaskNum() + taskNum <= threadCap; };
        while(!spare())
        {
            recycyleMove(curIdx);
            if(curIdx == tmp)
                return false;
        }
        return true;
    }

    
protected:
    bool stop;      
    int threadNum;  // 线程数
    int threadCap;  // 每个线程的任务容量
    int curIdx;     // 当前指向工作线程
    int moveStepOnce;   // 每次移动访问的范围
    bool isSteal;   // 线程间是否可以窃取任务
    int maxSteal;       // 窃取任务的范围
    std::unique_ptr<Th[]> threads;  // 线程
};


/**
 * @brief 单队列线程的线程池, 支持线程队列之间相互偷取任务
*/
class BalancePool : public PoolBase<OqThread>{
public:
    explicit BalancePool(int thread_num=32, int task_capacity=65536)
        : PoolBase(true, thread_num, task_capacity)
    {
        threads.reset(new OqThread[thread_num]);
        for(size_t i = 0; i < thread_num; ++i)
            threads[i].setJob(SmartThread(&BalancePool::work, this, i));
    }
    ~BalancePool() override = default;

private:
    void work(int idx)
    {
        auto &self = threads[idx];
        while(true)
        {
            if(stop && self.isFree())
                break;
            if(self.isFree())
            {
                if(isSteal)
                {
                    for(int i = idx, j = 0; j < maxSteal; ++j)
                    {
                        recycyleMove(i);
                        if(threads[i].tryGiveTask(self))
                        {
                            self.runTask();
                            break;
                        }
                    }
                }
                if(self.isFree())
                    std::this_thread::yield();
            }
            else
                self.runTask();
        }
    }
};

class SteadyPool : public PoolBase<DqThread>{
public:
    explicit SteadyPool(int thread_num=32, int task_capacity=65536)
        : PoolBase(true, thread_num, task_capacity)
    {
        threads.reset(new DqThread[threadNum]);
        for(int i = 0; i < threadNum; ++i)
            threads[i].setJob(SmartThread(&SteadyPool::work, this, i));
    }

    ~SteadyPool() override = default;

    void work(int idx)
    {
        auto &self = threads[idx];
        while(!stop)
        {
            if(self.isFree())
            {
                if(self.isWaiting())
                {
                    self.notifyComplete();
                    std::this_thread::yield();
                    continue;
                }
                if(isSteal)
                {
                    for(int i = idx, j = 0; j < maxSteal; ++j)
                    {
                        recycyleMove(i);
                        if(threads[i].tryGiveTask(self))
                        {
                            self.runTask();
                            break;
                        }
                    }
                    if(!self.isFree() || self.isWaiting())
                        continue;
                }
                std::this_thread::yield();
            }
            else
            {
                if(self.loadTask())
                    self.runTask();
            }
        }
    }
};

class DynamicPool{
public:
    DynamicPool(int thread_num=64)
        : threadNum(thread_num), tasksNum(0)
    {
        assert(threadNum > 0);
        for(int i = 0; i < threadNum; ++i)
            workers.emplace_back(&DynamicPool::work, this, i);
    }
    ~DynamicPool()
    {
        if(!stop)
        {
            stop = true;
            for(int i = 0; i < threadNum; ++i)
            {
                if(workers[i].joinable())
                    workers[i].join();
            }
        }
    }

    void addThreads(int num)
    {
        assert(num >= 0);
        {
            std::unique_lock<std::mutex> lock(share_mt);
            if(threadToDel > 0)
            {
                if(threadToDel >= num)
                {
                    threadToDel -= num;
                    tasksNum += num;
                    return ;
                }
                else
                {
                    int offset = threadToDel.load(std::memory_order_relaxed);
                    num -= offset;
                    tasksNum += offset;
                }
            }
        }

        int idx = 0;
        while(num--)
        {
            std::unique_lock<std::mutex> lock(share_mt);
            if(!deletedWorkers.empty())
            {
                idx = deletedWorkers.front();
                deletedWorkers.pop();
                lock.unlock();
                if(workers[idx].joinable())
                    workers[idx].join();
                workers[idx] = std::thread(&DynamicPool::work, this, idx);
            }
            else
            {
                lock.unlock();
                idx = workers.size();
                workers.emplace_back(&DynamicPool::work, this, idx);
            }
            threadNum++;
        }
    }
    
    void deleteThreads(int num)
    {
        assert(num >= 0 && num <= threadNum);
        tasksNum -= num;
        threadToDel += num;
        cond.notify_one();  
    }

    void adjustThreads()
    {
        if(threadNum > tasksNum.load(std::memory_order_relaxed))
        {
            deleteThreads((threadNum - tasksNum.load(std::memory_order_relaxed)) / 2);
        }
        else if(threadNum < tasksNum.load(std::memory_order_relaxed))
        {
            addThreads((tasksNum.load(std::memory_order_relaxed) - threadNum));
        }
    }

    template<typename F>
    void add(F&& foo)
    {
        {
            std::unique_lock<std::mutex> lock(share_mt);
            taskQueue.emplace(std::forward<F>(foo));
        }
        tasksNum++;
        cond.notify_one();
    }
    
    template<typename F>
    auto addReturnable(F&& foo) -> std::future<typename std::result_of<F()>::type>
    {
        using result_type = typename std::result_of<F()>::type;
        std::packaged_task<result_type()> task(std::forward<F>(foo));
        std::future<result_type> result = task.get_future();
        {
            std::unique_lock<std::mutex> lock(share_mt);
            taskQueue.emplace(std::move(task));
        }
        tasksNum++;
        cond.notify_one();
        return result;
    }

    template<typename Container>
    void addSomeTasks(Container& container, size_t size)
    {
        for(size_t i = 0; i < size; ++i)
        {
            {
                std::unique_lock<std::mutex> lock(share_mt);
                taskQueue.emplace(std::move(container[i]));
            }
            tasksNum++;
        }
        cond.notify_all();
    }

private:
    void manage()
    {
        while(true)
        {
            adjustThreads();
        }
    }
    void work(int idx)
    {
        Task task;
        while(true)
        {
            std::unique_lock<std::mutex> lock(share_mt);
            cond.wait(lock, [this]{ return !taskQueue.empty() || stop || threadToDel > 0;});
            if(stop && taskQueue.empty()) return;
            if(!taskQueue.empty())
            {
                task = std::move(taskQueue.front());
                taskQueue.pop();
                lock.unlock();
                task();
                --tasksNum;
            }
            else if(threadToDel > 0)
            {
                threadToDel--;
                deletedWorkers.emplace(idx);
                return;
            }

        }
    }
private:
    bool stop;
    int threadNum;
    std::atomic<int> threadToDel;
    std::atomic<int> tasksNum;
    std::thread manager;
    std::vector<std::thread> workers;
    std::mutex share_mt;
    std::condition_variable cond;
    std::queue<Task> taskQueue;
    std::queue<int> deletedWorkers;
};


#endif