#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include <memory>
#include "bst.h"


struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, std::shared_ptr<AVLNode<Key, Value>> parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    std::shared_ptr<AVLNode<Key, Value>> getParent_AVL() const;
    std::shared_ptr<AVLNode<Key, Value>> getLeft_AVL() const;
    std::shared_ptr<AVLNode<Key, Value>> getRight_AVL() const;

protected:
    // to store the balance of a given node
    char balance_;
};


    // -------------------------------------------------
    // Begin implementations for the AVLNode class.
    // -------------------------------------------------



// An explicit constructor to initialize the elements by calling the base class constructor and setting
// the color to red since every new node will be red when it is first inserted.

template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, std::shared_ptr<AVLNode<Key, Value>> parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

// A destructor which does nothing.
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

// A getter for the balance of a AVLNode.
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

// A setter for the balance of a AVLNode.
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

// Adds diff to the balance of a AVLNode.
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

// A separate getParent_AVL function other than the base class function due to covariant return types
template<class Key, class Value>
std::shared_ptr<AVLNode<Key, Value>> AVLNode<Key, Value>::getParent_AVL() const
{
    return std::static_pointer_cast< AVLNode<Key, Value> >(this->parent_);
}

// Similar getLeft_AVL function
template<class Key, class Value>
std::shared_ptr<AVLNode<Key, Value>> AVLNode<Key, Value>::getLeft_AVL() const
{
    return std::static_pointer_cast< AVLNode<Key, Value> >(this->left_);
}

// Similar getRight_AVL function
template<class Key, class Value>
std::shared_ptr<AVLNode<Key, Value>> AVLNode<Key, Value>::getRight_AVL() const
{
    return std::static_pointer_cast< AVLNode<Key, Value> >(this->right_);
}


// -----------------------------------------------
// End implementations for the AVLNode class.
// -----------------------------------------------


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    
    void rotateLeft(std::shared_ptr<AVLNode<Key, Value>> p, std::shared_ptr<AVLNode<Key, Value>> n); //TODO
    void rotateRight(std::shared_ptr<AVLNode<Key, Value>> p, std::shared_ptr<AVLNode<Key, Value>> n); //TODO

    // Remember, AVL is a self-balancing BST
    // Resultant tree after the insert and remove function should be a balanced tree
    // Make appropriate calls to rotateLeft(...) and rotateRight(...)
    // in insert and remove for balancing the height of the AVLTree
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    // Helper function already provided to you.
    virtual void nodeSwap( std::shared_ptr<AVLNode<Key,Value>> n1, std::shared_ptr<AVLNode<Key,Value>> n2);
    
    // Add helper functions here
    // Consider adding functions like getBalance(...) given a key in the Tree
    // setBalance(...) given a key to a node and balance value, etc
    
    // You may implement a printRootAVL(...) 
    // using the printRoot() function from the BST implementation
};

// Pre condition: p is the parent of n 
// Post condition: p is the left child of n
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft (std::shared_ptr<AVLNode<Key, Value>> p, std::shared_ptr<AVLNode<Key, Value>> n)
{
    // TODO
}

// Pre condition: p is the parent of n 
// Post condition: p is the right child of n
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight (std::shared_ptr<AVLNode<Key, Value>> p, std::shared_ptr<AVLNode<Key, Value>> n)
{
    // TODO
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key) {
    // TODO
}

// Function already completed for you
template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( std::shared_ptr<AVLNode<Key,Value>> n1, std::shared_ptr<AVLNode<Key,Value>> n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

#endif
