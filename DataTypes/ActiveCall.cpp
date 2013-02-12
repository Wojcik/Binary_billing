#include "ActiveCall.h"
#include <ctime>
#include "..\logic\Abonent.h"
#include "..\logic\Model.h"
#include <string>
#include <vector>

ActiveCall::ActiveCall(Abonent* _abonent, std::string number)
{
	abonent = _abonent;
	object_number = number;
	duration = 0;
	status = NONE;
}

//primitive checking if call inside home network
//TODO make with regexp
bool ActiveCall::isHomeNetwork()
{
	const std::vector<std::string>* networkCodes = Model::getInstance()->getHomeNetworkCodes();
	bool isHome = false;
	for (std::vector<std::string>::const_iterator iter = networkCodes->begin(); iter != networkCodes->end(); iter ++)
	{
		unsigned mm = object_number.find((*iter));
		isHome |=  !mm;
	}
	return isHome;
}

bool ActiveCall::startCall()
{
	status = START_DIAL;
	callDate = time(NULL);
	return true;
}

bool ActiveCall::setDuration( unsigned value )
{
	bool _isHomeNetwork = isHomeNetwork();
	bool _isWeekEnd = isWeekEnd();
	printf("--------Try start %sinside home network. Now %sweekend---------\n",(_isHomeNetwork ?"": "NOT "), (_isWeekEnd?"": "NOT "));
	possibleSeconds = abonent->getData()->getPossibleSeconds(_isHomeNetwork, _isWeekEnd);
	if (possibleSeconds <= 0 || possibleSeconds < value)
	{
		printf("abonent %s can speak only for %d minutes (%d seconds)\n", abonent->getData()->getName().c_str(), static_cast<int>(possibleSeconds/60), possibleSeconds);
		duration = 0;
		status = NOT_ENOUGH_MONEY;
		abonent->endCall();
		return false;
	}
	//if abonent speaks too much
	else if (value > Model::MAX_SESSION_LENGTH)
	{
		//update conversation time for system limits
		value = Model::MAX_SESSION_LENGTH;
		printf("Too long session. Session will be aborted after %d minutes because of system limits\n" , Model::MAX_SESSION_LENGTH/60);
	}
	duration = value;
	return true;
}

void ActiveCall::endCall()
{
	status = FINISHED;
	abonent->endCall();
}

void ActiveCall::setStatus( CALL_STATUS _status )
{
	status = _status;
}

bool ActiveCall::isWeekEnd()
{
	struct tm *timeval;
	time_t tt;
	tt = time( NULL );
	timeval = localtime( &tt );
	// print zero based day of week
	return timeval->tm_wday == 0 || timeval->tm_wday == 6;
}

ActiveCall::~ActiveCall()
{

}
