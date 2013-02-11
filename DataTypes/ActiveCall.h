#ifndef ACTIVE_CALL
#define ACTIVE_CALL

#include <string>

class Abonent;
enum CALL_STATUS
{
	NONE,
	START_DIAL,
	SPEAKING,
	NOT_ENOUGH_MONEY,
	FINISHED
};

class ActiveCall
{
public:
	ActiveCall(Abonent* _abonent, std::string number);
	~ActiveCall();
	bool startCall();
	void endCall();
	//set status of current session
	void		setStatus( CALL_STATUS status );
	CALL_STATUS getStatus() const {return status;};
	//true if call inside home network
	bool isHomeNetwork();
	//call start at weekend (Saturday or Sunday)
	bool isWeekEnd();
	//total duration of session
	unsigned	getDuration(bool inMinutes = false) const { return (inMinutes?static_cast<unsigned>(ceil(duration/60.0f)):duration); };
	bool		setDuration(unsigned value);
	
	float	getPrice() const {return price;};
	void	setPrice(float value) {price = value;};
private:
	Abonent*	abonent;
	std::string object_number;
	time_t		callDate;
	unsigned	duration;
	float		price;
	unsigned	possibleSeconds;
	CALL_STATUS status;
};
#endif
