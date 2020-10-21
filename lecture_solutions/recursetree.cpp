#include<iostream>
#include <memory>
#include <algorithm>
using namespace std;

template <typename T>
struct Item {    
    T val;    
    shared_ptr<Item<T>> left;    
    shared_ptr<Item<T>> right;      
    shared_ptr<Item<T>> parent;    
  };
  
  // Bin. Search Tree
  template <typename T>
  class BinTree {    
        public:    
        BinTree()= default;    
        ~BinTree()= default; // Yes, there are memory leaks now    
        // Add is provided for you and adds node to tree with value v
        void add(const T& v) ;    
        // Implement count recursively to return the number of nodes in the tree
        int count();    
        // Implement height recursively to return the height of the tree
        int height();   
        private:   
        shared_ptr<Item<T>> root;   
        // You may add private data members and functions
        int countHelper(shared_ptr<Item<T>> r);
        int heightHelper(shared_ptr<Item<T>> r);
  };
     
 
 
 template <typename T>
 int BinTree<T>::countHelper(shared_ptr<Item<T>> r){
     if (r == nullptr) return 0;
     return 1 + countHelper(r->left) + countHelper(r->right);
 }
 
 template <typename T>
 int BinTree<T>::count(){
     return countHelper(root);
 }
 
 template <typename T>
 int BinTree<T>::heightHelper(shared_ptr<Item<T>> r){
     if (r == nullptr) return 0;
     return 1 + max( heightHelper(r->left), heightHelper(r->right));
 }
 
 template <typename T>
 int BinTree<T>::height(){
     return heightHelper(root);
 }
 
 
   
   int main(){    
       BinTree<int> b1;    
       b1.add(4);    
       b1.add(5);    
       b1.add(3);    
       b1.add(9);    
       b1.add(7);    
       cout << "num of nodes " << b1.count() << endl;    
       cout << "height " << b1.height() << endl;    
       return 0;
   }


 template <typename T>
 void BinTree<T>::add(const T& v) {        
        if (root == nullptr){            
            root = make_shared<Item<T>>();            
            root->val = v;        
         } else {                        
            shared_ptr<Item<T>> temp = root;                
            while (temp != nullptr){                
                if (v <= temp->val){                    
                   if (temp->left == nullptr){                        
                       temp->left = make_shared<Item<T>>();                        
                       temp->left->val =v;                        
                       temp->left->parent = temp;                        
                       return;                    
                    }                    
                    temp = temp->left;                
                } else {                    
                     if (temp->right==nullptr){                       
                         temp->right = make_shared<Item<T>>();                        
                         temp->right->val = v;                        
                         temp->right->parent = temp;                        
                         return;                   
                      }                    
                      temp = temp->right;                
                 }            
             }        
          }    
             
   }
