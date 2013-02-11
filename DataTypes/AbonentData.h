#ifndef ABONENT_DATA
#define ABONENT_DATA

#include <string>
#include "ActiveCall.h"
#include <vector>

class AbonentData
{
private:
	unsigned	id;
	//abonent name
	std::string name;
	//current abonent balance
	float		balance;
	//abonent was banned for some reason
	bool		banned;
	//last time when balance was recharged
	unsigned	lastRechargeTime;
	//bonus for recharching
	unsigned	freeMinutes;
	
	std::vector<ActiveCall*> callsHistory;
public:
	AbonentData(unsigned _id , std::string _name, float _balance, int _lastRechargeTime, int _freeMinutes, bool _banned );
	~AbonentData();
	int getFreeMinutes();
	std::string getName() const {return name;};
	float getBalance() const {return balance;};
	void addToBalance(float value);
	bool isBanned() const {return banned;};
	void setBanned(bool _banned) {banned = _banned;};
	//when abonent add money to balance
	void AddCosts( unsigned _rechargeValue );
	void updateBalance( ActiveCall* activeCall );
	unsigned getPossibleSeconds(bool isHomeNetwork, bool isWeekend);
};
#endif


