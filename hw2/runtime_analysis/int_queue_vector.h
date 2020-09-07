#ifndef VECTOR_INT_QUEUE_H
#define VECTOR_INT_QUEUE_H

#include "int_queue.h"
#include <vector>
#include <stdexcept>


// This class implements the queue ADT interface using STL vector. Remember STL
// vector is a dynamically sized array.
class VectorIntQueue : public IntQueue {
public:
    int front() {
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

    void push_back(int v) {
        queue.push_back(v);
    }

    void pop_front() {
        if (!empty()) {
            queue.erase(queue.begin());
        }
    }

private:
   std::vector<int> queue;
};

#endif



