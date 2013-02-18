#include "BillingModel.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include "..\Imported\cJSON.h"
#include "..\logic\Utils.h"
#include "..\DataTypes\Tariff.h"


typedef std::map<std::string, Tariff*>::const_iterator tariffIterator_t;

bool BillingModel::init()
{
	//try to load all data
	cJSON *json = Utils::getJson("DataFiles/settings.json");
	if (!json)
	{
		printf("Settings cannot be opened\n");
		return false;
	}

	for (cJSON *item = json->child; item; item = item->next)
	{

		for (cJSON *pref_json = cJSON_GetObjectItem(item,"tariffs")->child; pref_json; pref_json = pref_json->next)
		{
			Tariff* tariff = new Tariff(pref_json);
			tariffs[tariff->getName()] = tariff;
		}

		for (cJSON *pref_json = cJSON_GetObjectItem(item,"home_network_prefixes")->child; pref_json; pref_json = pref_json->next)
		{
			homeNetworkCodes.push_back(pref_json->valuestring);
		}
	}
	cJSON_Delete(json);

	return true;
}


BillingModel::~BillingModel()
{
	for (tariffIterator_t iter = tariffs.begin(); iter != tariffs.end(); ++iter)
		delete iter->second;
	tariffs.clear();
}

Tariff* BillingModel::getTariffWithName( std::string name ) const
{
	std::map<std::string, Tariff*>::const_iterator iter = tariffs.find(name);
	if (iter == tariffs.end())
	{
		printf("No tariff with name - %s", name.c_str());
		return NULL;
	}
	return iter->second;
}
