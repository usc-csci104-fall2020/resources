class LList{
private:
  struct Item {
    Item(const int& v, Item* p, Item* n);
    int val;
    Item *prev;
    Item *next;
  };

public:
  LList();
  LList(const LList& other);
  LList& operator=(const LList& other);
  ~LList();

  int size() const;
  bool empty() const;
  void push_back(const int& val);
  int& get(int pos);
  void clear();

private:
  Item* getNodeAt(int pos) const;

  Item* mHead;
  Item* mTail;
  int mSize;
};