#include "runtime_evaluator.h"

#include <misc_utils.h>

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

BenchmarkTimer::LibperfHolder BenchmarkTimer::holder{};

BenchmarkTimer::BenchmarkTimer(bool autoStart):
accumulatedDuration(),
currStartTime(),
isEnabled(autoStart)
{
	if(autoStart)
	{
		start();
	}
}

void BenchmarkTimer::start()
{
	accumulatedDuration = 0;
	currStartTime = libperf_readcounter(holder.libperf, BENCHMARK_TIMER_PERF_COUNTER);

	isEnabled = true;
}

void BenchmarkTimer::stop()
{
	if(isEnabled)
	{
		accumulatedDuration += libperf_readcounter(holder.libperf, BENCHMARK_TIMER_PERF_COUNTER) - currStartTime;

		isEnabled = false;
	}

}

void BenchmarkTimer::resume()
{
	if(!isEnabled)
	{
		currStartTime = libperf_readcounter(holder.libperf, BENCHMARK_TIMER_PERF_COUNTER);

		isEnabled = true;
	}
}

uint64_t BenchmarkTimer::getTime()
{
	return accumulatedDuration;
}

void RuntimeEvaluator::printDataSet(DataSet const & data)
{
	std::cout << "# of Elements, Runtime (ns)" << std::endl;
	std::cout << std::fixed << std::setprecision(0);

	for(std::pair<uint64_t, uint64_t> const & dataPoint : data)
	{
		std::cout << dataPoint.first << ", " << dataPoint.second << std::endl;
	}
}

std::pair<double, double> RuntimeEvaluator::calcLinearRegression(DataSet const & data)
{
	double numPoints = static_cast<double>(data.size());

	// calculate sums used in the formula
	double sumXY = 0;
	double sumX = 0;
	double sumY = 0;
	double sumXSquared = 0;

	for(std::pair<uint64_t, uint64_t> const & point : data)
	{
		sumXY += static_cast<double>(point.first * point.second);
		sumX += static_cast<double>(point.first);
		sumY += static_cast<double>(point.second);
		sumXSquared += static_cast<double>(point.first * point.first);
	}

	// formula from here: https://www.mathsisfun.com/data/least-squares-regression.html
	double regressionSlope = (numPoints * sumXY - sumX * sumY) / (numPoints * sumXSquared - sumX * sumX);

	double regressionYintercept = (sumY - regressionSlope * sumX) / numPoints;

	return std::make_pair(regressionSlope, regressionYintercept);
}

void RuntimeEvaluator::discardOutliers(RuntimeEvaluator::DataSet &data)
{
	// first, figure out all the unique X values
	std::set<uint64_t> uniqueXValues;
	for(std::pair<uint64_t, uint64_t> const & point : data)
	{
		uniqueXValues.insert(point.first);
	}

	// it's easier to work with this data as a multimap
	std::multimap<uint64_t, uint64_t> dataMap(data.begin(), data.end());

	for(uint64_t xValue : uniqueXValues)
	{
		// now get all the Y values in sorted order
		auto valuesIteratorPair = dataMap.equal_range(xValue);
		std::multimap<uint64_t, uint64_t>::iterator yValReadIter = valuesIteratorPair.first;
		std::multimap<uint64_t, uint64_t>::iterator yValEndIter = valuesIteratorPair.second;

		std::vector<uint64_t> yValues;
		while(yValReadIter != yValEndIter)
		{
			yValues.push_back(yValReadIter->second);
			++yValReadIter;
		}

		std::sort(yValues.begin(), yValues.end());

		// ...aand go back through and knock off the 10% of largest values
		size_t valsToRemove = static_cast<size_t>(yValues.size() * (15.0 / 100));
		if(valsToRemove > 0)
		{
			for(size_t largestValIndex = yValues.size() - 1;  yValues.size() - largestValIndex < valsToRemove; --largestValIndex)
			{
				// linear search through and remove this value
				valuesIteratorPair = dataMap.equal_range(xValue);
				std::multimap<uint64_t, uint64_t>::iterator yValEraseIter = valuesIteratorPair.first;
				yValEndIter = valuesIteratorPair.second;

				while(yValEraseIter != yValEndIter)
				{
					if(yValEraseIter->second == yValues.at(largestValIndex))
					{
						if(_debug)
						{
							std::cout << "Removed outlier data point (" << xValue << ", "  << yValEraseIter->second << ")" << std::endl;
						}

						dataMap.erase(yValEraseIter);

						break;
					}
					++yValEraseIter;
				}

			}

		}

	}

	// now convert back from a multimap
	data = DataSet(dataMap.begin(), dataMap.end());
}

RuntimeEvaluator::LinearityConclusion RuntimeEvaluator::isLinear(DataSet const & data, bool allowYIntercept)
{
	std::pair<double, double> regressionCoefficients = calcLinearRegression(data);

	if(!allowYIntercept)
	{
		regressionCoefficients.second = 0;
	}

	// calculate mean squared error (and sum of squared y coefficients, to get something to compare it to)
	double sumErrorSquared = 0;
	double sumYSquared = 0;

	for(std::pair<uint64_t, uint64_t> const & point : data)
	{
		// estimate the time using the regression
		double regressionTime = static_cast<double>(point.first) * regressionCoefficients.first + static_cast<double>(regressionCoefficients.second);

		double regressionError = regressionTime - static_cast<double>(point.second);

		// to find out how close we are to the regression, we use squared errors -- this serves to weight a few large errors higher than lots of medium errors
		// I did modify the standard formula though by keeping the sign term.  This means that if there are errors on both sides of the regression line,
		// they will compensate for each other and decrease the total error versus if all errors are on the same side of the line.
		sumErrorSquared += regressionError * regressionError * sgn(regressionError);

		sumYSquared += static_cast<double>(point.second * point.second);
	}

	double averageErrorSquared = fabs(sumErrorSquared / static_cast<double>(data.size()));
	double averageYSquared = sumYSquared / static_cast<double>(data.size());

	double correlationFactor;

	if(averageErrorSquared == 0)
	{
		// no error means perfect linearity
		correlationFactor = INFINITY;
	}
	else
	{
		// in my preliminary testing, I found that comparing the average error and average y^2 values was a reasonable test for how linear the data is.
		// If the average y^2 is an order of magnitude or two greater than the average error, the data is more or less linear.
		// This ratio also has the nice property that if you multiply all times by a scalar, it stays the same,
		// so if the user's function gets 10x faster in every case, the correlation factor doesn't change at all.
		correlationFactor = log10(averageYSquared) - log10(averageErrorSquared);
	}

	if(_debug)
	{
		// always print 2 decimal places
		std::cout << std::scientific << std::setprecision(2);

		std::cout << "Average error squared: " << averageErrorSquared << std::endl;
		std::cout << "Average y squared: " << averageYSquared << std::endl;
		
	}

	std::cout << std::fixed << std::setprecision(4);

	if(_debug)
	{
		std::cout << "Regression formula: t = " << regressionCoefficients.first << "n + " << regressionCoefficients.second << std::endl;
	}
	
	std::cout << "Correlation factor (" << correlationFactor << ") is " << (correlationFactor >= _correlationThreshold ? ">=" : "<")
			<< " threshold (" << _correlationThreshold << ')' << std::endl;
	


	return LinearityConclusion(regressionCoefficients.first, correlationFactor >= _correlationThreshold);
}


RuntimeEvaluator::RuntimeEvaluator(std::string snippetName, uint8_t evalRangeStart, uint8_t evalRangeEnd, uint8_t numTrialsPerSize, Snippet const & snippet):
_snippetName(std::move(snippetName)),
_evalRangeStart(evalRangeStart),
_evalRangeEnd(evalRangeEnd),
_numTrialsPerSize(numTrialsPerSize),
_snippet(snippet),
_debug(false),
_recordedData(),
_correlationThreshold(2.0), // default value determined by modeling a couple of analyses in Excel
_matchedComplexities()
{
	// note: 64 comes from log2(max value of uint64_t)
	assert(_evalRangeStart < 64);
	assert(_evalRangeEnd < 64);

	assert(_evalRangeStart <= _evalRangeEnd);
}

// my Excel models seem to indicate that linear functions would have a slope of at least 1e-5 us/item
#define POSITIVE_REGRESSION_SLOPE .1e-5

void RuntimeEvaluator::evaluate()
{
	_recordedData = std::make_shared<DataSet>();

	std::cout << ">> Evaluating runtime of " << _snippetName << std::endl;

	for(uint8_t currPowOf2 = _evalRangeStart; currPowOf2 <= _evalRangeEnd; ++currPowOf2)
	{
		uint64_t numElements = static_cast<uint64_t>(pow(2, currPowOf2));

		std::cout << "Testing with 2^" << static_cast<uint16_t>(currPowOf2) << " (" << numElements << ") elements (trial ";

		for(uint8_t trial = 1; trial <= _numTrialsPerSize; ++trial)
		{
			std::stringstream progressMessage;
			progressMessage << static_cast<uint16_t>(trial) << '/' << static_cast<uint16_t>(_numTrialsPerSize) << ')';
			std::cout << progressMessage.str() << std::flush;

			// create random seed.  To get a nearly-unique uint32_t, we XOR the upper and lower halves of numElements together, then XOR trial every 4th bit
			RandomSeed seed = static_cast<RandomSeed>((numElements >> 32) ^ (numElements & 0xFFFFFFFF));
			for(uint8_t bit = 0; bit < sizeof(uint32_t) * 8; ++bit)
			{
				uint8_t bitToXor = static_cast<uint8_t>((trial & (1 << bit)) >> bit);
				seed ^= bitToXor << bit * 4;
			}

			uint64_t trialDuration = _snippet(numElements, seed);
			_recordedData->emplace_back(numElements, trialDuration);

			if(trial < _numTrialsPerSize)
			{
				// erase the message we printed earlier
				size_t numChars = progressMessage.str().length();
				std::cout << std::string(numChars, '\b');
			}
		}

		std::cout << std::endl;

	}

	discardOutliers(*_recordedData);

	if(_debug)
	{
		std::cout << "Runtime data: " << std::endl;
		printDataSet(*_recordedData);
		std::cout << "----------------------------------------------" << std::endl;
	}

	// ----------------------------------------------------------------------------------------
	// check data

	if(_recordedData->empty())
	{
		std::cerr << "ERROR: no runtime data points recorded for " << _snippetName << "." << std::endl;
		std::cerr << "Perhaps you need to fix the testing range?" << std::endl;
		return;
	}

	bool allZeros = true;

	for(std::pair<uint64_t, uint64_t> const & point : *_recordedData)
	{
		if(point.second != 0)
		{
			allZeros = false;
			break;
		}
	}

	if(allZeros)
	{
		std::cout << "WARNING: All runtime data points recorded for " << _snippetName << " are zeros." << std::endl;
		std::cerr << "Perhaps you need to increase the number of elements used?" << std::endl;
	}

	// ----------------------------------------------------------------------------------------

	std::cout << "Testing if time complexity could be linear..." << std::endl;

	LinearityConclusion linearConclusion = isLinear(*_recordedData);

	// to try and exclude constant-time functions, we disable the y-intercept and require a positive slope
	if(linearConclusion._isLinear && linearConclusion._regressionSlope >= POSITIVE_REGRESSION_SLOPE)
	{
		std::cout << ">> Time complexity of " << _snippetName << " is likely linear" << std::endl;
		_matchedComplexities.insert(TimeComplexity::LINEAR);
	}

	// ----------------------------------------------------------------------------------------

	std::cout << "Testing if time complexity could be constant..." << std::endl;


	// t = c
	// nt = cn

	// transform data by multiplying it by the size to create a linear function.
	// we also make every 0 into a 1 to make sure that they don't throw off the measurement

	DataSet constantCompensatedData;
	for(std::pair<uint64_t, uint64_t> const & point : *_recordedData)
	{
		uint64_t correctedTime = point.second;
		if(correctedTime == 0)
		{
			correctedTime = 1;
		}

		constantCompensatedData.emplace_back(point.first, static_cast<double>(correctedTime * point.first));
	}

	LinearityConclusion constantConclusion = isLinear(constantCompensatedData);

	if(constantConclusion._isLinear && constantConclusion._regressionSlope >= POSITIVE_REGRESSION_SLOPE)
	{
		std::cout << ">> Time complexity of " << _snippetName << " is likely constant" << std::endl;
		_matchedComplexities.insert(TimeComplexity::CONSTANT);
	}

	// ----------------------------------------------------------------------------------------

	std::cout << "Testing if time complexity could be logarithmic..." << std::endl;

	// t = logₖ(n)
	// t = ln(n)/ln(k)
	// t * ln(k) = ln(n)  [ln(k) is a constant]

	DataSet logarithmicCompensatedData;
	for(std::pair<uint64_t, uint64_t> const & point : *_recordedData)
	{
		logarithmicCompensatedData.emplace_back(log(point.first), point.second);
	}

	LinearityConclusion logarithmicConclusion = isLinear(logarithmicCompensatedData);

	if(logarithmicConclusion._isLinear && logarithmicConclusion._regressionSlope >= POSITIVE_REGRESSION_SLOPE)
	{
		std::cout << ">> Time complexity of " << _snippetName << " is likely logarithmic" << std::endl;
		_matchedComplexities.insert(TimeComplexity::LOGARITHMIC);
	}

	// ----------------------------------------------------------------------------------------

	std::cout << "Testing if time complexity could be linearithmic..." << std::endl;

	// t = nlogₖ(n)
	// t = n*(ln(n)/ln(k))
	// ln(k)*t/n = ln(n)

	DataSet linearrithmicCompensatedData;
	for(std::pair<uint64_t, uint64_t> const & point : *_recordedData)
	{
		linearrithmicCompensatedData.emplace_back(log(point.first), point.second / point.first);
	}

	LinearityConclusion linearithmicConclusion = isLinear(linearrithmicCompensatedData);

	if(linearithmicConclusion._isLinear && linearithmicConclusion._regressionSlope >= POSITIVE_REGRESSION_SLOPE)
	{
		std::cout << ">> Time complexity of " << _snippetName << " is likely linearithmic" << std::endl;
		_matchedComplexities.insert(TimeComplexity::LINEARITHMIC);
	}



	// ----------------------------------------------------------------------------------------

	std::cout << "Testing if time complexity could be quadratic..." << std::endl;

	// t = n^2
	// √t = n  (t and n are both >0)

	// transform recorded data by square-rooting it
	DataSet quadraticCompensatedData;
	for(std::pair<uint64_t, uint64_t> const & point : *_recordedData)
	{
		quadraticCompensatedData.emplace_back(point.first, sqrt(static_cast<double>(point.second)));
	}

	LinearityConclusion quadraticConclusion = isLinear(quadraticCompensatedData);

	if(quadraticConclusion._isLinear && quadraticConclusion._regressionSlope >= POSITIVE_REGRESSION_SLOPE)
	{
		std::cout << ">> Time complexity of " << _snippetName << " is likely quadratic" << std::endl;
		_matchedComplexities.insert(TimeComplexity::QUADRATIC);
	}

	// ----------------------------------------------------------------------------------------

	std::cout << "Testing if time complexity could be cubic..." << std::endl;


	// t = n^3
	// ∛t = n

	// transform recorded data by cube-rooting it
	DataSet cubicCompensatedData;
	for(std::pair<uint64_t, uint64_t> const & point : *_recordedData)
	{
		cubicCompensatedData.emplace_back(point.first, cbrt(static_cast<double>(point.second)));
	}

	LinearityConclusion cubicConclusion = isLinear(cubicCompensatedData);

	if(cubicConclusion._isLinear && cubicConclusion._regressionSlope >= POSITIVE_REGRESSION_SLOPE)
	{
		std::cout << ">> Time complexity of " << _snippetName << " is likely cubic" << std::endl;
		_matchedComplexities.insert(TimeComplexity::CUBIC);
	}

	// ----------------------------------------------------------------------------------------

	//  currently commented out because it generates false positives
	/*

	std::cout << "Testing if time complexity could be exponential..." << std::endl;


	// t = c^n
	// t^(1/n) = c (t and n are both >0)
	// nt^(1/n) = cn

	// transform recorded data by nth-rooting it then multiplying it by n
	DataSet exponentialCompensatedData;
	for(std::pair<uint64_t, uint64_t> const & point : *_recordedData)
	{
		exponentialCompensatedData.emplace_back(point.first, static_cast<double>(point.first) * pow(static_cast<double>(point.second), 1/static_cast<double>(point.first)));
	}

	LinearityConclusion exponentialConclusion = isLinear(exponentialCompensatedData);

	if(exponentialConclusion._isLinear && exponentialConclusion._regressionSlope >= POSITIVE_REGRESSION_SLOPE)
	{
		std::cout << ">> Time complexity of " << _snippetName << " might be exponential" << std::endl;
		_matchedComplexities.insert(TimeComplexity::EXPONENTIAL);
	}
	*/

}

bool RuntimeEvaluator::meetsComplexity(TimeComplexity complexity)
{
	// iterate backwards through the complexities smaller than or equl to the given complexity
	for(TimeComplexity checkingComplexity = complexity;
			static_cast<uint8_t>(checkingComplexity) >= static_cast<uint8_t>(TimeComplexity::CONSTANT);
			checkingComplexity = static_cast<TimeComplexity>(static_cast<uint8_t>(checkingComplexity) - 1))
	{
		if(_matchedComplexities.find(checkingComplexity) != _matchedComplexities.end())
		{
			return true;
		}
	}

	return false;
}


