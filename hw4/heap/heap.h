#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>


template<typename T, typename TComparator = std::less<T> >
class Heap {
public:
    // Constructs an m-ary heap for any m >= 2
    Heap(size_t m, TComparator comparator = TComparator());

    // Destructor as needed
    ~Heap();

    // Adds an item
    void push(const T& item);

    // returns the element at the top of the heap
    //  max (if max-heap) or min (if min-heap)
    const T& top() const;

    // Removes the top element
    void pop();

    // returns true if the heap is empty
    bool empty() const;

private:
    // Add whatever helper functions and data members you need below

    // heapify() helper function
    void heapify(size_t loc);

    // Data
    std::vector<T> store;
    size_t m;
    TComparator comparator;
};

template<class T, class TComparator>
const T& Heap<T, TComparator>::top() const {
    // If nothing to top:
    // throw std::logic_error("can't top an empty heap");
}

template<class T, class TComparator>
void Heap<T, TComparator>::pop() {
    // If nothing to pop
    // throw std::logic_error("can't pop an empty heap");
}

#endif
