#ifndef UTILS
#define UTILS

#include "..\Imported\cJSON.h"
#include <string>
#include <utility>

template<class A, class B>
struct DeleteMap
{
	bool operator()( std::pair<A,B> &x) const
	{
		delete x.second;
		return true;
	}
};

namespace Utils
{
	//get json file with give name
	cJSON* getJson(std::string name);
	bool is_digits(const std::string &str);
}
#endif