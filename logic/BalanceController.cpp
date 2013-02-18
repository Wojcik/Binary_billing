
#include <ctime>
#include <assert.h>

#include "BalanceController.h"
#include "..\Data\Model.h"
#include "..\Data\BillingModel.h"
#include "..\DataTypes\ActiveCall.h"
#include "..\DataTypes\AbonentData.h"
#include "..\DataTypes\Abonent.h"
#include "..\DataTypes\Tariff.h"
#include "priceCount\PriceCalcWeekend.h"
#include "priceCount\PriceCalcWithFreeMinutes.h"
#include "priceCount\GeneralPriceCalc.h"

void BalanceController::updateAbonentsBalance( ActiveCall* callInfo )
{
	printf("--------Try start %sinside home network. Now %sweekend---------\n",(callInfo->getIsHomeNetwork() ?"": "NOT "), (callInfo->getIsWeekend()?"": "NOT "));
	AbonentData* abonent = callInfo->getAbonent()->getData();

	//calc price
	PriceCalcWeekend calculator (new PriceCalcWithFreeMinutes(new GeneralPriceCalc()));
	float price = calculator.getPriceForCall(callInfo, callInfo->getDuration());
	if (price > abonent->getBalance())
	{
		callInfo->setDuration(0);
		callInfo->setPrice(0);
		return;
	}
	callInfo->setPrice(price);
	abonent->setBalance(std::max(abonent->getBalance() - price , 0.0f));
}