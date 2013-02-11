#include "Abonent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>


Abonent::Abonent(AbonentData* _data)
{
	assert(_data);
	this->data = _data;
	activeCall = NULL;
}

bool Abonent::startCall(ActiveCall* _activeCall)
{
	assert(_activeCall);
	printf("\n-------------------------------START_CALLING------------------------\n");
	printf("Abonent %s is start calling", data->getName().c_str());
	activeCall = _activeCall;
	return activeCall->startCall();
}

void Abonent::endCall()
{
	switch (activeCall->getStatus())
	{
	case FINISHED:
		printf("\nSession was ended\n");
		//TODO calc cost of call
		data->updateBalance(activeCall);
		break;
	case NOT_ENOUGH_MONEY:
		printf("\nPlease recharge balance. Yours balance = %f \n", data->getBalance());
		break;
	default:
		break;
	}
	printf("\n------------------------------END_CALLING---------------------------\n");
	activeCall = NULL;
}

//add money to the balance
bool Abonent::recharge( unsigned _rechargeValue )
{
	//add some error codes if recharge is not possible
	if (this->data->isBanned())
		return false;
	this->data->AddCosts(_rechargeValue);
	return true;
}

//session closed by abonent
void Abonent::hungUp()
{
	activeCall->setStatus(FINISHED);
	endCall();
}

Abonent::~Abonent()
{

}
