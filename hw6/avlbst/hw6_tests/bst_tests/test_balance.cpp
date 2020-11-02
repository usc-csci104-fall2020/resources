//
// CS104 BST Balance Tests
//

#include <check_bst.h>
#include <create_bst.h>

#include <random_generator.h>

#include <gtest/gtest.h>


TEST(BSTBalance, EmptyTree)
{
	BinarySearchTree<std::string, std::string> testTree;
	EXPECT_TRUE(checkBalance(testTree));
}

TEST(BSTBalance, OneNode)
{
	BinarySearchTree<std::string, std::string> testTree;

	EXPECT_TRUE(checkBalance(testTree));
}


TEST(BSTBalance, 3Nodes_Unbalanced)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));
	
	EXPECT_TRUE(checkBalance(testTree));
}

TEST(BSTBalance, 3Nodes_Balanced)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(3, 9));
	testTree.insert(std::make_pair(1, 8));
	testTree.insert(std::make_pair(5, 159));

	EXPECT_TRUE(checkBalance(testTree));
}

TEST(BSTBalance, UnbalancedSubtree)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));
	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(10, 0x5a));

	testTree.insert(std::make_pair(15, 0xb));
	testTree.insert(std::make_pair(4, 4));
	testTree.insert(std::make_pair(17, 159));

	testTree.print();
	EXPECT_TRUE(checkBalance(testTree));
}

TEST(BSTBalance, Random50x30ele)
{
	const RandomSeed masterSeed = 343;
	const size_t numElements = 30;
	const size_t numTrials = 50;

	BinarySearchTree<int, int> testTree;

	// generate twice as many seeds as we need because we need 2 for each trial
	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials * 2, masterSeed);

	for(size_t counter = 0; counter < numTrials*2; counter+= 2)
	{
		// note: we do 30 random numbers because that creates an almost-full, but not overfull, graph on printBST
		std::set<int> randomData = makeRandomIntSet(numElements, seeds.at(counter));
		fillTree(testTree, randomData, seeds.at(counter + 1));

		EXPECT_TRUE(checkBalance(testTree));

		testTree.clear();
	}


}