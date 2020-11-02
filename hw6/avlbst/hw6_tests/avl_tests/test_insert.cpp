#include "check_avl.h"
#include <create_bst.h>

#include <random_generator.h>

#include <gtest/gtest.h>

#include <initializer_list>
#include <set>
#include <utility>

TEST(AVLBST, ConstructionDestruction)
{
	AVLTree<std::string, std::string> testTree;
}

TEST(AVLInsert, OneNode)
{
	AVLTree<std::string, std::string> testTree;

	testTree.insert(std::make_pair("Hello World", "!!!"));

	EXPECT_TRUE(verifyAVL(testTree, std::set<std::string>({"Hello World"})));
}


TEST(AVLInsert, DoubleInsertLeft)
{
	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(0, 8));

	EXPECT_TRUE(verifyAVL(testTree, std::set<uint16_t>({0, 1})));
}

TEST(AVLInsert, DoubleInsertRight)
{
	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(2, 8));

	EXPECT_TRUE(verifyAVL(testTree, std::set<uint16_t>({1, 2})));
}

TEST(AVLInsert, InsertZigZigLeft)
{
	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(2, 9));
	testTree.insert(std::make_pair(1, 8));
	testTree.insert(std::make_pair(0, 159));

	EXPECT_TRUE(verifyAVL(testTree, std::set<uint16_t>({0, 1, 2})));
}

TEST(AVLInsert, InsertZigZigRight)
{
	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(0, 9));
	testTree.insert(std::make_pair(1, 8));
	testTree.insert(std::make_pair(2, 159));

	EXPECT_TRUE(verifyAVL(testTree, std::set<uint16_t>({0, 1, 2})));
}

TEST(AVLInsert, InsertZigZagLeft)
{
	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(2, 9));
	testTree.insert(std::make_pair(0, 8));
	testTree.insert(std::make_pair(1, 159));

	EXPECT_TRUE(verifyAVL(testTree, std::set<uint16_t>({0, 1, 2})));
}

TEST(AVLInsert, InsertZigZagRight)
{
	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(0, 9));
	testTree.insert(std::make_pair(2, 8));
	testTree.insert(std::make_pair(1, 159));

	EXPECT_TRUE(verifyAVL(testTree, std::set<uint16_t>({0, 1, 2})));
}

TEST(AVLInsert, 7Elements)
{
	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));
	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(10, 0x5a));
	testTree.insert(std::make_pair(15, 0xb));
	testTree.insert(std::make_pair(2, 4));
	testTree.insert(std::make_pair(4, 159));

	EXPECT_TRUE(verifyAVL(testTree, std::set<uint16_t>({5, 3, 1, 10, 15, 2, 4})));
}

TEST(AVLClear, Clear)
{
	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));

	testTree.clear();

	EXPECT_TRUE(verifyAVL(testTree, std::set<uint16_t>({})));
}

TEST(AVLInsert, Duplicates)
{
	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));
	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(3, 0x5a));
	testTree.insert(std::make_pair(15, 0xb));
	testTree.insert(std::make_pair(1, 4));
	testTree.insert(std::make_pair(3, 159));

	EXPECT_TRUE(verifyAVL(testTree, std::set<uint16_t>({5, 3, 1, 15})));
}



TEST(AVLInsert, Random50x30ele)
{
	const RandomSeed masterSeed = 6768;
	const size_t numElements = 30;
	const size_t numTrials = 50;

	AVLTree<int, int> testTree;

	// generate twice as many seeds as trials because we need 2 for each trial
	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials * 2, masterSeed);

	for(size_t counter = 0; counter < numTrials*2; counter+= 2)
	{
		// note: we do 30 random numbers because that creates an almost-full, but not overfull, graph on printBST
		std::set<int> randomData = makeRandomIntSet(numElements, seeds.at(counter));
		fillTree(testTree, randomData, seeds.at(counter + 1));
		EXPECT_TRUE(verifyAVL(testTree, randomData));

		testTree.clear();
	}


}

TEST(AVLInsert, Random3x1000ele)
{
	const RandomSeed masterSeed = 4999;
	const size_t numElements = 1000;
	const size_t numTrials = 3;

	AVLTree<int, int> testTree;

	// generate twice as many seeds as trials because we need 2 for each trial
	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials * 2, masterSeed);

	for(size_t counter = 0; counter < numTrials*2; counter+= 2)
	{
		// note: we do 30 random numbers because that creates an almost-full, but not overfull, graph on printBST
		std::set<int> randomData = makeRandomIntSet(numElements, seeds.at(counter));
		fillTree(testTree, randomData, seeds.at(counter + 1));
		EXPECT_TRUE(verifyAVL(testTree, randomData));

		testTree.clear();
	}


}
