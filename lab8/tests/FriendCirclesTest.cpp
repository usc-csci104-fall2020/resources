#include "gtest/gtest.h"
#include "../friend_circles.h"

#include <vector>
#include <iostream>

using namespace std;

TEST(FriendCirclesTest, Empty) {
	vector<vector<int>> M1;
	EXPECT_EQ(0, findCircleNum(M1));


	vector<vector<int>> M2 {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};
	EXPECT_EQ(3, findCircleNum(M2));
}

TEST(FriendCirclesTest, Basic) {
	vector<vector<int>> M1 {
		{1, 1, 0},
		{1, 1, 0},
		{0, 0, 1}
	};
	EXPECT_EQ(2, findCircleNum(M1));


	vector<vector<int>> M2 {
		{1, 1, 0},
		{1, 1, 1},
		{0, 1, 1}
	};
	EXPECT_EQ(1, findCircleNum(M2));
}

TEST(FriendCirclesTest, Medium) {
	vector<vector<int>> M1 {
		{1, 1, 0, 0}, // 0 and 1 are friends
		{1, 1, 1, 0}, // 0, 1, 2 are friends
		{0, 1, 1, 0}, // 1 and 2 are friends
		{0, 0, 0, 1} // 3 is alone
	};
	// 0, 1, and 2 are in a friend circle
	// 3 is in another friend circle
	EXPECT_EQ(2, findCircleNum(M1));

	vector<vector<int>> M2 {
		{1, 1, 0, 0}, // 0 and 1 are friends
		{1, 1, 0, 0}, // 0 and 1 are friends
		{0, 0, 1, 0}, // 2 is alone
		{0, 0, 0, 1} // 3 is alone
	};
	// 0 and 1 are in a friend circle
	// 2 is in another friend circle
	// 3 is in another friend circle
	EXPECT_EQ(3, findCircleNum(M2));

	vector<vector<int>> M3 {
		{1, 0, 0, 1}, // 0 and 3 are friends
		{0, 1, 1, 0}, // 1 and 2 are friends
		{0, 1, 1, 1}, // 1, 2, 3 are friends
		{1, 0, 1, 1} // 0, 2, 3 are friends
	};
	// 0, 1, 2, 3 are all in one friend circle
	EXPECT_EQ(1, findCircleNum(M3));
}
