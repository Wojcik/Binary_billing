#ifndef ABONENT
#define ABONENT


#include "../DataTypes/AbonentData.h"
#include "../DataTypes/ActiveCall.h"


class Abonent
{
public:
	Abonent(AbonentData* _data);
	~Abonent();

	AbonentData* getData() const {return this->data;};
	ActiveCall* GetActiveCall() {return this->activeCall;};

	//start session
	bool startCall(ActiveCall* _activeCall);
	//session was ended by abonent or aborted by system
	void endCall();
	//session was ended by abonent
	void hungUp();
	
	//add money to balance
	bool recharge(unsigned _rechargeValue);
private:
	//info from database
	AbonentData* data;
	//current abonent call
	ActiveCall* activeCall;
};
#endif
