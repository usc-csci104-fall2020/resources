#include <vector>
#include <functional>
#include <iostream>
#include <cstdlib>
#include "heap.h"

using namespace std;


int main() {
    Heap<int, greater<int> > max_heap(2);

    for(size_t i = 0; i < 20; i++) {
        max_heap.push(rand() % 100);
    }

    while (!max_heap.empty()) {
        cout << max_heap.top() << " ";
        max_heap.pop();
    }
    cout << endl;

    Heap<int> min_heap(3);

    for (size_t i = 0; i < 20; i++) {
        min_heap.push(rand() % 100);
    }

    while (!min_heap.empty()) {
        cout << min_heap.top() << " ";
        min_heap.pop();
    }
    cout << endl;

    return 0;
}
