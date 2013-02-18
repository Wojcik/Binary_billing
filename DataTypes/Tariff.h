#include <string>
#ifndef TARIFF
#define TARIFF

struct cJSON;

class Tariff
{
public:
	Tariff(cJSON* _data);
	~Tariff(void);

	//getters for private data
	unsigned	getId() const { return id; };
	std::string getName() const { return name; };
	unsigned	getFreeMinutesPeriod() const {return freeMinutesPeriod;};
	unsigned	getFixedFreeMinutes() const {return freeMinutes;};
	float		getConnectionFee() const { return connectionFee; };
	float		getMinutePrice ( bool callInsideHome ) const;
	unsigned	getWeekendFreeMinutes()  const {return weekendFreeMinutes;};
private:
	unsigned	id;
	std::string name;
	unsigned	weekendFreeMinutes;			//if user call in weekend this amount of minutes will be free
	unsigned	freeMinutes;				//free minutes given for freeMinutesPeriod
	unsigned	freeMinutesPeriod;			//add freeMinutes for this period when user recharge balance
	float		homeMinutePrice;			//price for call inside home network
	float		othersMinutePrice;			//price for call to others operators

	float		connectionFee;				//fixed pay when connection was established
};
#endif

