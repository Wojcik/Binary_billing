#include "GeneralPriceCalc.h"
#include "..\..\DataTypes\Tariff.h"
#include "..\..\DataTypes\ActiveCall.h"
#include "..\..\DataTypes\AbonentData.h"
#include "..\..\Data\BillingModel.h"
#include "..\..\DataTypes\Abonent.h"

float GeneralPriceCalc::getPriceForCall( ActiveCall* callInfo, unsigned duration )
{
	AbonentData* abonent = callInfo->getAbonent()->getData();
	Tariff* abonentTariff = BillingModel::getInstance()->getTariffWithName(abonent->getCurrentTariff());
	assert(abonentTariff);

	float totalPrice = abonentTariff->getConnectionFee();

	int totalMinutes = static_cast<unsigned>(ceil(duration/60.0f));
	float minutePrice = abonentTariff->getMinutePrice(callInfo->getIsHomeNetwork());

	totalPrice += totalMinutes* minutePrice;

	return totalPrice;
}
