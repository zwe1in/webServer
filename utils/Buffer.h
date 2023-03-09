#ifndef BUFFER_H
#define BUFFER_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <assert.h>

/**
 * @brief 参考muduo的字符串缓冲区，基于vector为底层容器，设置读位置readIdx、写位置writeIdx
 *          插入时，按照情况重复利用已读空间或新增空间;
 *          |-----------|--------------|----------------------|
 *        begin       readIdx       writeIdx
 * */
class Buffer{
public:
    static const size_t CheapPrepend = 8;
    static const size_t InitialSize = 1024;
    Buffer(size_t initialSize=InitialSize)
        : data(CheapPrepend + initialSize), readIdx(CheapPrepend), writeIdx(CheapPrepend){}
    ~Buffer() = default;
    Buffer(const Buffer&) = default;
    Buffer& operator=(const Buffer& other)
    {
        readIdx = other.readIdx;
        writeIdx = other.writeIdx;
        data.assign(other.data.begin(), other.data.end());
        return *this;
    }
    Buffer(Buffer&& other)
    {
        std::swap(readIdx, other.readIdx);
        std::swap(writeIdx, other.writeIdx);
        other.data.swap(data);
    }
    Buffer& operator=(Buffer&& other)
    {
        if(this != &other)
        {
            std::swap(readIdx, other.readIdx);
            std::swap(writeIdx, other.writeIdx);
            other.data.swap(data);  
        }
        return *this;
    }

    const char* beginRead() const { return begin() + readIdx; }
    char* beginWrite() { return begin() + writeIdx; }
    const char* beginWrite() const { return begin() + writeIdx; }
    size_t readableBytes() const { return writeIdx - readIdx; }
    size_t writableBytes() const { return data.size() - writeIdx; }
    size_t prependaBleBytes() const { return readIdx; }
    void retrieveAll()
    {
        readIdx = CheapPrepend;
        writeIdx = CheapPrepend;
    }
    void retrieveUntil(const char* end)
    {
        assert(end >= beginRead() && end <= beginWrite());
        retrieve(end - beginRead());
    }
    void retrieve(size_t size)
    {
        assert(size <= readableBytes());
        if(size < readableBytes())
        {
            readIdx += size;
        }
        else
        {
            retrieveAll();
        }
    }
    std::string retrieveToStr(size_t size)
    {
        assert(size <= readableBytes());
        std::string res(beginRead(), size);
        retrieve(size);
        return res;
    }
    std::string retrieveAllToStr()
    {
        return retrieveToStr(readableBytes());
    }
    void append(const char* str, size_t len)
    {
        if(writableBytes() < len)
        {
            makeSpace(len);
        }
        std::copy(str, str + len, begin() + writeIdx);
        writeIdx += len;
    }
    void append(std::string str)
    {
        append(str.c_str(), str.size());
    }
    
private:
    char* begin() { return &*data.begin(); }
    const char* begin() const { return &*data.begin(); }
    void makeSpace(size_t len)
    {
        if(writableBytes() + prependaBleBytes() < len + CheapPrepend)
        {
            data.resize(writeIdx + len);
        }
        else
        {
            size_t readable = readableBytes();
            std::copy(begin() + readIdx, begin() + writeIdx, begin() + CheapPrepend);
            readIdx = CheapPrepend;
            writeIdx = readIdx + readable;
        }
    }
private:
    size_t readIdx;
    size_t writeIdx;
    std::vector<char> data;
};

#endif