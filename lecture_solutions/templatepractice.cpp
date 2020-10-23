#include <iostream>
#include <memory>
using namespace std;

// Item definition - do NOT change
template <typename T>
struct Item {
    T val;
    shared_ptr<Item<T>> next;
    // Constructor for convenience of testing
    Item<T>(T v, shared_ptr<Item<T>> n): val(v), next(n) {}
};


// Sample comparator for reference and testing
struct isEven {
    bool operator()(int v) {
        return v%2 == 0;
    }

};


template <typename T, typename functor>
struct change {
    void operator()(shared_ptr<Item<T>> p, functor changer){
        changer(p->val);
    }
};

struct increment {
    void operator()(int& t){
        t++;
    }
};

//
template <class T, class Compare, class Change>
void changeCond(shared_ptr<Item<T>> head, Compare comp, Change update);

template <class T, class Compare, class Change2, class change3>
void changeCond2(shared_ptr<Item<T>> head, Compare comp, Change2 update, change3 update2);


template<class T>
void printList(shared_ptr<Item<T>> list) {
    shared_ptr<Item<T>> tmp = list;
    while(tmp != NULL) {
        cout << tmp->val << " ";
        tmp =tmp->next;
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    shared_ptr<Item<int>> head;
    shared_ptr<Item<int>> curr;
    for(int i = 1; i < argc; i++) {
        if(i==1) {
            head = make_shared<Item<int>>(atoi(argv[i]), nullptr); 
            curr = head;
        } else {
            curr->next = make_shared<Item<int>>(atoi(argv[i]), nullptr); 
            curr = curr->next;
        }
    }

    cout << "Original list: " << endl;
    printList(head);

    isEven comp1;
    increment cond2;
    change<int, increment> cond3;

    changeCond(head,comp1, cond2);
    //changeCond2(head,comp1, cond3, cond2);


    cout << "After changing " << endl;
    printList(head);

    // Don't worry about freeing memory.
    // We know it is necessary to avoid memory leaks...
    return 0;

}

template <class T, class Compare, class Change>
void changeCond(shared_ptr<Item<T>> head, Compare comp, Change update){
       if (head == nullptr) return;
       if (comp(head->val)){
           update(head->val);
       }
       changeCond(head->next, comp, update);
    
}

template <class T, class Compare, class Change2, class change3>
void changeCond2(shared_ptr<Item<T>> head, Compare comp, Change2 update, change3 update2){
     if (head == nullptr) return;
       if (comp(head->val)){
           update(head, update2);
       }
       changeCond2(head->next, comp, update, update2);
    

}
