#include "PriceCalcWeekend.h"
#include "..\..\DataTypes\ActiveCall.h"
#include "..\..\DataTypes\Abonent.h"
#include "..\..\DataTypes\AbonentData.h"
#include "..\..\Data\BillingModel.h"
#include "..\..\DataTypes\Tariff.h"


float PriceCalcWeekend::getPriceForCall( ActiveCall* callInfo , unsigned duration )
{
	if (callInfo->getIsWeekend())
	{
		AbonentData* abonent = callInfo->getAbonent()->getData();
		Tariff* abonentTariff = BillingModel::getInstance()->getTariffWithName(abonent->getCurrentTariff());
		assert(abonentTariff);
		duration = std::max(static_cast<float>(duration - abonentTariff->getWeekendFreeMinutes()), 0.0f);
	}
	return m_calculator->getPriceForCall(callInfo, duration);
}

