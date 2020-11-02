
#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>
#include <vector>
#include <set>
#include <string>
#include <cstdint>

// Header for CS104 test suite random number generation 

// type for random seeds
typedef uint32_t RandomSeed;

// template function for generating random vectors of different types of integer.
// Takes parameters for the count, seed, min and max, and whether or not duplicate values are allowed.
template<typename IntType>
std::vector<IntType> makeRandomNumberVector(size_t count, IntType min, IntType max, RandomSeed seed, bool allowDuplicates)
{
	// set up random number generator
	std::mt19937 randEngine;
	randEngine.seed(seed);

	std::uniform_int_distribution<IntType> distributor(min, max);

	// generate the vector
	std::vector<IntType> randomVector;
	randomVector.reserve(count);
	std::set<IntType> usedValues;
	do
	{
		IntType randInt = distributor(randEngine);

		if(!allowDuplicates)
		{
			// skip value if it's a duplicate

			if(usedValues.find(randInt) != usedValues.end())
			{
				//duplicate
				continue;
			}

			usedValues.insert(randInt);
		}

		randomVector.push_back(randInt);
	}
	while(randomVector.size() < count);


	return randomVector;
}

// Create a random sequence composed of the given elements repeated in random order.
template<typename T>
std::vector<T> makeRandomSequence(size_t count, std::vector<T> const & elements, RandomSeed seed)
{
	// set up random number generator
	std::mt19937 randEngine;
	randEngine.seed(seed);

	std::uniform_int_distribution<size_t> distributor(0, elements.size() - 1);

	std::vector<T> results;
	results.reserve(count);

	while(results.size() < count)
	{
		size_t elementIndex = distributor(randEngine);

		results.push_back(elements[elementIndex]);
	}

	return results;
}

// template function for generating a random integer
// Takes parameters for the seed, min and max.
template<typename IntType>
IntType makeRandomNumber(IntType min, IntType max, RandomSeed seed)
{
	// set up random number generator
	std::mt19937 randEngine;
	randEngine.seed(seed);

	// make numbers in [-5*count, 5*count]
	std::uniform_int_distribution<IntType> distributor(min, max);

	return distributor(randEngine);
}

// Generates a set of unique random integers of the given length, with the given seed.
// Generates numbers in the range [-10*count, 10*count]
std::set<int> makeRandomIntSet(size_t count, RandomSeed seed);

// Generates a vector of random integers of the given length, with the given seed.
// Generates numbers in the range [-5*count, 5*count].
// If allowDuplicates is true, then this function can generate duplicate values.
std::vector<int> makeRandomIntVector(size_t count, RandomSeed seed, bool allowDuplicates);

// Generates a vector of random seeds of the given length, with the given seed.
// Generates numbers in the range [0, 10*count].
// This function never generates duplicate values
std::vector<RandomSeed> makeRandomSeedVector(size_t count, RandomSeed seed);

// Generates a vector of random strings containing of the given length, with the given seed.
// The strings will be string-conversions of random numbers, in the range [-5*count, 5*count].
// Duplicates may be generated.
std::vector<std::string> makeRandomNumStringVector(size_t count, RandomSeed seed);

// generates a vector of count random strings with the given seed.
// strings will be composed of random lowercase alphabetic characters
std::vector<std::string> makeRandomAlphaStringVector(size_t count, RandomSeed seed, size_t stringLength, bool allowDuplicates);

#endif
