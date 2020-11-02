#ifndef MISC_UTILS_H
#define MISC_UTILS_H

#include <string>
#include <vector>
#include <sstream>

// Header for miscellaneous utilities used in the CS104 test suite

// Removes the limit on the max size the stack can grow to, allowing for much deeper recursive functions.
// Affects the current process; since test cases are each run in their own process this means it only affects 
// the current test case. 
// NOTE: if your program has a stack overflow after this function has been called, the system may steal
// stack from other processes, potentially crashing the entire computer.
void removeStackLimit();

// Converts a vector of items to a printable string
template<typename T>
std::string vectorToString(std::vector<T> const & items)
{
	std::stringstream output;
	output << '[';

	bool firstLoop = true;

	for(T const & item : items)
	{
		if(firstLoop)
		{
			firstLoop = false;
		}
		else
		{
			output << ", ";
		}

		output << item;
	}

	output << ']';

	return output.str();
}

// simple sgn function -- from https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
// can someone explain to me why this is not in standard C/C++ again?
template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

// converts string to lower case
void makeLowercase(std::string & toConvert);

// splits a string on a token into a vector of strings
std::vector<std::string> splitString(std::string str, std::string const & token);

// used when we are in a checker function and need to call another checker function.
// If the given function returns a false AssertionResult, this returns it from the current function.
#define SUB_ASSERT(functioncall) \
{ \
	testing::AssertionResult result = functioncall;\
	if(!result) \
	{\
		return result; \
	} \
}

#endif