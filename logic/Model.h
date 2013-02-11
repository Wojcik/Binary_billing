#ifndef MODEL
#define MODEL

#include <map>
#include "../DataTypes/AbonentData.h"


//handle data
class Model
{
public:
	//user can speak for this long at one call
	static const unsigned MAX_SESSION_LENGTH = 3600; //seconds (1 hour)

	//singleton
	static Model* getInstance() {
		static Model instance;
		return &instance;
	}  
	//load data
	bool		init();
	//print all registered users
	void		printAbonents();

	//returns abonent with given id
	AbonentData* getAbonentWithId(int id);

	//getters for private data
	unsigned			getFreeMinutesPeriod() const {return freeMinutesPeriod;};
	unsigned			getFixedFreeMinutes() const {return freeMinutes;};
	float		getConnectionFee() const { return connectionFee; };
	float		getMinutePrice ( bool callInsideHome ) const;
	unsigned	getWeekendFreeMinutes()  const {return weekendFreeMinutes;};
	const		std::vector<std::string>* getHomeNetworkCodes() const {return &homeNetworkCodes;};
private:        

	//private constructors
	Model(){};
	Model(const Model& root);
	Model& operator=(const Model&);
	
	//data from DB
	std::map <unsigned, AbonentData*> abonents;	//info about registered abonents
	unsigned	weekendFreeMinutes;			//if user call in weekend this amount of minutes will be free
	unsigned	freeMinutes;				//free minutes given for freeMinutesPeriod
	unsigned	freeMinutesPeriod;			//add freeMinutes for this period when user recharge balance
	float		homeMinutePrice;			//price for call inside home network
	float		othersMinutePrice;			//price for call to others operators
	
	float		connectionFee;				//fixed pay when connection was established
	
	//codes for home network
	std::vector<std::string> homeNetworkCodes;
};
#endif
