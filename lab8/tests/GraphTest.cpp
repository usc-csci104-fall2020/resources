#include "gtest/gtest.h"
#include "../graph.h"

#include <vector>
#include <iostream>

using namespace std;

TEST(GraphTest, DFS_FALSE) {
	Node first;
	Node second;
	Node third;
	Node fourth;
	Node fifth;

	first.neighbors = {&second, &third};
	third.neighbors = {&fourth};
	fourth.neighbors = {&third};

	EXPECT_FALSE(DFS(&first, &fifth));
}

TEST(GraphTest, DFS_TRUE) {
	Node first;
	Node second;
	Node third;
	Node fourth;
	Node fifth;

	first.neighbors = {&second, &third};
	third.neighbors = {&fourth};
	fourth.neighbors = {&third};

	EXPECT_TRUE(DFS(&first, &second));
}

TEST(GraphTest, BFS) {
	vector<vector<int> > adjacency_matrix = 
	{
		{0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
	};

	EXPECT_TRUE(BFS(adjacency_matrix, 0, 3));
	EXPECT_FALSE(BFS(adjacency_matrix, 0, 4));
}
