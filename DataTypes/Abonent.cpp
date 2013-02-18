#include "Abonent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include "Tariff.h"


Abonent::Abonent(AbonentData* _data)
{
	assert(_data);
	this->data = _data;
}

void Abonent::setCurrentTariff( std::string _curTariff )
{
	data->setCurrentTariff(_curTariff);
}

//add money to the balance
void Abonent::recharge( unsigned _rechargeValue )
{
	this->data->AddCosts(_rechargeValue);
}

Abonent::~Abonent()
{

}
