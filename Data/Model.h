#ifndef MODEL
#define MODEL

#include <map>
#include "../DataTypes/AbonentData.h"


//handle data
class AbonentsModel
{
public:

	//singleton
	static AbonentsModel* getInstance() {
		static AbonentsModel instance;
		return &instance;
	}  
	//load data
	bool		init();
	//print all registered users
	void		printAbonents();

	//returns abonent with given id
	AbonentData* getAbonentWithId(int id);

	~AbonentsModel();

private:        

	//private constructors
	AbonentsModel(){};
	AbonentsModel(const AbonentsModel& root); 
	AbonentsModel& operator=(const AbonentsModel&);

	//data from DB
	std::map <unsigned, AbonentData*> abonents;	//info about registered abonents
};
#endif
