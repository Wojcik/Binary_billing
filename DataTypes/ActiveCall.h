#ifndef ACTIVE_CALL
#define ACTIVE_CALL

#include <string>
#include <ctime>
#include "AbonentData.h"

class Abonent;

enum CALL_STATUS
{
	DIAL,
	STARTED,
	FINISHED,
	TERMINATED
};

class ActiveCall
{
public:
	ActiveCall(Abonent* _abonent, std::string number);
	~ActiveCall();
	void startCall();
	void endCall(CALL_STATUS finishedWithStatus);

	Abonent* getAbonent(){return abonent;};
	//total duration of session
	unsigned	getDuration(bool inMinutes = false) const { return (inMinutes?static_cast<unsigned>(ceil(duration/60.0f)):duration); };
	void		setDuration(unsigned value);
	
	float	getPrice() const {return price;};
	void	setPrice(float value) {price = value;};

	std::string getObjectNumber() const { return object_number; };


	bool getIsHomeNetwork() const { return isHomeNetwork; };
	void setIsHomeNetwork(bool val) { isHomeNetwork = val; };

	bool getIsWeekend() const { return isWeekEnd; };
	void setIsWeekEnd(bool val) { isWeekEnd = val; };
	time_t getCallStartDate() const { return callStartDate; };
private:
	Abonent*	abonent;
	std::string object_number;
	time_t		callStartDate;
	CALL_STATUS status;
	unsigned	duration;
	float		price;
	bool isHomeNetwork;
	bool isWeekEnd;
};
#endif
