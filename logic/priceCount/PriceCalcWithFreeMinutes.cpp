#include "PriceCalcWithFreeMinutes.h"
#include "..\..\DataTypes\ActiveCall.h"
#include "..\..\DataTypes\Abonent.h"
#include "..\..\DataTypes\AbonentData.h"


float PriceCalcWithFreeMinutes::getPriceForCall( ActiveCall* callInfo , unsigned duration )
{
	if (callInfo->getIsHomeNetwork())
	{
		AbonentData* abonent = callInfo->getAbonent()->getData();
		int totalMinutes = static_cast<unsigned>(ceil(duration/60.0f));
		unsigned freeMinutes = abonent->getFreeMinutes();
		// minus free minutes
		duration = std::max(static_cast<float>(totalMinutes - freeMinutes), 0.0f);
		abonent->setFreeMinutes(std::max(static_cast<float>(freeMinutes - totalMinutes), 0.0f));
	}
	return m_calculator->getPriceForCall(callInfo, duration);
}

