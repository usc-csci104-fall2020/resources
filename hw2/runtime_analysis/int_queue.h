#ifndef INT_QUEUE_H
#define INT_QUEUE_H

#include <cstddef>


class IntQueue {
public:
    virtual int front() =  0;
    virtual bool empty() = 0;
    virtual size_t size() = 0;
    virtual void push_back(int v) = 0;
    virtual void pop_front() = 0;
};

#endif
