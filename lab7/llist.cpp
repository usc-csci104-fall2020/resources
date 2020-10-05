#include "llist.h"
 
LList::Item::Item(const int& v, Item* p, Item* n)
: val(v), prev(p), next(n)
{
}

LList::LList() {
  mHead = new Item(int(), nullptr, nullptr);
  mTail = mHead;
  mSize = 0;
}

LList::LList(const LList& other) {
  mHead = new Item(int(), nullptr, nullptr);
  mTail = mHead;
  mSize = 0;
  Item* temp = other.mHead;
  while(temp != other.mTail){
    push_back(temp->val);
    temp = temp->next;
  }
}

LList& LList::operator=(const LList& other) {
  if(this == &other){
    return *this;
  }
  clear();
  Item* temp = other.mHead;
  while(temp != other.mTail){
    push_back(temp->val);
    temp = temp->next;
  }
  return *this;
}

LList::~LList() {
  clear();
  delete mHead;
}

int LList::size() const {
  return mSize;
}

bool LList::empty() const {
  return mSize == 0;
}

void LList::push_back(const int& val) {
  Item* n = new Item (val, mTail->prev, mTail);
  if(mHead == mTail){
    mHead = n;
  }
  else
  {
    mTail->prev->next = n;
  }
  mTail->prev = n;
  ++mSize;
}

int& LList::get(int loc) {
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LList::clear() {
  while(mHead != mTail) {
    Item *temp = mHead->next;
    delete mHead;
    mHead = temp;
  }
  mSize = 0;
}

typename LList::Item* LList::getNodeAt(int loc) const {
  if(loc >= 0 && loc < mSize){
    Item *temp = mHead;
    while(loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    return nullptr;
  }
}