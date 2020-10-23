#include<iostream>
#include <memory>
#include <algorithm>
using namespace std;


struct Node {    
    int val;    
    shared_ptr<Node> left;    
    shared_ptr<Node> right;      
  };
  
  

// Write a recursive function to have each node store the sum of
// the values on the path from the root to each node.
 void prefix(shared_ptr<Node> root);
 void prefixH(shared_ptr<Node> root, int psum);
 
 // Write a recursive function to print the binary tree in 
 // preorder traversal order
 void print_preorder(shared_ptr<Node> root);
 
 
   
   int main(){   
       shared_ptr<Node> head = make_shared<Node>();
       shared_ptr<Node> l = make_shared<Node>();
       shared_ptr<Node> r = make_shared<Node>();
       shared_ptr<Node> ll = make_shared<Node>();
       shared_ptr<Node> lr = make_shared<Node>();
       head->val = 4;
       l->val = 3;
       r->val = 8;
       ll->val = 5;
       lr->val = 7;
       head->left = l;
       head->right = r;
       l->val = 3;
       l->left = ll;
       l->right = lr;
        
       print_preorder(head);  
       cout << endl;
       prefix(head);
       print_preorder(head);
       // no need to worry about memory leaks right now
       return 0;
   }


void print_preorder(shared_ptr<Node> root){
    if (root == nullptr) return;
    cout << root->val << " ";
    print_preorder(root->left);
    print_preorder(root->right);
}

void prefix(shared_ptr<Node> root){
    prefixH(root, 0);
}

void prefixH(shared_ptr<Node> root, int psum){
    if (root == nullptr) return;
    root->val += psum;
    prefixH(root->left, root->val);
    prefixH(root->right, root->val);
}
