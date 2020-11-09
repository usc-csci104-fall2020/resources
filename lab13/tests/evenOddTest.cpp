#include "gtest/gtest.h"
#include "../evenOdd.h"
#include <iostream>

using namespace std;

TEST(EvenOdd, basic) 
{
	std::shared_ptr<Node> n1 = std::make_shared<Node>(1);
	std::shared_ptr<Node> temp = oddEvenList(n1);

	ASSERT_EQ(temp->val, 1);
}


TEST(EvenOdd, segfault) 
{
	std::shared_ptr<Node> n1 = nullptr;
	std::shared_ptr<Node> temp = oddEvenList(n1);
}

TEST(EvenOdd, shorttest) 
{
	std::shared_ptr<Node> n1 = std::make_shared<Node>(1, (std::make_shared<Node>(2, std::make_shared<Node>(3))));
	std::shared_ptr<Node> temp = oddEvenList(n1);

	vector<int> result = {1, 3, 2};

	for(size_t i = 0; i < result.size(); i++) {
		ASSERT_EQ(temp->val, result[i]);
		temp = temp->next;
	}
}

TEST(EvenOdd, normal) 
{
	std::shared_ptr<Node> n1 = std::make_shared<Node>(1, (std::make_shared<Node>(2, std::make_shared<Node>(3, std::make_shared<Node>(4, std::make_shared<Node>(5))))));
	std::shared_ptr<Node> temp = oddEvenList(n1);

	vector<int> result = {1, 3, 5, 2, 4};

	for(size_t i = 0; i < result.size(); i++) {
		ASSERT_EQ(temp->val, result[i]);
		temp = temp->next;
	}

}

TEST(EvenOdd, long) 
{
	std::shared_ptr<Node> n2 = std::make_shared<Node>(6, (std::make_shared<Node>(7, std::make_shared<Node>(8, std::make_shared<Node>(9, std::make_shared<Node>(10))))));
	std::shared_ptr<Node> n1 = std::make_shared<Node>(1, (std::make_shared<Node>(2, std::make_shared<Node>(3, std::make_shared<Node>(4, std::make_shared<Node>(5, n2))))));
	std::shared_ptr<Node> temp = oddEvenList(n1);

	vector<int> result = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

	for(size_t i = 0; i < result.size(); i++) {
		ASSERT_EQ(temp->val, result[i]);
		temp = temp->next;
	}

}