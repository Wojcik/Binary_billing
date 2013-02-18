#ifndef CALLS_MANAGER
#define CALLS_MANAGER

#include <string>

class ActiveCall;
class Abonent;
class BalanceController;

class CallsManager
{
public:
	CallsManager(void);
	~CallsManager(void);

	//start session
	void addCall(Abonent* _abonent, std::string number);
	//session was ended by abonent or aborted by system
	void endCall(unsigned duration);

	ActiveCall* GetActiveCall() {return this->activeCall;};

private:
	BalanceController* balanceController;
	//current abonent call
	ActiveCall* activeCall;
	bool isHomeNetwork();
	bool isWeekend();
};
#endif

