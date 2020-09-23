
#include <iostream>
#include <memory>
#include <stdexcept>  

using namespace std;

template <typename T>
class BAList {
public:
  BAList(unsigned int cap);
  ~BAList(){}
  bool empty() const  {return size_==0;}
  unsigned int  size() const {return size_;}
  void insert(int pos, const T& val);
  void remove(int pos);
  // Extra exercises
  //T const & get(int loc) const;
  T& get(int loc) { return data_[loc];}
  //void set(int loc, const T& val);
  void push_back(const T& val);
  private:
  unique_ptr<T []> data_;
  unsigned int size_;
  unsigned int cap_;
  
  };



int main()
{
    BAList<int> test(20);
    try {
       for (int i = 0; i < 10; i++)
            test.push_back(i);
    
       test.insert(4, 15);
       test.remove(7);
       cout << test.size() << endl;
       for (int j = 0 ; j < test.size(); j++)
           cout << test.get(j) << endl;
    } catch (out_of_range e){
       cout << e.what() << endl;
    }

    return 0;
}

template <typename T>
BAList<T>::BAList (unsigned int cap): size_(0), cap_(cap)   
   {
      data_ = make_unique<T[]>(cap_);
   }

template <typename T>
void BAList<T>::push_back(const T& val){
   if(size_ < cap_){
      data_[size_++] = val;  
   } else {
       throw out_of_range("No space in array list");
   }
  
}

template <typename T>
void BAList<T>::insert(int loc, const T& val){
   if(loc >= 0 && loc <= size_ && size_+1 <= cap_){
      if(size_ < cap_){
         for(int i=size_-1; i >= loc; i--){
            data_[i+1] = data_[i];
         }
         data_[loc] = val;
         size_++;
       }
   } else {
       throw out_of_range("invalid insertion");
   }
}

template <typename T>
void BAList<T>::remove(int loc) {  
  if (empty()) return;
  if(loc >= 0 && loc <= size_-1){
         for(int i=loc; i < size_-1 ; i++){
            data_[i] = data_[i+1];
         }
         // cannot assume what value to overwrite data_[size_-1] = 0;
         size_--;
   } else {
    throw out_of_range("removal location");
      
   }

}
