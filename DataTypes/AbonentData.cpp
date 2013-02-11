#include "AbonentData.h"
#include <ctime>
#include "..\logic\Model.h"


void AbonentData::AddCosts( unsigned _rechargeValue )
{
	this->balance += _rechargeValue;
	this->lastRechargeTime = static_cast<int>(time(NULL));
	freeMinutes = Model::getInstance()->getFixedFreeMinutes();
}

AbonentData::AbonentData(unsigned _id, std::string _name, float _balance, int _lastRechargeTime, int _freeMinutes, bool _banned ) 
	: id(_id), name(_name), 
	balance(_balance), lastRechargeTime(_lastRechargeTime), freeMinutes(_freeMinutes), banned(_banned)
{

}


void AbonentData::updateBalance( ActiveCall* activeCall )
{
	bool callInsideHome = activeCall->isHomeNetwork();
	float totalPrice = Model::getInstance()->getConnectionFee();
	unsigned totalMinutes = static_cast<unsigned>(ceil(activeCall->getDuration()/60.0f));
	freeMinutes = getFreeMinutes();

	//minus free weekend minutes
	if (activeCall->isWeekEnd())
	{
		totalMinutes -= Model::getInstance()->getWeekendFreeMinutes();
		if (totalMinutes < 0)
			totalMinutes = 0;
	}

	// if abonent calling inside home network
	if (callInsideHome && freeMinutes && totalMinutes)
	{
		// minus free minutes
		int tmp = totalMinutes - freeMinutes;
		if (tmp > 0)
		{
			totalMinutes = tmp;
			freeMinutes = 0;
		}
		else
		{
			freeMinutes -= totalMinutes;
			totalMinutes = 0;
		}
	}

	//if abonent has no free minutes or call outside home network
	if (totalMinutes)
	{
		totalPrice += totalMinutes* Model::getInstance()->getMinutePrice(callInsideHome);
	}

	this->balance -= totalPrice;
	if (balance < 0)
		balance = 0;
	activeCall->setPrice(totalPrice);
	callsHistory.push_back(activeCall);
	printf("\nTotal time = %d minutes, price = %g, %s balance after call = %g\n",static_cast<int>(ceil(activeCall->getDuration()/60.0f)),activeCall->getPrice(), this->getName().c_str(), this->balance);
}

int AbonentData::getFreeMinutes()
{
	//check if free minutes period was expired
	time_t currTime = time(NULL);

	if (freeMinutes && Model::getInstance()->getFreeMinutesPeriod() < (currTime - lastRechargeTime)/(86400))
		freeMinutes = 0;
	return freeMinutes;
}

unsigned AbonentData::getPossibleSeconds(bool isHomeNetwork, bool isWeekend)
{
	// abonent can speak for this long
	unsigned minutesToTalk = 0;
	if (balance <= 0)
		return 0;

	//at first get free seconds that abonent have
	minutesToTalk += getFreeMinutes();
	minutesToTalk += int(isWeekend)*Model::getInstance()->getWeekendFreeMinutes();


	float _balance = balance - Model::getInstance()->getConnectionFee();
	//no money for connection
	if (_balance <= 0)
		return 0;

	//abonent has no free minutes and can't speak even for 1 minute
	if (minutesToTalk == 0 && (_balance - Model::getInstance()->getMinutePrice(isHomeNetwork) <= 0) )
		return 0;

	//add possible minutes if abonent pays for it
	minutesToTalk += static_cast<int>(floor(_balance / Model::getInstance()->getMinutePrice(isHomeNetwork)));

	//total seconds
	return minutesToTalk*60;
}

