
#ifndef WEEKEND_PRICE
#define WEEKEND_PRICE

#include <memory>

#include "IPriceCalculator.h"

class ActiveCall;

class PriceCalcWeekend : public IPriceCalculator
{
public:
	PriceCalcWeekend ( IPriceCalculator* calculator): m_calculator(calculator){};
	virtual float getPriceForCall(ActiveCall* call, unsigned duration);
	virtual ~PriceCalcWeekend(void) {};
private:
	std::auto_ptr<IPriceCalculator> m_calculator;
};

#endif

