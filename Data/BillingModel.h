#ifndef BILLING_MODEL
#define BILLING_MODEL

#include <map>
#include "../DataTypes/AbonentData.h"


//handle data
class BillingModel
{
public:

	//singleton
	static BillingModel* getInstance() {
		static BillingModel instance;
		return &instance;
	}  
	//load data
	bool		init();
	//print all registered users

	const	std::vector<std::string>* getHomeNetworkCodes() const {return &homeNetworkCodes;};
	Tariff* getTariffWithName(std::string name) const;
	~BillingModel();

private:        

	//private constructors
	BillingModel(){};
	BillingModel(const BillingModel& root); 
	BillingModel& operator=(const BillingModel&);

	std::vector<std::string> homeNetworkCodes;
	std::map<std::string, Tariff*> tariffs;
};
#endif
