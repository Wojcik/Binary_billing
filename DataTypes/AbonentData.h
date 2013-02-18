#ifndef ABONENT_DATA
#define ABONENT_DATA

#include <string>
#include <vector>
#include <assert.h>

class Tariff;
class ActiveCall;

class AbonentData
{
private:
	unsigned	id;
	//abonent name
	std::string name;
	// active user tariff
	std::string currentTariff;
	//current abonent balance
	float		balance;
	//abonent was banned for some reason
	bool		banned;
	//last time when balance was recharged
	unsigned	lastRechargeTime;
	//bonus for recharge
	unsigned	freeMinutes;
	std::vector<ActiveCall*> callsHistory;
public:
	AbonentData(unsigned _id , std::string _name, std::string tariff, float _balance, int _lastRechargeTime, int _freeMinutes, bool _banned );
	~AbonentData();
	std::string getName() const {return name;};
	float getBalance() const {return balance;};
	void setBalance(float value) {balance = value;};

	//when abonent add money to balance
	void AddCosts( unsigned _rechargeValue );
	unsigned getLastRechargeTime() const { return lastRechargeTime; };
	std::string getCurrentTariff() const { return currentTariff; };
	void	setCurrentTariff(std::string val) {assert(val.length()); currentTariff = val; };

	unsigned getFreeMinutes();
	void	setFreeMinutes(unsigned val) { freeMinutes = val; };
};
#endif


