#include <memory>
#include <iostream>
#include "selectionsort.h"
using namespace std;

shared_ptr<Item> findMin(shared_ptr<Item>& head){
    if(head == nullptr) return nullptr;
    shared_ptr<Item> tmp =  head;
    shared_ptr<Item> min = head; 
    int v = tmp->getValue();
    while(tmp != nullptr){
        if(tmp->getValue() < v) {
            v = tmp->getValue();
            min = tmp;
        } 
        tmp = tmp->next;
    } 

    if (min == head) {
        head = head->next;
        head->prev = nullptr;
    } else if (min->next == nullptr){
	if (min->prev != nullptr){
         min->prev->next = nullptr;
       }
   } else {
      min->prev->next = min->next;
      min->next->prev = min->prev;
   }

    min->next = nullptr;
    min->prev = nullptr;
    return min;
} 

shared_ptr<Item> LLSelectionSort(shared_ptr<Item> head){
    if(head == nullptr || head->next == nullptr) 
        return head;

    
    shared_ptr<Item> min = findMin(head);

    min->next = LLSelectionSort(head);
    if (head != nullptr) head->prev = min;
    
    return min;
} 

int main(){

   shared_ptr<Item> a = make_shared<Item>(2);
 
   shared_ptr<Item> b = make_shared<Item>(11);
   shared_ptr<Item> c = make_shared<Item>(23); 
   shared_ptr<Item> d = make_shared<Item>(3); 
   a->next = b;
   b->prev = a;
   b->next = c;
   c->prev = b;
   d->prev = c;
   c->next = d;

  shared_ptr<Item> sorted = LLSelectionSort(a);

  shared_ptr<Item> temp = sorted;

  while (temp != nullptr){

      cout << "Current value " << temp->getValue() << endl;
      temp = temp->next;
  }

}

