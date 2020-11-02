#ifndef RUNTIME_EVALUATOR_H
#define RUNTIME_EVALUATOR_H

#include <ctime>
#include <chrono>
#include <functional>
#include <vector>
#include <memory>
#include <set>

#include <libperf.h>

#include "random_generator.h"

// RuntimeEvaluator: C++ class that evaluates a snippet of code
// to determine its time complexity (linear, logarithmic, etc.)

// first, a utility class for benchmarking
class BenchmarkTimer
{
private:

#define BENCHMARK_TIMER_PERF_COUNTER LIBPERF_COUNT_SW_TASK_CLOCK

	// simple wrapper class to hold libperf reference
	struct LibperfHolder
	{
		struct libperf_data * libperf;

		LibperfHolder():
		libperf(libperf_initialize(-1, -1))
		{
			// enable task counter
			libperf_enablecounter(holder.libperf, BENCHMARK_TIMER_PERF_COUNTER);
		}

		~LibperfHolder()
		{
			libperf_disablecounter(holder.libperf, BENCHMARK_TIMER_PERF_COUNTER);

			libperf_close(libperf);
		}
	};

	// global reference of libperf
	static LibperfHolder holder;

	// Accrued time from previous enabled periods
	uint64_t accumulatedDuration;

	// time (in task clock ticks) that the clock was enabled (only valid if isEnabled is true)
	uint64_t currStartTime;

	bool isEnabled;

public:

	// Constructor.  If autoStart is true, the timer will start counting immediately.
	BenchmarkTimer(bool autoStart = true);

	BenchmarkTimer(const BenchmarkTimer & other) = default;

	// reset the accumulated time to 0 and start counting
	void start();

	// stop counting (for now).
	// Does nothing if the timer is not started.
	void stop();

	// start counting again, adding to the previous accumulated time.
	// Does nothing if the timer is started.
	void resume();

	// get the total accumulated time since the timer was started
	// units are Linux task clock ticks (CPU nanoseconds??)
	uint64_t getTime();
};

class RuntimeEvaluator
{
public:
	// type for code snippets for this class to evaluate.
	// the first parameter is the number of elements (n) for the function to operate on,
	// and the second is a random seed to use in generating random numbers.  The random seed is guaranteed to be
	// consistent for each trial every time evaluate() is run, but different between adjacent trials.
	// The return value should be a CPU task timer as returned by BenchmarkTimer.getTime()
	typedef std::function<uint64_t(uint64_t, RandomSeed)> Snippet;

	// enum for different time complexities.
	// NOTE: must be listed in order of increasing complexity
	enum class TimeComplexity: uint8_t
	{
		CONSTANT = 1,     // O(1)
		LOGARITHMIC = 2,  // O(logn)
		LINEAR = 3,       // O(n)
		LINEARITHMIC = 4, // O(nlogn)  **note: these usually end up getting detected as linear functions, but things will still work fine as they do
		QUADRATIC = 5,    // O(n^2)
		CUBIC = 6,        // O(n^3)
		EXPONENTIAL = 7   // O(e^n)    **note: currently not working due to high rate of false positives
	};

private:

	// represents a set of data points: the first element is the # of elements (independent variable),
	// and the second element is the runtime taken (dependent variable).
	// Note that there might be multiple points with the same # of elements.
	// DataSets are sorted from least to greatest # of elements.
	// NOTE: using a uint64_t to store nanoseconds give us up to 584 years, and I REALLY hope no function takes that long
	typedef std::vector<std::pair<uint64_t, uint64_t>> DataSet;

	// name of this snippet for output
	std::string _snippetName;

	// range of input sizes to test with (exponents of 2)
	uint8_t _evalRangeStart, _evalRangeEnd;

	// how many successive trials are performed for each size in the range.
	uint8_t _numTrialsPerSize;

	// code snippet to evaluate
	Snippet _snippet;

	// true iff we should print debug output for this runtime calculation
	bool _debug;

	// data recorded from evaluate() (null if evaluate has not been called)
	std::shared_ptr<DataSet> _recordedData;

	// if correlation factor is >= this, then a dataset is considered matching the given transformation
	double _correlationThreshold;

	// stores all time complexities that were matched when the snippet was evaluated
	std::set<TimeComplexity> _matchedComplexities;

	// print the data set in CSV format to cout
	static void printDataSet(DataSet const & data);

	// Calculates a linear regression of the given data.
	// Returns a pair of the regression slope and the regression y-intercept.
	static std::pair<double, double> calcLinearRegression(DataSet const & data);

	// for each x value, discard the top 15% of Y values
	// this is needed because Linux perf counters appear prone to random spikes of high runtime affecting a few percent of the data points
	void discardOutliers(DataSet & data);

	// struct for the return values of isLinear()
	struct LinearityConclusion
	{
		const double _regressionSlope;
		const bool _isLinear;

		LinearityConclusion(double regressionSlope, bool isLinear):
		_regressionSlope(regressionSlope),
		_isLinear(isLinear)
		{

		}
	};

	// Decide whether the given data set is linear or not.
	// Iff allowYIntercept is true, the error calculation will be done using the y-intercept parameter in the mix, otherwise it will assume that f(0) = 0.
	// This is required for O(1) functions to regress properly.
	LinearityConclusion isLinear(DataSet const & data, bool allowYIntercept = false);

public:

	// snippetName - name of snippet to use in cout statements
	// evalRangeStart, evalRangeEnd - range of input sizes to test the snippet over.  These are interpreted as
	//     exponents of 2.  For example, evalRangeStart = 4 would start the snippet with 2^4 = 16 elements.
	//     These values must be between 0 and 63 inclusive.
	// numTrialsPerSize - how many successive trials are performed for each size in the range.
	// snippet - code snippet to evaluate
	RuntimeEvaluator(std::string snippetName, uint8_t evalRangeStart, uint8_t evalRangeEnd, uint8_t numTrialsPerSize, Snippet const & snippet);

	// evaluate the snippet to determine its runtime.
	// With the number of items set to each power of two from evalRangeStart to evalRangeEnd, the
	// snippet is executed numTrialsPerSize times.
	void evaluate();

	// print the full data set to output, as well as more information about why
	// time complexity checks succeed or fail
	void enableDebugging()
	{
		_debug = true;
	}

	// Set the required correlation factor for a function to match its time complexity.
	// Lowering it permits a wider variance in the range of runtimes a function can have.
	// The default value is 2.0, and reasonable values would probably be between 1.0 and 3.0
	void setCorrelationThreshold(double threshold)
	{
		_correlationThreshold = threshold;
	}

	// Returns true iff the snippet appears to run in O of this time complexity.
	// If there are multiple possible complexities, then the lowest one is considered.

	// For example, if a snippet matched as both logarithmic and linear, then this function would return true
	// for LOGARITHMIC, LINEAR, and CUBIC complexities, but false for CONSTANT.
	bool meetsComplexity(TimeComplexity complexity);
};

#endif
