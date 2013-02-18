#include <ctime>
#include <assert.h>

#include "CallsManager.h"
#include "BalanceController.h"

#include "..\DataTypes\ActiveCall.h"
#include "..\DataTypes\Abonent.h"
#include "..\Data\BillingModel.h"



CallsManager::CallsManager(void)
{
	balanceController = new BalanceController();
}

void CallsManager::addCall(Abonent* _abonent, std::string number)
{
	assert(_abonent);
	assert(number.length());
	printf("\n-------------------------------START_CALLING------------------------\n");
	printf("Abonent %s is start calling", _abonent->getData()->getName().c_str());
	activeCall = new ActiveCall(_abonent , number);
	activeCall->startCall();

	activeCall->setIsHomeNetwork(isHomeNetwork());
	activeCall->setIsWeekEnd(isWeekend());
}

void CallsManager::endCall(unsigned duration)
{
	activeCall->setDuration(duration);
	balanceController->updateAbonentsBalance(activeCall);
	activeCall->endCall(activeCall->getDuration() ==0 ?TERMINATED :FINISHED);
	printf("\n------------------------------END_CALLING---------------------------\n");
	delete activeCall;
	activeCall = NULL;
}

//primitive checking if call inside home network
//TODO make with regexp
bool CallsManager::isHomeNetwork()
{
	bool isHome = false;
	const std::vector<std::string>* networkCodes = BillingModel::getInstance()->getHomeNetworkCodes();
	for (std::vector<std::string>::const_iterator iter = networkCodes->begin(); iter != networkCodes->end(); iter ++)
	{
		unsigned mm = activeCall->getObjectNumber().find((*iter));
		isHome |=  !mm;
	}
	return isHome;
}

bool CallsManager::isWeekend()
{
	struct tm *timeval;
	time_t tt;
	tt = activeCall->getCallStartDate();
	timeval = localtime( &tt );
	return timeval->tm_wday == 0 || timeval->tm_wday == 6;
}

CallsManager::~CallsManager(void)
{
	delete balanceController;
}
