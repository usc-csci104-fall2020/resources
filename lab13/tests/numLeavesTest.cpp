#include "gtest/gtest.h"
#include "../numLeaves.h"
#include <iostream>

using namespace std;

TEST(NumLeaves, empty) 
{
	EXPECT_EQ(numLeaves(nullptr), 0);
}

TEST(NumLeaves, oneLeaf) 
{
	/*
		 1
		/
	   2
	*/
	Node n2(2, nullptr, nullptr);
	Node n1(1, std::make_shared<Node>(n2), nullptr);

	EXPECT_EQ(numLeaves(std::make_shared<Node>(n1)), 1);
}

TEST(NumLeaves, twoLeaves) 
{
	/*
		 1
		/ \
	   2   3
	*/
	Node n3(3, nullptr, nullptr);
	Node n2(2, nullptr, nullptr);
	Node n1(1, std::make_shared<Node>(n2), std::make_shared<Node>(n3));

	EXPECT_EQ(numLeaves(std::make_shared<Node>(n1)), 2);
}

TEST(NumLeaves, threeLeaves) 
{
	/*
		 1
		/ \
	   2   3
	  / \
	 4   5
	*/
	Node n5(5, nullptr, nullptr);
	Node n4(4, nullptr, nullptr);
	Node n3(3, nullptr, nullptr);
	Node n2(2, std::make_shared<Node>(n4), std::make_shared<Node>(n5));
	Node n1(1, std::make_shared<Node>(n2), std::make_shared<Node>(n3));

	EXPECT_EQ(numLeaves(std::make_shared<Node>(n1)), 3);
}

TEST(NumLeaves, fourLeaves) 
{
	/*
		  1
		/   \
	   2     3
	  / \   / \
	 4   5 6   7
	*/
	Node n7(7, nullptr, nullptr);
	Node n6(6, nullptr, nullptr);
	Node n5(5, nullptr, nullptr);
	Node n4(4, nullptr, nullptr);
	Node n3(3, std::make_shared<Node>(n6), std::make_shared<Node>(n7));
	Node n2(2, std::make_shared<Node>(n4), std::make_shared<Node>(n5));
	Node n1(1, std::make_shared<Node>(n2), std::make_shared<Node>(n3));

	EXPECT_EQ(numLeaves(std::make_shared<Node>(n1)), 4);
}


