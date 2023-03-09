#ifndef COMMON_H
#define COMMON_H

class nonCopyable{
public:
    nonCopyable() = default;
    ~nonCopyable() = default;

private:
    nonCopyable(nonCopyable&) = delete;
    nonCopyable(const nonCopyable&) = delete;
    nonCopyable& operator=(const nonCopyable&) = delete;
};

#endif