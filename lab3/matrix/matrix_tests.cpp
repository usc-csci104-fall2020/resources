#include "matrix.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(MatrixTest, Basic) {
	Matrix i = {
		{1, 0, 0, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1}
	};
}

TEST(MatrixTest, CopyConstructor) {
	Matrix a = {
		{1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 0, 1, 1},
		{1, 0, 0, 0, 1}
	};
	Matrix b(a);
	EXPECT_EQ(a, b);
}

TEST(MatrixTest, CopyAssignmentOperator) {
	Matrix a = {
		{3, 0, 5, 0, 3},
		{0, 2, 0, 2, 0},
		{5, 0, 1, 0, 5},
		{0, 2, 0, 2, 1},
		{3, 0, 5, 0, 3}
	};
	Matrix b = a;
	Matrix c = b;
	EXPECT_EQ(a, b);
	EXPECT_EQ(b, c);
}

TEST(MatrixTest, Addition) {
	Matrix a = {
		{1, 0},
		{2, 4}
	};
	Matrix b = {
		{2, 0},
		{4, 8}
	};
	Matrix e = {
		{3, 0},
		{6, 12}
	};
	EXPECT_EQ(e, a + b);
}

TEST(MatrixTest, One_Dim_Multiplication) {
	Matrix a = {
		{1, 3, 5, 7, 9}
	};
	Matrix b = {
		{2},
		{4},
		{6},
		{8},
		{10}
	};
	Matrix e = {
		{190}
	};
	EXPECT_EQ(e, a * b);
}

TEST(MatrixTest, Two_Dim_Multiplication) {
	Matrix a = {
		{1, 9},
		{9, 8},
		{0, 4},
		{1, 6}
	};
	Matrix b = {
		{2, 0},
		{1, 9}
	};
	Matrix e = {
		{11, 81},
		{26, 72},
		{4, 36},
		{8, 54}
	};
	EXPECT_EQ(e, a * b);
}

TEST(MatrixTest, Identity_Multiplication) {
	Matrix i = {
		{1, 0, 0, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1}
	};
	Matrix m1 = {
		{81, 51},
		{6, 32},
		{4, 16},
		{82, 4},
		{99, 100}
	};
	Matrix m2 = {
		{81, 51, 0, 21},
		{6, 32, 32, 3},
		{4, 16, 4 ,100},
		{82, 4, 98, 43},
		{99, 100, 14, 20}
	};
	EXPECT_EQ(m1, i * m1);
	EXPECT_EQ(m2, i * m2);
}
