//
// Auto-checker for AVL trees
//
// MODIFIED Fall 2020 - switched to smart pointers

#ifndef CS104_HW7_TEST_SUITE_CHECK_AVL_H
#define CS104_HW7_TEST_SUITE_CHECK_AVL_H

#include "publicified_avlbst.h"

#include <check_bst.h>

#include <algorithm>

template<typename Key, typename Value>
testing::AssertionResult checkHeightsHelper(AVLTree<Key, Value> & tree, std::shared_ptr<AVLNode<Key, Value>> currRoot);

/* Verifies that, for a given tree, each node's height value
   is correct.  Walks down to each leaf node, then back up
   to to verify that each higher node has the correct height.

   This function may only be called on a tree if that tree is
   valid according to isValidTree(), so it does not have
   to check for tree consistency.

   Returns true on success, false on failure.
*/
template<typename Key, typename Value>
bool checkHeights(AVLTree<Key, Value> & tree)
{
	return checkHeightsHelper(tree, std::dynamic_pointer_cast<AVLNode<Key, Value>>(tree.root_));
}

// recursively checks that the height of this subtree is correct
template<typename Key, typename Value>
testing::AssertionResult checkHeightsHelper(AVLTree<Key, Value> & tree, std::shared_ptr<AVLNode<Key, Value>> currRoot)
{
	if(currRoot == nullptr)
	{
		//reached bottom of this subtree
		return testing::AssertionSuccess();
	}

	// verify heights of each child node
	testing::AssertionResult leftResult = checkHeightsHelper(tree, currRoot->getLeft());
	if(!leftResult)
	{
		return leftResult;
	}

	testing::AssertionResult rightResult = checkHeightsHelper(tree, currRoot->getRight());
	if(!rightResult)
	{
		return rightResult;
	}

	// now, assuming child heights are correct, verify this node's height
	int leftHeight = currRoot->getLeft() == nullptr ? 0 : currRoot->getLeft()->getHeight();
	int rightHeight = currRoot->getRight() == nullptr ? 0 : currRoot->getRight()->getHeight();

	int thisHeight = std::max(leftHeight, rightHeight);

	if(thisHeight == currRoot->getHeight())
	{
		return testing::AssertionSuccess();
	}
	else
	{
		return testing::AssertionFailure() << "Height of node " << currRoot->getKey() << " is incorrect! Was " << currRoot->getHeight() << ", should have been " << thisHeight;
	}


}

template<typename Key, typename Value>
std::pair<int, testing::AssertionResult> verifyAVLBalanceRecursive(AVLTree<Key, Value> & tree, std::shared_ptr<AVLNode<Key, Value>> currNode);

/**
 * Verifies that an AVL tree is in balance, and returns an assertion failure if any subtree is not.
 * @tparam Key
 * @tparam Value
 * @param tree
 * @return
 */
template<typename Key, typename Value>
testing::AssertionResult checkAVLBalance(AVLTree<Key, Value> & tree)
{
	return verifyAVLBalanceRecursive(tree, std::dynamic_pointer_cast<AVLNode<Key, Value>>(tree.root_)).second;
}

// recursively checks that a subtree is balanced, and returns the height of the passed node.
// note: if a failure is returned, the height will not be correct, since it isn't needed in higher-up calls.
// This is similar to verifyBalanceRecursive(), but returns an error message if any subtree is out of balance showing where the issue is.
template<typename Key, typename Value>
std::pair<int, testing::AssertionResult> verifyAVLBalanceRecursive(AVLTree<Key, Value> & tree, std::shared_ptr<AVLNode<Key, Value>> currNode)
{
	if (currNode == nullptr)
	{
		return std::make_pair(0, testing::AssertionSuccess());
	}

	std::pair<int, testing::AssertionResult> balanceResultsLeft = verifyAVLBalanceRecursive(tree, std::dynamic_pointer_cast<AVLNode<Key, Value>>(currNode->getLeft()));
	if(!balanceResultsLeft.second)
	{
		return std::make_pair(0, balanceResultsLeft.second);
	}

	std::pair<int, testing::AssertionResult> balanceResultsRight = verifyAVLBalanceRecursive(tree, std::dynamic_pointer_cast<AVLNode<Key, Value>>(currNode->getRight()));
	if(!balanceResultsRight.second)
	{
		return std::make_pair(0, balanceResultsRight.second);
	}

	if(std::abs(balanceResultsLeft.first - balanceResultsRight.first) < 2)
	{
		// this subtree is in balance

		int thisNodeHeight = std::max(balanceResultsLeft.first, balanceResultsRight.first) + 1;

		return std::make_pair(thisNodeHeight, testing::AssertionSuccess());
	}
	else
	{
		// this subtree is out of balance
		return std::make_pair(0, (testing::AssertionFailure() << "AVL balance error: subtree rooted at " << currNode->getKey() << " is out of balance!  Left child has height "
						   << balanceResultsLeft.first << ", and right child has height " << balanceResultsRight.first << "."));
	}
}



/* Top-level testing function.
   Makes sure that the passed tree is valid and consistent,
   and prints an error if it is not.

   Then, it checks the values against the provided value set, and
   prints an error if there is a mismatch.

   Returns true iff there are no errors.
*/

template<typename Key, typename Value>
testing::AssertionResult verifyAVL(AVLTree<Key, Value> & tree, std::set<Key> const & keySet)
{
	// first verify it as a BST
	testing::AssertionResult bstResult = verifyBST(tree, keySet);

	if(!bstResult)
	{
		return bstResult;
	}

	testing::AssertionResult balanceResult = checkAVLBalance(tree);
	if(!balanceResult)
	{
		std::cout << "Balance error!" << std::endl;
		std::cout << "Tree was: " << std::endl;
		tree.print();
	}

	return balanceResult;
}

// similar to above, but only checks validity, not keys.
template<typename Key, typename Value>
testing::AssertionResult verifyAVL(AVLTree<Key, Value> & tree)
{
	// first verify it as a BST
	testing::AssertionResult bstResult = verifyBST(tree);

	if(!bstResult)
	{
		return bstResult;
	}

	testing::AssertionResult balanceResult = checkAVLBalance(tree);
	if(!balanceResult)
	{
		std::cout << "Balance error!" << std::endl;
		std::cout << "Tree was: " << std::endl;
		tree.print();
	}

	return balanceResult;

}


#endif //CS104_HW7_TEST_SUITE_CHECK_AVL_H
