#include "Utils.h"
#include <stdio.h>

cJSON* Utils::getJson(std::string name)
{

	FILE *fIn = fopen(name.c_str(), "r");
	if(!fIn)
	{
		printf("Settings cannot be opened\n");
		return false;
	}

	// Load file contents
	fseek(fIn, 0, SEEK_END);
	unsigned size = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);
	char *data_f = new char[size + 1];
	fread(data_f, 1, size, fIn);
	// Close file
	fclose(fIn);

	if (!data_f)
		return NULL;
	return cJSON_Parse(data_f);
}

bool Utils::is_digits(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}