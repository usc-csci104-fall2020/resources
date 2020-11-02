#include <check_bst.h>
#include <create_bst.h>

#include <random_generator.h>

#include <gtest/gtest.h>

#include <initializer_list>
#include <set>
#include <utility>

TEST(BST, ConstructionDestruction)
{
	BinarySearchTree<std::string, std::string> testTree;
}

TEST(BSTInsert, JustRoot)
{
	BinarySearchTree<std::string, std::string> testTree;

	testTree.insert(std::make_pair("Hello World", "!!!"));

	EXPECT_TRUE(verifyBST(testTree, std::set<std::string>({"Hello World"})));
}


TEST(BSTInsert, DoubleInsertLeft)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(0, 8));

	EXPECT_TRUE(verifyBST(testTree, std::set<uint16_t>({0, 1})));
}

TEST(BSTInsert, DoubleInsertRight)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(2, 8));

	EXPECT_TRUE(verifyBST(testTree, std::set<uint16_t>({1, 2})));
}

TEST(BSTInsert, InsertZigZigLeft)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(2, 9));
	testTree.insert(std::make_pair(1, 8));
	testTree.insert(std::make_pair(0, 159));

	EXPECT_TRUE(verifyBST(testTree, std::set<uint16_t>({0, 1, 2})));
}

TEST(BSTInsert, InsertZigZigRight)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(0, 9));
	testTree.insert(std::make_pair(1, 8));
	testTree.insert(std::make_pair(2, 159));

	EXPECT_TRUE(verifyBST(testTree, std::set<uint16_t>({0, 1, 2})));
}

TEST(BSTInsert, InsertZigZagLeft)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(2, 9));
	testTree.insert(std::make_pair(0, 8));
	testTree.insert(std::make_pair(1, 159));

	EXPECT_TRUE(verifyBST(testTree, std::set<uint16_t>({0, 1, 2})));
}

TEST(BSTInsert, InsertZigZagRight)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(0, 9));
	testTree.insert(std::make_pair(2, 8));
	testTree.insert(std::make_pair(1, 159));

	EXPECT_TRUE(verifyBST(testTree, std::set<uint16_t>({0, 1, 2})));
}

TEST(BSTInsert, 7Elements)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));
	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(10, 0x5a));
	testTree.insert(std::make_pair(15, 0xb));
	testTree.insert(std::make_pair(2, 4));
	testTree.insert(std::make_pair(4, 159));

	EXPECT_TRUE(verifyBST(testTree, std::set<uint16_t>({5, 3, 1, 10, 15, 2, 4})));
}

TEST(BSTClear, Clear)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));

	testTree.clear();

	EXPECT_TRUE(verifyBST(testTree, std::set<uint16_t>({})));
}

TEST(BSTFind, InvalidFind)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));

	EXPECT_EQ(testTree.find(7), testTree.end());
}


TEST(BSTInsert, Duplicates)
{
	BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));
	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(3, 0x5a));
	testTree.insert(std::make_pair(15, 0xb));
	testTree.insert(std::make_pair(1, 4));
	testTree.insert(std::make_pair(3, 159));

	EXPECT_TRUE(verifyBST(testTree, std::set<uint16_t>({5, 3, 1, 15})));
}



TEST(BSTInsert, BasicRandom)
{
	BinarySearchTree<int, int> testTree;

	RandomSeed randomSeed1 = 1405, randomSeed2 = 1;

	std::set<int> randomData = makeRandomIntSet(10, randomSeed1);
	fillTree(testTree, randomData, randomSeed2);
	EXPECT_TRUE(verifyBST(testTree, randomData));

}

TEST(BSTInsert, Random50x30ele)
{
	const RandomSeed masterSeed = 343;
	const size_t numElements = 30;
	const size_t numTrials = 50;

	BinarySearchTree<int, int> testTree;

	// generate twice as many seeds as trials because we need 2 for each trial
	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials * 2, masterSeed);

	for(size_t counter = 0; counter < numTrials*2; counter+= 2)
	{
		std::set<int> randomData = makeRandomIntSet(numElements, seeds.at(counter));
		fillTree(testTree, randomData, seeds.at(counter + 1));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		testTree.clear();
	}


}

TEST(BSTInsert, Random3x1000ele)
{
	const RandomSeed masterSeed = 6565;
	const size_t numElements = 1000;
	const size_t numTrials = 3;

	BinarySearchTree<int, int> testTree;

	// generate twice as many seeds as trials because we need 2 for each trial
	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials * 2, masterSeed);

	for(size_t counter = 0; counter < numTrials*2; counter+= 2)
	{
		std::set<int> randomData = makeRandomIntSet(numElements, seeds.at(counter));
		fillTree(testTree, randomData, seeds.at(counter + 1));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		testTree.clear();
	}


}
