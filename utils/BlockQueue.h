#ifndef BLOCKQUEUE_H
#define BLOCKQUEUE_H
#include <vector>
#include <mutex>
#include <condition_variable>
/**
 * @brief 阻塞队列，使用两个互斥量管理队列
 * @author zwlin
 * */
template<class T, int N=1024>
class BlockQueue{
public:
    BlockQueue() : data(N), readIdx(0), writeIdx(0){}
    ~BlockQueue(){}
    void push(const T& elem);
    void pop(T& elem);
    bool isEmpty();
    bool isFull();
private:
    size_t readIdx;     // 读位置
    size_t writeIdx;    // 写位置
    std::vector<T> data;
    std::mutex mt;
    std::condition_variable notFull, notEmpty;
};

template<class T, int N>
void BlockQueue<T, N>::push(const T& elem)
{
    std::unique_lock<std::mutex> lock(mt);
    while(writeIdx - readIdx >= N)
        notFull.wait(lock);
    size_t index = writeIdx % N;
    writeIdx++;
    data[index] = elem;
    notEmpty.notify_all();
}

template<class T, int N>
void BlockQueue<T, N>::pop(T& elem)
{
    std::unique_lock<std::mutex> lock(mt);
    while(readIdx >= writeIdx)
        notEmpty.wait(lock);
    size_t index = readIdx % N;
    readIdx++;
    elem = data[index];
    notFull.notify_all();
}

template<class T, int N>
bool BlockQueue<T, N>::isEmpty()
{
    std::unique_lock<std::mutex> lock(mt);
    return readIdx == writeIdx;
}

template<class T, int N>
bool BlockQueue<T, N>::isFull()
{
    std::unique_lock<std::mutex> lock(mt);
    return writeIdx - readIdx >= N;
}
#endif