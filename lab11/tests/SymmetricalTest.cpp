#include "gtest/gtest.h"
#include "../symmetrical.h"
#include <iostream>

using namespace std;

TEST(SymmetricalTest, SymmetricalTestEmpty) { 
	ASSERT_TRUE(isSymmetrical(nullptr));
}

TEST(SymmetricalTest, SymmetricalTestTrue) { 
	// Leaf Nodes
	Node n4left(nullptr, nullptr, 4);
	Node n4right(nullptr, nullptr, 4);

	Node n3left(nullptr, nullptr, 3);
	Node n3right(nullptr, nullptr, 3);

	Node n2left(&n4left, &n3left, 2);
	Node n2right(&n3right, &n4right, 2);

	Node n1(&n2left, &n2right, 1);

	ASSERT_TRUE(isSymmetrical(&n1));
}

TEST(SymmetricalTest, SymmetricalTestFalse) { 
	// Leaf Nodes
	Node n4left(nullptr, nullptr, 4);
	Node n4right(nullptr, nullptr, 4);

	Node n3left(nullptr, nullptr, 3);
	Node n3right(nullptr, nullptr, 3);

	Node n2left(&n4left, &n3left, 2);
	Node n2right(&n4right, &n3right, 2); // This line is different

	Node n1(&n2left, &n2right, 1);

	ASSERT_FALSE(isSymmetrical(&n1));
}