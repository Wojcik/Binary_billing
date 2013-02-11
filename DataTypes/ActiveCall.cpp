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
	possibleSeconds = abonent->getData()->getPossibleSeconds(isHomeNetwork(), isWeekEnd());
	if (possibleSeconds <= 0 || possibleSeconds < value)
	{
		printf("abonent %s can speak only for %d minutes (%d seconds)\n", abonent->getData()->getName().c_str(), static_cast<int>(possibleSeconds/60), possibleSeconds);
		duration = 0;
		status = NOT_ENOUGH_MONEY;
		abonent->endCall();
		return false;
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
