#include "AbonentData.h"
#include <ctime>

#include "Tariff.h"
#include "ActiveCall.h"
#include "..\Data\BillingModel.h"


void AbonentData::AddCosts( unsigned _rechargeValue )
{
	this->balance += _rechargeValue;
	this->lastRechargeTime = static_cast<int>(time(NULL));
	freeMinutes = BillingModel::getInstance()->getTariffWithName(currentTariff)->getFixedFreeMinutes();
}

AbonentData::AbonentData(unsigned _id, std::string _name, std::string tariff,float _balance, int _lastRechargeTime, int _freeMinutes, bool _banned ) 
	: id(_id), name(_name), currentTariff(tariff),
	balance(_balance), lastRechargeTime(_lastRechargeTime), freeMinutes(_freeMinutes), banned(_banned)
{
}

unsigned AbonentData::getFreeMinutes()
{
	//check if free minutes period was expired
	time_t currTime = time(NULL);
	//if free minutes period expired
	if (freeMinutes && BillingModel::getInstance()->getTariffWithName(currentTariff)->getFreeMinutesPeriod() < (currTime - lastRechargeTime)/(86400))
		freeMinutes = 0;
	return freeMinutes;
}

AbonentData::~AbonentData()
{

}


