// check_bst.h - implements functions to check that BSTs are correct and valid
//
// MODIFIED Fall 2020 - switched to smart pointers

#ifndef CHECK_BST_H
#define CHECK_BST_H

#include "publicified_bst.h"

#include <gtest/gtest.h>

#include <set>
#include <iostream>
#include <memory>

// forward declarations
template<typename Key, typename Value>
testing::AssertionResult checkValidTraversal(std::shared_ptr<Node<Key, Value>> current);
template<typename Key, typename Value>
testing::AssertionResult checkKeys(BinarySearchTree<Key, Value> const & tree, std::set<Key> const & keySet);
template<typename Key, typename Value>
testing::AssertionResult checkStructureRecursive(std::shared_ptr<Node<Key, Value>> expectedNode, std::shared_ptr<Node<Key, Value>> actualNode);
template<typename Key, typename Value>
testing::AssertionResult checkSameStructure(BinarySearchTree<Key, Value> & expected, BinarySearchTree<Key, Value> & actual);


/* Verifies that tree is a valid binary tree.
   That is, each node is greater than its
   predecessor in the tree structure, and
   the parent->child and child->parent pointers
   of all nodes match up.

   This function should **gracefully**
   deal with errors in the tree structure, and
   print a helpful error message telling the user
   what is wring when it finds one.

   Return value is true if the tree is valid, and false if it is not.
*/
template<typename Key, typename Value>
testing::AssertionResult isValidTree(BinarySearchTree<Key, Value> & tree)
{
	// empty trees are always valid
	if(tree.root_ == nullptr)
	{
		return testing::AssertionSuccess();
	}
	else
	{
		return checkValidTraversal(tree.root_);
	}
}

// author credit: Chris Hailey
template<typename Key, typename Value>
testing::AssertionResult checkValidTraversal(std::shared_ptr<Node<Key, Value>> current)
{
		if(current->getLeft()!=NULL){
			if(!(current->getLeft()->getKey() < current->getKey())){
				return testing::AssertionFailure() << "The left child of "<<current->getKey()<<" is "<<current->getLeft()->getKey()<<" which is larger than its parent and not allowed for a left child in a BST";
			}
			if(current->getLeft()->getParent()!=current){
				return testing::AssertionFailure() <<"The left child of "<<current->getKey()<<" does not have its parent set correctly";
			}
			std::shared_ptr<Node<Key, Value>> predecessor = current->getLeft();
			while(predecessor->getRight()!=NULL){
				predecessor = predecessor->getRight();
			}
			if(!(predecessor->getKey()< current->getKey())){
				return testing::AssertionFailure() << "The predecessor of "<<current->getKey()<<" is "<< predecessor->getKey()<<" which is larger than what it is predecessing";
			}

			testing::AssertionResult traversalResult = checkValidTraversal(current->getLeft());

			if(!traversalResult){
				return traversalResult;
			}
		}
		if(current->getRight()!=NULL)
		{
			if(!(current->getKey() < current->getRight()->getKey()))
			{
				return testing::AssertionFailure() << "The right child of "<<current->getKey()<<" is "<<current->getRight()->getKey()<<" which is less than its parent and not allowed for a right child";
			}
			if(current->getRight()->getParent()!=current)
			{
				return testing::AssertionFailure() << "the right child of "<<current->getKey()<<" does not have its parent set correctly";
			}

			testing::AssertionResult traversalResult = checkValidTraversal(current->getRight());

			if(!traversalResult)
			{
				return traversalResult;
			}
		}

		return testing::AssertionSuccess();
}


/* Verifies that the given tree contains the
   keys given by the key set, in their natural order.

   The passed tree is guaranteed to be valid according to
   isValidTree(), so an iterator can be used for this function.

   Returns true on success, false on failure.
*/
template<typename Key, typename Value>
testing::AssertionResult checkKeys(BinarySearchTree<Key, Value> const & tree, std::set<Key> const & keySet)
{
  for (typename std::set<Key>::iterator it = keySet.begin(); it != keySet.end(); ++it)
  {
      typename BinarySearchTree<Key, Value>::iterator keyToFind = tree.find(*it);
      if (keyToFind == tree.end())
      {
	      return testing::AssertionFailure() << "Tree should contain key " << *it << ", but it was not found using find()!";
      }
  }
  return testing::AssertionSuccess();
}

// recursive helper function for below function
template<typename Key, typename Value>
testing::AssertionResult checkStructureRecursive(std::shared_ptr<Node<Key, Value>> expectedNode, std::shared_ptr<Node<Key, Value>> actualNode)
{

	// compare items
	if(expectedNode->getItem().first != actualNode->getItem().first)
	{
		return testing::AssertionFailure() << "Node mismatch against expected tree!  Expected (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << "), got ("
				<< actualNode->getItem().first << ", " << actualNode->getItem().second << ")";
	}

	// note; we don't compare the heights since those are verified as right by verifyBST()

	// compare existance/nonexistance of children
	if(expectedNode->getRight() == nullptr)
	{
		if(actualNode->getRight() != nullptr)
		{
			return testing::AssertionFailure() << "Node mismatch against expected tree!  Node (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << ") is not supposed to have a right child, but instead it has ("
				<< actualNode->getRight()->getItem().first << ", " << actualNode->getRight()->getItem().second << ")"<< std::endl;
		}
	}
	else
	{
		if(actualNode->getRight() == nullptr)
		{
			return testing::AssertionFailure() << "Node mismatch against expected tree!  Node (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << ") is supposed to have a right child, ("
				<< expectedNode->getRight()->getItem().first << ", " << actualNode->getRight()->getItem().second << "), but instead it has no right child"<< std::endl;
		}
		else
		{
			// recurse to right child
			testing::AssertionResult rightChildStructureResult = checkStructureRecursive(expectedNode->getRight(), actualNode->getRight());

			if(!rightChildStructureResult)
			{
				return rightChildStructureResult;
			}
		}
	}

	if(expectedNode->getLeft() == nullptr)
	{
		if(actualNode->getLeft() != nullptr)
		{
			return testing::AssertionFailure() << "Node mismatch against expected tree! Node (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << ") is not supposed to have a left child, but instead it has ("
				<< actualNode->getLeft()->getItem().first << ", " << actualNode->getLeft()->getItem().second << ")";
		}
	}
	else
	{
		if(actualNode->getLeft() == nullptr)
		{
			return testing::AssertionFailure() << "Node mismatch against expected tree! Node (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << ") is supposed to have a left child, ("
				<< expectedNode->getLeft()->getItem().first << ", " << actualNode->getLeft()->getItem().second << "), but instead it has no left child";
		}
		else
		{
			// recurse to left child
			testing::AssertionResult leftChildStructureResult = checkStructureRecursive(expectedNode->getLeft(), actualNode->getLeft());

			if(!leftChildStructureResult)
			{
				return leftChildStructureResult;
			}
		}
	}

	// passed the gauntlet!
	return testing::AssertionSuccess();
}

/* Returns true iff two BSTs contain the same data AND 
   have the same node structure.  As in, these would be
   equal:
              [20]                 [20]
              /  \        and      /  \
           [08]  [37]           [08]  [37]

   but these would be unequal:

              [20]                 [37]
              /  \        and      /  
           [08]  [37]           [20]  
                                /
                             [08]

   They must contain the same keys, and are not
   allowed to have different internal node structures.

   The passed trees are guaranteed to be valid according to
   isValidTree(), so iterators can be used for this function.

   Prints error messages where differences are found between trees.
*/
template<typename Key, typename Value>
testing::AssertionResult checkSameStructure(BinarySearchTree<Key, Value> & expected, BinarySearchTree<Key, Value> & actual)
{
	if(expected.root_ == nullptr)
	{
		if(actual.root_ != nullptr)
		{
			return testing::AssertionFailure() << "Node mismatch against expected tree! Tree is supposed to be empty, but instead it has root (" << actual.root_->getItem().first << ", " << actual.root_->getItem().second << ")";
		}
	}
	else
	{
		if(actual.root_ == nullptr)
		{
			return testing::AssertionFailure() << "Node mismatch against expected tree! Tree is supposed to have root (" << expected.root_->getItem().first << ", " << expected.root_->getItem().second << "), but instead it is empty!";
		}
		else
		{
			// recursively compare rest of tree
			testing::AssertionResult recursiveResult = checkStructureRecursive(expected.root_, actual.root_);

			if(!recursiveResult)
			{
				return recursiveResult;
			}
		}
	}

	return testing::AssertionSuccess();
}

// recursively checks that a subtree is balanced, and returns the height of the passed node.
// note: if false is returned, the height will not be correct, since it isn't needed in higher-up calls
template<typename Key, typename Value>
std::pair<int, bool> verifyBalanceRecursive(BinarySearchTree<Key, Value> & tree, std::shared_ptr<Node<Key, Value>> currNode)
{
	if (currNode == nullptr)
	{
		return std::make_pair(0, true);
	}

	std::pair<int, bool> balanceResultsLeft = verifyBalanceRecursive(tree, currNode->getLeft());
	if(!balanceResultsLeft.second)
	{
		return std::make_pair(0, false);
	}

	std::pair<int, bool> balanceResultsRight = verifyBalanceRecursive(tree, currNode->getRight());
	if(!balanceResultsRight.second)
	{
		return std::make_pair(0, false);
	}

	if(std::abs(balanceResultsLeft.first - balanceResultsRight.first) < 2)
	{
		// this subtree is in balance

		int thisNodeHeight = std::max(balanceResultsLeft.first, balanceResultsRight.first) + 1;

		return std::make_pair(thisNodeHeight, true);
	}
	else
	{
		// this subtree is out of balance
		return std::make_pair(0, false);
	}
}


/*
 * Verifies that iff all subtrees are balanced, isBalanced() returned the correct result.
 */
template<typename Key, typename Value>
testing::AssertionResult checkBalance(BinarySearchTree<Key, Value> & tree)
{
	if(tree.root_ == nullptr)
	{
		if(!tree.isBalanced())
		{
			return testing::AssertionFailure() << "Tree is empty, but isBalanced() returned false!";
		}
	}
	else
	{
		bool isActuallyBalanced = verifyBalanceRecursive(tree, tree.root_).second;

		if(isActuallyBalanced)
		{
			if(!tree.isBalanced())
			{
				return testing::AssertionFailure() << "Tree is balanced, but isBalanced() returned false!";
			}
		}
		else
		{
			if(tree.isBalanced())
			{
				return testing::AssertionFailure() << "Tree is not balanced, but isBalanced() returned true!";
			}
		}
	}

	return testing::AssertionSuccess();
}

/* Top-level testing function.
   Makes sure that the passed tree is valid and consistent,
   and prints an error if it is not.

   Then, it checks the values against the provided value set, and
   prints an error if there is a mismatch.

   Returns true iff there are no errors.
*/ 

template<typename Key, typename Value>
testing::AssertionResult verifyBST(BinarySearchTree<Key, Value> & tree, std::set<Key> const & keySet)
{
	testing::AssertionResult validResult = isValidTree(tree);

	if(!validResult)
	{
		std::cerr << ">> Binary tree structure is broken!" << std::endl;
		return validResult;
	}

	testing::AssertionResult keysResult = checkKeys(tree, keySet);

	if(!keysResult)
	{
		std::cerr << ">> Key mismatch error!" << std::endl;
		std::cerr << ">> Tree was:" << std::endl;
		tree.print();
		return keysResult;
	}

	return testing::AssertionSuccess();
}

// similar to above, but only checks validity, not keys.
template<typename Key, typename Value>
testing::AssertionResult verifyBST(BinarySearchTree<Key, Value> & tree)
{
	testing::AssertionResult validResult = isValidTree(tree);

	if(!validResult)
	{
		std::cerr << ">> Binary tree structure is broken!" << std::endl;
		std::cerr << ">> Tree was:" << std::endl;
		tree.print();
		return validResult;
	}

	return testing::AssertionSuccess();

}

#endif
