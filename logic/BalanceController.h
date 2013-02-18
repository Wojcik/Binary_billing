#ifndef BALANCE_CONTROLLER
#define BALANCE_CONTROLLER

class AbonentData;
class ActiveCall;

class BalanceController
{
public:

	void updateAbonentsBalance(ActiveCall* callInfo);
	BalanceController(void) {};
	~BalanceController(void) {};
private:
};

#endif