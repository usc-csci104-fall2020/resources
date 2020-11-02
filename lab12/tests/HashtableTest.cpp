#include "gtest/gtest.h"
#include "../hashtable.h"

#include <vector>
#include <iostream>
#include <random>
#include <set>

using namespace std;

string gen_random(int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    string temp = "";

    for (int i = 0; i < len; ++i) {
        temp += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return temp;
}

bool test_remove(const set<string>& contents, HashTable& test) {
	set<string> curr = contents;
	set<string> removed;
	for(string str : contents){
		curr.erase(curr.find(str));
		test.remove(str);
		removed.insert(str);
		for(string in : curr) {
			if(!test.find(in)) return false;
		}
		for(string out : removed) {
			if(test.find(out)) return false;
		}
	}
	return true;
}

TEST(HashtableTest, TestRemoveWithNoCollision) {
	HashTable test(10);
    test.insert("a");
    test.insert("b");
    test.insert("c");
    ASSERT_TRUE(test.find("a"));
    test.remove("a");
    ASSERT_FALSE(test.find("a"));
}

TEST(HashtableTest, TestRemoveWithOneCollision) {
	HashTable test(10);
    test.insert("ae");
    test.insert("ag");
    test.insert("ah");
    test.insert("ai");
    ASSERT_TRUE(test.find("ae"));
    test.remove("ae");
    ASSERT_FALSE(test.find("ae"));
}

TEST(HashtableTest, TestRemoveWithThreeCollisions) {
	HashTable test(10);
    test.insert("ac");
    test.insert("ae");
    test.insert("af");
    test.insert("ag");
    test.insert("ah");
    test.insert("ai");
    ASSERT_TRUE(test.find("ae"));
    test.remove("ae");
    ASSERT_FALSE(test.find("ae"));
}

TEST(HashtableTest, TestRemoveSize10) {
	set<string> all;
	srand(1);
	HashTable test(10);

	for(int i = 0; i < 10; i++) {
		string gen = gen_random(5);
		all.insert(gen);
		test.insert(gen);
	}
	ASSERT_TRUE(test_remove(all, test));

}

TEST(HashtableTest, TestRemoveReinsert) {
	set<string> all;
	srand(1);
	HashTable test(10);

	for(int i = 0; i < 10; i++) {
		string gen = gen_random(5);
		all.insert(gen);
		test.insert(gen);
	}
	ASSERT_TRUE(test_remove(all, test));

	all.clear();

	for(int i = 0; i < 10; i++) {
		string gen = gen_random(5);
		all.insert(gen);
		test.insert(gen);
	}
	ASSERT_TRUE(test_remove(all, test));

}

TEST(HashtableTest, TestOverinsert) {
	set<string> all;
	srand(1);
	HashTable test(10);

	for(int i = 0; i < 10; i++) {
		string gen = gen_random(5);
		all.insert(gen);
		test.insert(gen);
	}
	for(int i = 0; i < 20; i++) {
		string gen = gen_random(5);
		test.insert(gen);
	}
	ASSERT_TRUE(test_remove(all, test));
}


TEST(HashtableTest, TestRemoveStress) {
	set<string> all;
	srand(1);
	HashTable test(100);

	for(int i = 0; i < 100; i++) {
		string gen = gen_random(7);
		all.insert(gen);
		test.insert(gen);
	}
	ASSERT_TRUE(test_remove(all, test));
}

TEST(HashtableTest, TestRemoveSUPERSTRESS_AGHHHHHHHHH) {
	set<string> all;
	srand(1);
	HashTable test(1000);

	for(int i = 0; i < 1000; i++) {
		string gen = gen_random(9);
		all.insert(gen);
		test.insert(gen);
	}
	ASSERT_TRUE(test_remove(all, test));
}