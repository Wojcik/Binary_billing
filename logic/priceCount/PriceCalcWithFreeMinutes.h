
#ifndef FREE_MINUTES_PRICE
#define FREE_MINUTES_PRICE

#include <memory>

#include "IPriceCalculator.h"

class ActiveCall;

class PriceCalcWithFreeMinutes : public IPriceCalculator
{
public:
	PriceCalcWithFreeMinutes ( IPriceCalculator* calculator): m_calculator(calculator){};
	virtual float getPriceForCall(ActiveCall* call, unsigned duration);
	virtual ~PriceCalcWithFreeMinutes(void) {};
private:
	std::auto_ptr<IPriceCalculator> m_calculator;
};

#endif

