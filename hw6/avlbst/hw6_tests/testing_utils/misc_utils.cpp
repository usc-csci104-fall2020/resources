#include "misc_utils.h"

#include <sys/resource.h>

#include <iostream>
#include <sstream>
#include <cstring>

std::string stackLimToString(rlim_t stackLimit)
{
	std::stringstream result;

	if(stackLimit == RLIM_INFINITY)
	{
		result << "infinity";
	}
	else
	{
		result << "0x" << std::hex << stackLimit;
	}

	return result.str();
}

void removeStackLimit()
{
	struct rlimit stack_limit = {};
	getrlimit(RLIMIT_STACK, &stack_limit);

	std::cout << "Stack size was " << stackLimToString(stack_limit.rlim_cur) << " bytes, setting it to the max of " << stackLimToString(stack_limit.rlim_max) << " bytes." << std::endl;

	stack_limit.rlim_cur = stack_limit.rlim_max;
	setrlimit(RLIMIT_STACK, &stack_limit);
}

void makeLowercase(std::string & toConvert)
{
	for(size_t index = 0; index < toConvert.length(); ++index)
	{
		toConvert[index] = (char)std::tolower(toConvert[index]);
	}
}

// from https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
std::vector<std::string> splitString(std::string str, std::string const & token)
{
	std::vector<std::string> result;
	while(!str.empty())
	{
		size_t index = str.find(token);

		if(index != std::string::npos)
		{
			result.push_back(str.substr(0,index));
			str = str.substr(index+token.size());
			if(str.size()==0)
			{
				result.push_back(str);
			}

		}
		else
		{
			result.push_back(str);
			str = "";
		}
	}
	return result;
}