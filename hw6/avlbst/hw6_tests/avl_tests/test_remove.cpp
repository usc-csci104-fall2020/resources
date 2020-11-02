#include "check_avl.h"
#include <create_bst.h>

#include <gtest/gtest.h>

#include <initializer_list>
#include <utility>

TEST(AVLRemove, EmptyTree)
{
	AVLTree<std::string, std::string> testTree;

	testTree.remove("supercalifragilisticexpialodocious");

	EXPECT_TRUE(verifyAVL(testTree, {}));
}

TEST(AVLRemove, NodeMismatch)
{
	AVLTree<std::string, std::string> testTree;

	testTree.insert(std::make_pair("blah", "blah"));
	testTree.insert(std::make_pair("bluh", "blug"));

	testTree.remove("supercalifragilisticexpialodocious");

	EXPECT_TRUE(verifyAVL(testTree, {"blah", "bluh"}));
}


TEST(AVLRemove, SingleRemove)
{
	AVLTree<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.remove(1);

	EXPECT_TRUE(verifyAVL(bst, {}));
}

TEST(AVLRemove, RightChildRemove)
{
	AVLTree<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	bst.remove(1);

	EXPECT_TRUE(verifyAVL(bst, {2, 3}));
}

TEST(AVLRemove, LeftChildRemove)
{
	AVLTree<int, double> bst;
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.remove(3);

	EXPECT_TRUE(verifyAVL(bst, {1, 2}));
}

TEST(AVLRemove, TwoChildrenRemove_3Node)
{
	AVLTree<int, double> bst;
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	bst.remove(2);

	EXPECT_TRUE(verifyAVL(bst, {1, 3}));

	// predecessor, 1, should be promoted
	ASSERT_NE(nullptr, bst.root_);
	EXPECT_EQ(1, bst.root_->getKey());

	ASSERT_NE(nullptr, bst.root_->getRight());
	EXPECT_EQ(3, bst.root_->getRight()->getKey());

	ASSERT_EQ(nullptr, bst.root_->getLeft());
}


TEST(AVLRemove, TwoChildrenRemove_4Node)
{
	AVLTree<int, double> bst;
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(6, 1.0));
	bst.insert(std::make_pair(4, 1.0));

	bst.remove(5);

	EXPECT_TRUE(verifyAVL(bst, {2, 6, 4}));

	// predecessor, 4, should be promoted
	ASSERT_NE(nullptr, bst.root_);
	EXPECT_EQ(4, bst.root_->getKey());

	ASSERT_NE(nullptr, bst.root_->getRight());
	EXPECT_EQ(6, bst.root_->getRight()->getKey());

	ASSERT_NE(nullptr, bst.root_->getLeft());
	EXPECT_EQ(2, bst.root_->getLeft()->getKey());
}

TEST(AVLRemove, Random50x30ele)
{
	const RandomSeed masterSeed = 1778;
	const size_t numElements = 30;
	const size_t numTrials = 50;

	AVLTree<int, int> testTree;

	// generate 3x as many seeds as trials because we need 3 for each trial
	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials * 3, masterSeed);

	for(size_t counter = 0; counter < numTrials*3; counter+= 3)
	{

		// create tree of random data
		std::set<int> randomData = makeRandomIntSet(numElements, seeds.at(counter));
		fillTree(testTree, randomData, seeds.at(counter + 1));

		ASSERT_TRUE(verifyAVL(testTree, randomData));

		// now remove elements at random
		std::vector<int> randomDataVector(randomData.begin(), randomData.end());
		std::default_random_engine shuffleRandEngine;
		shuffleRandEngine.seed(seeds.at(counter + 2));
		std::shuffle(randomDataVector.begin(), randomDataVector.end(), shuffleRandEngine);

		for(size_t elementIndex = 0; elementIndex < randomDataVector.size(); ++elementIndex)
		{
			testTree.remove(randomDataVector[elementIndex]);
			randomData.erase(randomData.find(randomDataVector[elementIndex]));

			ASSERT_TRUE(verifyAVL(testTree, randomData));

		}
	}


}

// extensive combined insert-remove test
// author credit: Shreya Havaldar
TEST(AVLStress, InsertRemove)
{
	AVLTree<int, std::string> b, c, d;
	std::pair<int, std::string> item5(5, "five");
	std::pair<int, std::string> item3(3, "three");
	std::pair<int, std::string> item7(7, "seven");
	std::pair<int, std::string> item4(4, "four");
	std::pair<int, std::string> item6(6, "six");
	std::pair<int, std::string> item9(9, "nine");
	std::pair<int, std::string> item10(10, "ten");
	std::pair<int, std::string> item2(2, "two");
	std::pair<int, std::string> item8(8, "eight");
	std::pair<int, std::string> item13(13, "thirteen");
	std::pair<int, std::string> item11(11, "eleven");
	std::pair<int, std::string> item12(12, "twelve");
	std::pair<int, std::string> item15(15, "fifteen");
	std::pair<int, std::string> item14(14, "fourteen");
	std::pair<int, std::string> item16(16, "sixteen");
	std::pair<int, std::string> item17(17, "seventeen");


	b.insert(item5);
	ASSERT_TRUE(verifyAVL(b, {item5.first}));

	b.remove(7);
	ASSERT_TRUE(verifyAVL(b, {item5.first}));

	b.remove(5);
	ASSERT_TRUE(verifyAVL(b, {}));

	b.insert(item5);
	b.insert(item3);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first}));

	b.remove(5);
	ASSERT_TRUE(verifyAVL(b, {item3.first}));

	b.remove(3);
	ASSERT_TRUE(verifyAVL(b, {}));


	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first}));

	b.remove(5);
	ASSERT_TRUE(verifyAVL(b, {item3.first, item7.first}));

	b.remove(7);
	ASSERT_TRUE(verifyAVL(b, {item3.first}));

	b.remove(3);
	ASSERT_TRUE(verifyAVL(b, {}));

	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first}));

	b.remove(5);
	ASSERT_TRUE(verifyAVL(b, {item3.first, item7.first, item4.first}));

	b.clear();
	ASSERT_TRUE(verifyAVL(b, {}));

	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	b.insert(item6);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first, item6.first}));

	b.remove(6);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first}));

	b.remove(4);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first}));

	b.clear();
	ASSERT_TRUE(verifyAVL(b, {}));

	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	b.insert(item6);
	b.insert(item9);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first}));

	b.remove(5);
	ASSERT_TRUE(verifyAVL(b, {item3.first, item7.first, item4.first, item6.first, item9.first}));

	b.remove(7);
	ASSERT_TRUE(verifyAVL(b, {item3.first, item4.first, item6.first, item9.first}));

	b.remove(6);
	ASSERT_TRUE(verifyAVL(b, {item3.first, item4.first, item9.first}));

	b.clear();
	ASSERT_TRUE(verifyAVL(b, {}));

	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	b.insert(item6);
	b.insert(item9);
	b.insert(item10);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first}));

	b.remove(5);
	ASSERT_TRUE(verifyAVL(b, {item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first}));

	b.remove(9);
	ASSERT_TRUE(verifyAVL(b, {item3.first, item7.first, item4.first, item6.first, item10.first}));

	b.remove(3);
	ASSERT_TRUE(verifyAVL(b, {item7.first, item4.first, item6.first, item10.first}));

	b.remove(7);
	ASSERT_TRUE(verifyAVL(b, {item4.first, item6.first, item10.first}));

	b.remove(4);
	ASSERT_TRUE(verifyAVL(b, {item6.first, item10.first}));

	b.remove(10);
	ASSERT_TRUE(verifyAVL(b, {item6.first}));

	b.remove(10);
	ASSERT_TRUE(verifyAVL(b, {item6.first}));

	b.remove(6);
	ASSERT_TRUE(verifyAVL(b, {}));

	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	b.insert(item6);
	b.insert(item9);
	b.insert(item10);
	b.insert(item2);
	b.insert(item8);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first, item2.first, item8.first}));

	b.insert(item13);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first, item2.first, item8.first, item13.first}));

	b.insert(item12);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first, item2.first, item8.first, item13.first, item12.first}));

	b.insert(item11);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first, item2.first, item8.first, item13.first,
	                          item12.first, item11.first}));

	b.remove(13);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first, item2.first, item8.first,
	                          item12.first, item11.first}));

	b.remove(12);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first, item2.first, item8.first, item11.first}));

	b.remove(10);
	b.remove(13);
	b.remove(7);
	b.remove(8);
	b.remove(7);
	ASSERT_TRUE(verifyAVL(b, {item5.first, item3.first, item4.first, item6.first,
	                          item9.first, item2.first, item11.first}));


	d.insert(item10);
	d.insert(item3);
	d.insert(item2);
	d.insert(item15);
	d.insert(item12);
	d.insert(item11);
	d.insert(item14);
	d.insert(item13);
	d.insert(item16);
	d.insert(item17);

	ASSERT_TRUE(verifyAVL(d, {item10.first, item3.first, item2.first, item15.first, item12.first,
	                          item11.first, item14.first, item13.first, item16.first,
	                          item17.first}));

	d.remove(15);

	ASSERT_TRUE(verifyAVL(d, {item10.first, item3.first, item2.first, item12.first,
	                          item11.first, item14.first, item13.first, item16.first,
	                          item17.first}));

	d.remove(10);
	ASSERT_TRUE(verifyAVL(d, {item3.first, item2.first, item12.first,
	                          item11.first, item14.first, item13.first, item16.first,
	                          item17.first}));

	c.insert(item5);
	c.insert(item3);
	c.insert(item7);
	c.insert(item4);
	c.insert(item6);
	c.insert(item9);
	c.insert(item10);
	c.insert(item2);
	c.insert(item8);
	c.insert(item15);
	c.insert(item11);
	c.insert(item14);
	c.insert(item13);
	c.insert(item12);

	ASSERT_TRUE(verifyAVL(c, {item5.first, item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first, item2.first, item8.first, item15.first,
	                          item11.first, item14.first, item13.first, item12.first}));
	c.remove(15);
	c.remove(14);

	ASSERT_TRUE(verifyAVL(c, {item5.first, item3.first, item7.first, item4.first, item6.first,
	                          item9.first, item10.first, item2.first, item8.first,
	                          item11.first, item13.first, item12.first}));

}


// uncomment for debug output
#define DEBUG_STRESS_REMOVE

TEST(AVLStress, Remove)
{
	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(2, 8));
	testTree.insert(std::make_pair(1, -50));
	testTree.insert(std::make_pair(3, 0));
	testTree.insert(std::make_pair(10, 0));
	testTree.insert(std::make_pair(15, 0));

#ifdef DEBUG_STRESS_REMOVE
	std::cout << "Before any removals, tree is: " << std::endl;
	testTree.print();
#endif

	testTree.remove(-1);
	EXPECT_TRUE(verifyAVL(testTree, std::set<int>({2, 1, 3, 10, 15})));

#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing -1 (which doesn't exist), tree is: " << std::endl;
	testTree.print();
#endif

	testTree.remove(2);
	EXPECT_EQ(10, testTree.root_->item_.first);
	EXPECT_TRUE(verifyAVL(testTree, std::set<int>({1, 3, 10, 15})));

#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 2 (the root), tree is: " << std::endl;
	testTree.print();
#endif

	testTree.remove(10);
	EXPECT_TRUE(verifyAVL(testTree, std::set<int>({1, 3, 15})));

#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 10, tree is: " << std::endl;
	testTree.print();
#endif

	testTree.remove(1);
	EXPECT_TRUE(verifyAVL(testTree, std::set<int>({3, 15})));

#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 1, tree is: " << std::endl;
	testTree.print();
#endif

	testTree.remove(3);
	EXPECT_TRUE(verifyAVL(testTree, std::set<int>({15})));

#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 3, tree is: " << std::endl;
	testTree.print();
#endif

	testTree.remove(15);
	EXPECT_TRUE(verifyAVL(testTree, std::set<int>({})));

#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 15 (the last element), tree is: " << std::endl;
	testTree.print();
#endif

	testTree.remove(15);
	EXPECT_TRUE(verifyAVL(testTree, std::set<int>({})));

#ifdef DEBUG_STRESS_REMOVE
	std::cout << "After removing 15 (which doesn't exist), tree is: " << std::endl;
	testTree.print();
#endif
}
