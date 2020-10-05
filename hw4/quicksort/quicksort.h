#ifndef QSORT_H
#define QSORT_H

#include <vector>
#include <algorithm>


template<class T, class TComparator>
T& median_of_three(T& a, T& b, T& c, TComparator comparator) {
    // TODO: implement.
}

template<class T, class TComparator>
size_t partition(std::vector<T>& vec, TComparator& comparator, size_t low, size_t high) {
	  // TODO: implement.
}

template<class T, class TComparator>
void quicksort(std::vector<T>& vec, TComparator comparator) {
    // TODO: implement.
}

#endif
