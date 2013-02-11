#ifndef UTILS
#define UTILS

#include "..\Imported\cJSON.h"
#include <string>

namespace Utils
{
	//get json file with give name
	cJSON* getJson(std::string name);
}
#endif