//
// CS104 BST tree runtime tests
//

#include <check_bst.h>
#include <create_bst.h>
#include <runtime_evaluator.h>
#include <random_generator.h>

#include <gtest/gtest.h>
#include <iostream>

// runtime test for inserting a key in balanced order
TEST(BSTRuntime, InsertBalanced)
{
	RuntimeEvaluator runtimeEvaluator("BinarySearchTree::insert() with balanced insertions", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		BinarySearchTree<uint64_t, uint64_t> tree;
		std::vector<uint64_t> elems(numElements);
		uint64_t n = numElements/2;
		uint64_t numPerLevel = 1;
		uint64_t i = 0;
		for(uint64_t start = n; start >= 1; start /= 2, numPerLevel *= 2){
		  uint64_t val = start, step = start*2;
		  for(uint64_t j = 0; j < numPerLevel; j++){
		    elems[i++] = val;
		    val += step;
		  }
		}
		// fill the tree in balanced order
		for(uint64_t i = 0; i < numElements-1; ++i)
		{
			tree.insert(std::make_pair(elems[i], elems[i]));
		}

		BenchmarkTimer timer;
		tree.insert(std::make_pair(numElements + 1, numElements + 1));
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

// runtime test for removing a key in balanced order
TEST(BSTRuntime, RemoveBalancedRoot)
{
	RuntimeEvaluator runtimeEvaluator("BinarySearchTree::remove() root with keys in balanced order", 0, 15, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		BinarySearchTree<uint64_t, uint64_t> tree;
		std::vector<uint64_t> elems(numElements);
		uint64_t n = numElements/2;
		uint64_t numPerLevel = 1;
		uint64_t i = 0;
		for(uint64_t start = n; start >= 1; start /= 2, numPerLevel *= 2){
		  uint64_t val = start, step = start*2;
		  for(uint64_t j = 0; j < numPerLevel; j++){
		    elems[i++] = val;
		    val += step;
		  }
		}
		// fill the tree in balanced order
		for(uint64_t i = 0; i < numElements-1; ++i)
		{
			tree.insert(std::make_pair(elems[i], elems[i]));
		}

		BenchmarkTimer timer;
		tree.remove(numElements/2); // root should require predecessor 
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

// runtime test for removing a key in balanced order
TEST(BSTRuntime, RemoveBalancedMin)
{
	RuntimeEvaluator runtimeEvaluator("BinarySearchTree::remove() root with keys in balanced order", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		BinarySearchTree<uint64_t, uint64_t> tree;
		std::vector<uint64_t> elems(numElements);
		uint64_t n = numElements/2;
		uint64_t numPerLevel = 1;
		uint64_t i = 0;
		for(uint64_t start = n; start >= 1; start /= 2, numPerLevel *= 2){
		  uint64_t val = start, step = start*2;
		  for(uint64_t j = 0; j < numPerLevel; j++){
		    elems[i++] = val;
		    val += step;
		  }
		}
		// fill the tree in balanced order
		for(uint64_t i = 0; i < numElements-1; ++i)
		{
			tree.insert(std::make_pair(elems[i], elems[i]));
		}

		BenchmarkTimer timer;
		tree.remove(1); // 1 should be deepest
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}
// runtime test for finding the smallest node in balanced order
TEST(BSTRuntime, GetSmallestNodeBalanced)
{
	RuntimeEvaluator runtimeEvaluator("BinarySearchTree::getSmallestNode() with keys in balanced order", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		BinarySearchTree<uint64_t, uint64_t> tree;
		std::vector<uint64_t> elems(numElements);
		uint64_t n = numElements/2;
		uint64_t numPerLevel = 1;
		uint64_t i = 0;
		for(uint64_t start = n; start >= 1; start /= 2, numPerLevel *= 2){
		  uint64_t val = start, step = start*2;
		  for(uint64_t j = 0; j < numPerLevel; j++){
		    elems[i++] = val;
		    val += step;
		  }
		}
		// fill the tree in balanced order
		for(uint64_t i = 0; i < numElements-1; ++i)
		{
			tree.insert(std::make_pair(elems[i], elems[i]));
		}

		BenchmarkTimer timer;
		tree.getSmallestNode(); 
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

// runtime test for finding a key in balanced order
TEST(BSTRuntime, FindNodeBalanced)
{
	RuntimeEvaluator runtimeEvaluator("BinarySearchTree::find() with keys in balanced order", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		BinarySearchTree<uint64_t, uint64_t> tree;
		std::vector<uint64_t> elems(numElements);
		uint64_t n = numElements/2;
		uint64_t numPerLevel = 1;
		uint64_t i = 0;
		for(uint64_t start = n; start >= 1; start /= 2, numPerLevel *= 2){
		  uint64_t val = start, step = start*2;
		  for(uint64_t j = 0; j < numPerLevel; j++){
		    elems[i++] = val;
		    val += step;
		  }
		}
		// fill the tree in balanced order
		for(uint64_t i = 0; i < numElements-1; ++i)
		{
			tree.insert(std::make_pair(elems[i], elems[i]));
		}

		BenchmarkTimer timer;
		tree.find(1); 
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

// runtime test for iterating over all nodes in balanced order
TEST(BSTRuntime, IteratorBalanced)
{
	RuntimeEvaluator runtimeEvaluator("using BinarySearchTree::iterator to iterate over all keys", 0, 14, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		BinarySearchTree<uint64_t, uint64_t> tree;
		std::vector<uint64_t> elems(numElements);
		uint64_t n = numElements/2;
		uint64_t numPerLevel = 1;
		uint64_t i = 0;
		for(uint64_t start = n; start >= 1; start /= 2, numPerLevel *= 2){
		  uint64_t val = start, step = start*2;
		  for(uint64_t j = 0; j < numPerLevel; j++){
		    elems[i++] = val;
		    val += step;
		  }
		}
		// fill the tree in balanced order
		for(uint64_t i = 0; i < numElements-1; ++i)
		{
			tree.insert(std::make_pair(elems[i], elems[i]));
		}

		BinarySearchTree<uint64_t, uint64_t>::iterator it = tree.begin();
		BenchmarkTimer timer;
		for(uint64_t i = 0; i < numElements-1; i++){
		  ++it;
		}
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEAR));
}




