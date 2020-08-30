#include "array.h"
#include "gtest/gtest.h"

TEST(ArrayTest, Basic) {
    Array a;
    for (int i = 0; i < 5; ++i) {
        a.push(i);
    }
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(a.at(i), i);
    }
}

TEST(ArrayTest, CopyConstructor) {
    Array a;
    for (int i = 0; i < 5; ++i) {
        a.push(i);
    }
    Array b(a);
}

TEST(ArrayTest, CopyAssignmentOperator) {
    Array a;
    for (int i = 0; i < 5; ++i) {
        a.push(i);
    }
    Array b;
    for (int i = 0; i < 5; ++i) {
        b.push(i);
    }
    b = a;
}
