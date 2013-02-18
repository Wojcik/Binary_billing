
#ifndef GNERAL_PRICE
#define GNERAL_PRICE

#include "IPriceCalculator.h"

class ActiveCall;

class GeneralPriceCalc : public IPriceCalculator
{
public:
	virtual float getPriceForCall(ActiveCall* call, unsigned duration);
	virtual ~GeneralPriceCalc(void) {};
private:

};

#endif

