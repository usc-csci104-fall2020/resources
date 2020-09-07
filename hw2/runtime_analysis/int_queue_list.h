#ifndef INT_QUEUE_LIST_H
#define INT_QUEUE_LIST_H

#include "int_queue.h"
#include <list>
#include <stdexcept>


// This class implements the queue ADT interface using STL list. Remember STL
// list is a doubly linked list implementation.
class ListIntQueue : public IntQueue {
public:
    int front() {
        // We can throw an exception here to indicate that the queue is empty.
        // In practice, throwing an exception here prevents us from having to
        // choose some arbitrary int to return when we don't have any elements
        // to actually choose from. We'll learn more about exceptions soon.
        if (this->empty()) {
            throw std::out_of_range("no elements");
        }
        return queue.front();
    }

    bool empty() {
        return queue.empty();
    }

    size_t size() {
        return queue.size();
    }

    void push_back(int value) {
        queue.push_back(value);
    }

    void pop_front() {
        // We don't need to throw here; if we pop with nothing, nothing really
        // has to happen.
        if (!empty()) {
            queue.pop_front();
        }
    }

private:
    std::list<int> queue;
};

#endif
