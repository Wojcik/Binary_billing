#include "Tariff.h"
#include "..\Imported\cJSON.h"


Tariff::Tariff(cJSON* data)
{
	id = cJSON_GetObjectItem(data,"id")->valueint;
	name = data->string;
	connectionFee =  static_cast<float>(cJSON_GetObjectItem(data,"connection_fee")->valuedouble);
	freeMinutes =  cJSON_GetObjectItem(data,"free_talk_minutes")->valueint;
	freeMinutesPeriod =  cJSON_GetObjectItem(data,"free_talk_minutes_period")->valueint;
	homeMinutePrice =  static_cast<float>(cJSON_GetObjectItem(data,"minute_cost_home")->valuedouble);
	othersMinutePrice =  static_cast<float>(cJSON_GetObjectItem(data,"minute_cost_others")->valuedouble);
	weekendFreeMinutes =  cJSON_GetObjectItem(data,"weekend_free_minutes")->valueint;
}


float Tariff::getMinutePrice( bool callInsideHome ) const
{
	return callInsideHome?homeMinutePrice:othersMinutePrice;
}



Tariff::~Tariff(void)
{
}
