#include<iostream>
#include <memory>
#include <algorithm>
using namespace std;


struct Node {    
    int val;    
    shared_ptr<Node> left;    
    shared_ptr<Node> right;      
  };
  
  
shared_ptr<Node> find(shared_ptr<Node> root, int value); 
void findInRange(shared_ptr<Node> root, int k1, int k2);
 
 // Write a recursive function to print the binary tree in 
 // preorder traversal order
 void print_preorder(shared_ptr<Node> root);
 
 
   
   int main(){   
       shared_ptr<Node> head = make_shared<Node>();
       shared_ptr<Node> l = make_shared<Node>();
       shared_ptr<Node> r = make_shared<Node>();
       shared_ptr<Node> ll = make_shared<Node>();
       shared_ptr<Node> lr = make_shared<Node>();
       head->val = 14;
       l->val = 2;
       r->val = 18;
       ll->val = 1;
       lr->val = 3;
       head->left = l;
       head->right = r;
      // l->val = 3;
       l->left = ll;
       l->right = lr;
        
       print_preorder(head);  
       cout << endl;
       shared_ptr<Node> search = find(head, 23);
       if (search == nullptr) cout << "23 not found" << endl;
       
       cout << "Searching for values 23 through 25" << endl;
       findInRange(head, 23, 25);
       cout << "Searching for values 5 through 18" << endl;
       findInRange(head, 5, 18);
       return 0;
   }


void print_preorder(shared_ptr<Node> root){
    if (root == nullptr) return;
    cout << root->val << " ";
    print_preorder(root->left);
    print_preorder(root->right);
}

shared_ptr<Node> find(shared_ptr<Node> root, int v)
{
  if( root == nullptr ) return nullptr;
  if (root->val == v) return root;
  if (v < root->val) {
      return (find(root->left,v));
  } else {
      return (find(root->right,v));
  }
}

void findInRange(shared_ptr<Node> root, int k1, int k2){
    if (root == nullptr) return;
    if (root->val > k1 ) findInRange(root->left, k1, k2);
    if (root->val >= k1 && root->val <= k2) cout << root->val << endl;
    if (root->val < k2 ) findInRange(root->right, k1, k2);
}
