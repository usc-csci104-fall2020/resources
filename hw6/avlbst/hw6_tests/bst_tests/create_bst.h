// Header that implements functions for creating BSTs.

#include "publicified_bst.h"

#include <random_generator.h>

#include <set>
#include <limits>
#include <random>
#include <algorithm>

#ifndef CREATE_BST_H
#define CREATE_BST_H


/* Fills the given bst with one node for each item in the set.
   The key and value of the node are both set to the item's value.

   This way, keys in the tree will be ordered the same way
   they are in the set, and it will be easy to check that
   the value corresponding to a key was correctly stored.

   So that the tree will be roughly balanced, values will
   be inserted in *random* order with the given seed.

*/
template<typename Key>
void fillTree(BinarySearchTree<Key, Key> & tree, std::set<Key> const & dataSet, RandomSeed randomSeed)
{
	// set up random number generator
	std::mt19937 randEngine;
	randEngine.seed(randomSeed);

	std::vector<Key> setElements(dataSet.begin(), dataSet.end());
	std::shuffle(setElements.begin(), setElements.end(), randEngine);

	for(size_t index = 0; index < setElements.size(); ++index)
	{
		tree.insert(std::make_pair(setElements[index], setElements[index]));
	}
}

#endif
