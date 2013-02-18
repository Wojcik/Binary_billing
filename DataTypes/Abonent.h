#ifndef ABONENT
#define ABONENT


#include "AbonentData.h"
#include "ActiveCall.h"

class Tariff;

class Abonent
{
public:
	Abonent(AbonentData* _data);
	~Abonent();

	AbonentData* getData() const {return this->data;};

	//set active users tariff
	void setCurrentTariff(std::string _curTariff);

	//add money to balance
	void recharge(unsigned _rechargeValue);
private:
	//info from database
	AbonentData* data;
};
#endif
