#ifndef PRICE_CALCULATOR
#define PRICE_CALCULATOR

class ActiveCall;

class IPriceCalculator
{
public:
	virtual float getPriceForCall(ActiveCall* call, unsigned duration) = 0;
	virtual ~IPriceCalculator(void) {};
};

#endif

