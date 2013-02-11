#include "Model.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "..\Imported\cJSON.h"
#include "Utils.h"

typedef std::map<unsigned, AbonentData*>::const_iterator userIterator_t;

bool Model::init()
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
		connectionFee =  static_cast<float>(cJSON_GetObjectItem(item,"connection_fee")->valuedouble);
		freeMinutes =  cJSON_GetObjectItem(item,"free_talk_minutes")->valueint;
		freeMinutesPeriod =  cJSON_GetObjectItem(item,"free_talk_minutes_period")->valueint;
		homeMinutePrice =  static_cast<float>(cJSON_GetObjectItem(item,"minute_cost_home")->valuedouble);
		othersMinutePrice =  static_cast<float>(cJSON_GetObjectItem(item,"minute_cost_others")->valuedouble);
		weekendFreeMinutes =  cJSON_GetObjectItem(item,"weekend_free_minutes")->valueint;

		for (cJSON *pref_json = cJSON_GetObjectItem(item,"home_network_prefixes")->child; pref_json; pref_json = pref_json->next)
		{
			homeNetworkCodes.push_back(pref_json->valuestring);
		}
	}
	cJSON_Delete(json);

	cJSON *usersJson = Utils::getJson("DataFiles/users.json");
	if (!usersJson)
	{
		printf("Users cannot be opened\n");
		return false;
	}

	for (cJSON *user = usersJson->child; user; user = user->next)
	{
		unsigned id =  cJSON_GetObjectItem(user,"id")->valueint;
		std::string name =  cJSON_GetObjectItem(user,"name")->valuestring;
		float balance =  static_cast<float>(cJSON_GetObjectItem(user,"balance")->valuedouble);
		bool banned =  !!cJSON_GetObjectItem(user,"banned")->valueint;
		unsigned lastRechargeTime =  cJSON_GetObjectItem(user,"lastRechargeTime")->valueint;
		unsigned freeMinutes =  cJSON_GetObjectItem(user,"freeMinutes")->valueint;
		//TODO add parsing callsHistory
		AbonentData* data = new AbonentData(id, name, balance, lastRechargeTime, freeMinutes, banned);
		abonents[id] = data;
	}
	cJSON_Delete(usersJson);

	return true;
}

AbonentData* Model::getAbonentWithId( int id )
{
	userIterator_t iter = abonents.find(id);
	if (iter != abonents.end())
		return iter->second;
	else
	{
		printf("wrong id\n");
		return NULL;
	}
	
}

void Model::printAbonents()
{
	for (userIterator_t iter = abonents.begin(); iter!= abonents.end(); iter++ )
	{
		printf("\nId - %d, Name: %s, Balance = %f, FreeMinutes = %d\n", iter->first, iter->second->getName().c_str(), iter->second->getBalance(), iter->second->getFreeMinutes());
		printf("--------------------------------------------------------------------\n");
	}
}

float Model::getMinutePrice( bool callInsideHome ) const
{
	return callInsideHome?homeMinutePrice:othersMinutePrice;
}
