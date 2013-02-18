#include "Model.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "..\Imported\cJSON.h"
#include "..\logic\Utils.h"
#include "..\DataTypes\Tariff.h"
#include <algorithm>

typedef std::map<unsigned, AbonentData*>::const_iterator abonentIterator_t;

bool AbonentsModel::init()
{
	//try to load all data

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
		std::string tariffName =  cJSON_GetObjectItem(user,"tariffName")->valuestring;
		float balance =  static_cast<float>(cJSON_GetObjectItem(user,"balance")->valuedouble);
		bool banned =  !!cJSON_GetObjectItem(user,"banned")->valueint;
		unsigned lastRechargeTime =  cJSON_GetObjectItem(user,"lastRechargeTime")->valueint;
		unsigned freeMinutes =  cJSON_GetObjectItem(user,"freeMinutes")->valueint;
		//TODO add parsing callsHistory
		AbonentData* data = new AbonentData(id, name, tariffName, balance, lastRechargeTime, freeMinutes, banned);
		abonents[id] = data;
	}
	cJSON_Delete(usersJson);

	return true;
}

AbonentData* AbonentsModel::getAbonentWithId( int id )
{
	abonentIterator_t iter = abonents.find(id);
	if (iter != abonents.end())
		return iter->second;
	else
	{
		printf("wrong id\n");
		return NULL;
	}
	
}

void AbonentsModel::printAbonents()
{
	for (abonentIterator_t iter = abonents.begin(); iter!= abonents.end(); iter++ )
	{
		printf("\nId - %d, Name: %s, Balance = %f, FreeMinutes = %d\n", iter->first, iter->second->getName().c_str(), iter->second->getBalance(), iter->second->getFreeMinutes());
		printf("--------------------------------------------------------------------\n");
	}
}

AbonentsModel::~AbonentsModel()
{
	for (abonentIterator_t iter = abonents.begin(); iter != abonents.end(); ++iter)
		delete iter->second;
	abonents.clear();
}