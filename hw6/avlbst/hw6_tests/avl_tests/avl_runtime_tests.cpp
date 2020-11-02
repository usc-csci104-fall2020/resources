//
// CS104 AVL tree runtime tests
//

#include "publicified_avlbst.h"


#include <create_bst.h>
#include <runtime_evaluator.h>
#include <random_generator.h>

#include <gtest/gtest.h>

// runtime test for keys in increasing order
TEST(AVLRuntime, InsertAscending)
{
	RuntimeEvaluator runtimeEvaluator("AVLTree::insert() with keys in ascending order", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		AVLTree<uint64_t, uint64_t> tree;

		// fill the tree in ascending order
		for(uint64_t element = 0; element < numElements; ++element)
		{
			tree.insert(std::make_pair(element, element));
		}

		BenchmarkTimer timer;
		tree.insert(std::make_pair(numElements - 1, numElements - 1));
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

// runtime test for keys in decreasing order
TEST(AVLRuntime, InsertDescending)
{
	RuntimeEvaluator runtimeEvaluator("AVLTree::insert() with keys in descending order", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		AVLTree<uint64_t, uint64_t> tree;

		// fill the tree in ascending order
		for(uint64_t element = numElements - 1; element > 0; --element)
		{
			tree.insert(std::make_pair(element, element));
		}

		BenchmarkTimer timer;
		tree.insert(std::make_pair(0, 0));
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

// runtime test for keys in random order
TEST(AVLRuntime, InsertRandom)
{
	RuntimeEvaluator runtimeEvaluator("AVLTree::insert() with keys in random order", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		AVLTree<uint64_t, uint64_t> tree;

		std::vector<uint64_t> elements = makeRandomNumberVector<uint64_t>(numElements, 0, numElements * 10, seed, false);

		// fill the tree in ascending order
		for(size_t elementIndex = 0; elementIndex < numElements - 1; ++elementIndex)
		{
			tree.insert(std::make_pair(elements[elementIndex], elements[elementIndex]));
		}

		BenchmarkTimer timer;
		tree.insert(std::make_pair(elements[numElements - 1], elements[numElements - 1]));
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

TEST(AVLRuntime, RemoveMin)
{
	RuntimeEvaluator runtimeEvaluator("AVLTree::remove() on min element", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		AVLTree<uint64_t, uint64_t> tree;

		// fill the tree in ascending order
		for(uint64_t element = 0; element < numElements; ++element)
		{
			tree.insert(std::make_pair(element, element));
		}

		BenchmarkTimer timer;
		tree.remove(0);
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

TEST(AVLRuntime, RemoveMax)
{
	RuntimeEvaluator runtimeEvaluator("AVLTree::remove() on max element", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		AVLTree<uint64_t, uint64_t> tree;

		// fill the tree in ascending order
		for(uint64_t element = 0; element < numElements; ++element)
		{
			tree.insert(std::make_pair(element, element));
		}

		BenchmarkTimer timer;
		tree.remove(numElements - 1);
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}
