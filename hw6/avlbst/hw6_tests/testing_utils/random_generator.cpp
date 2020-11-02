
#include "random_generator.h"

#include <limits>

// Generates a set of unique random integers of the given length, with the given seed.
std::set<int> makeRandomIntSet(size_t count, RandomSeed seed)
{
	// set up random number generator
	std::mt19937 randEngine;
	randEngine.seed(seed);

	// make numbers in [-10*count, 10*count]
	std::uniform_int_distribution<int> distributor(-5 * ((int)count), 5 * ((int)count));

	// keep adding numbers until we have enough.
	// We can't use a for-loop because some numbers are duplicates and won't count.
	std::set<int> randomSet;
	do
	{
		randomSet.insert(distributor(randEngine));
	}
	while(randomSet.size() < count);

	return randomSet;
}


std::vector<int> makeRandomIntVector(size_t count, RandomSeed seed, bool allowDuplicates)
{
	return makeRandomNumberVector<int>(count, -5 * static_cast<int>(count), 5 * static_cast<int>(count), seed, allowDuplicates);
}

std::vector<RandomSeed> makeRandomSeedVector(size_t count, RandomSeed seed)
{
	return makeRandomNumberVector<RandomSeed>(count, 0, 10 * static_cast<RandomSeed>(count), seed, false);
}

std::vector<std::string> makeRandomNumStringVector(size_t count, RandomSeed seed)
{
	// set up random number generator
	std::mt19937 randEngine;
	randEngine.seed(seed);

	// make numbers in [-5*count, 5*count]
	std::uniform_int_distribution<int> distributor(-5 * ((int)count), 5 * ((int)count));

	// generate the vector
	std::vector<std::string> randomVector;
	randomVector.reserve(count);
	for(size_t index = 0; index < count; ++index)
	{
		randomVector.push_back(std::to_string(distributor(randEngine)));
	}

	return randomVector;
}

std::vector<std::string> makeRandomAlphaStringVector(size_t count, RandomSeed seed, size_t stringLength, bool allowDuplicates)
{
	// set up random number generator
	std::mt19937 randEngine;
	randEngine.seed(seed);

	// have each byte be a character between a and z
	std::uniform_int_distribution<uint8_t> distributor('a', 'z');

	// generate the vector
	std::vector<std::string> randomVector;
	randomVector.reserve(count);
	std::set<std::string> usedValues;
	do
	{
		std::string currString;

		while(currString.length() < stringLength)
		{
			currString.insert(currString.length(), 1, distributor(randEngine));
		}

		if(!allowDuplicates)
		{
			// skip value if it's a duplicate

			if(usedValues.find(currString) != usedValues.end())
			{
				//duplicate
				continue;
			}

			usedValues.insert(currString);
		}

		randomVector.push_back(currString);
	}
	while(randomVector.size() < count);

	return randomVector;
}