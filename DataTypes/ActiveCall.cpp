#include "ActiveCall.h"
#include "..\Data\AbonentsModel.h"
#include <string>
#include <vector>
#include "AbonentData.h"
#include "Abonent.h"

ActiveCall::ActiveCall(Abonent* _abonent, std::string number)
{
	abonent = _abonent;
	object_number = number;
	duration = 0;
	isHomeNetwork = false;
	isWeekEnd = false;
	status = DIAL;
}

void ActiveCall::startCall()
{
	callStartDate = time(NULL);
	status = STARTED;
}


void ActiveCall::setDuration( unsigned value )
{
	duration = value;
}

void ActiveCall::endCall(CALL_STATUS finishedWithStatus)
{
	status = finishedWithStatus;
	switch (status)
	{
	case DIAL:
		break;
	case STARTED:
		break;
	case FINISHED:
		printf("\nTotal time = %d minutes, price = %.2f, %s balance after call = %g, free minutes left %d\n",
			static_cast<int>(ceil(duration/60.0f)), 
			price, 
			abonent->getData()->getName().c_str(), 
			abonent->getData()->getBalance(), 
			abonent->getData()->getFreeMinutes());
		break;
	case TERMINATED:
		price = 0.0f;
		duration = 0;
		printf("\n Call terminated, not enough money");
		break;
	default:
		break;
	}
}

ActiveCall::~ActiveCall()
{

}
