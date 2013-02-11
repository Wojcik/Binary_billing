#ifndef BILLING_CONTROLLER
#define BILLING_CONTROLLER

//controls user input and sessions
class BillingController
{
private:
	bool running;
public:
	BillingController();
	~BillingController();
	void init();
};
#endif
