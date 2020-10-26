#include "gtest/gtest.h"
#include "../allCombos.h"
#include <iostream>

using namespace std;

bool checkAllCombos(const std::vector<std::string>& expected, std::vector<std::string> actual) {
	for (auto combo : expected)
	{
		std::vector<std::string>::iterator it = std::find(actual.begin(), actual.end(), combo);
		if (it == actual.end())
			return false;
		else
			actual.erase(it);
	}
	return actual.empty();
}

TEST(AllCombosTest, AllCombosSimple) { 
	std::vector<char> letters = { 'U', 'S', 'C' };
	std::vector<std::string> expected = {
		"U",
		"S",
		"C"
	};
	std::vector<std::string> actual = allCombos(letters, 1);
	ASSERT_TRUE(checkAllCombos(expected, actual));

	expected = {
		"UU",
		"US",
		"UC",
		"SU",
		"SS",
		"SC",
		"CU",
		"CS",
		"CC"
	};
	actual = allCombos(letters, 2);
	ASSERT_TRUE(checkAllCombos(expected, actual));

	expected = {
		"UUU", "UUS", "UUC", 
		"USU", "USS", "USC", 
		"UCU", "UCS", "UCC", 
		"SUU", "SUS", "SUC", 
		"SSU", "SSS", "SSC", 
		"SCU", "SCS", "SCC", 
		"CUU", "CUS", "CUC", 
		"CSU", "CSS", "CSC", 
		"CCU", "CCS", "CCC"
	};
	actual = allCombos(letters, 3);
	ASSERT_TRUE(checkAllCombos(expected, actual));
}