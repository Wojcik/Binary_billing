#include <iomanip>
#include <sstream>
#include <iostream>
#include <ctime>
#include <conio.h>

#include "BillingController.h"
#include "Abonent.h"
#include "..\DataTypes\AbonentData.h"
#include "Model.h"

BillingController::BillingController()
{
	running = false;
}


//main loop
void BillingController::init()
{
	using namespace std;

	Abonent* abonent;
	AbonentData* data;
	int id;
	running = true;
	//start input data
	while(running)
	{
		abonent = NULL;
		data = NULL;
		id = 0;
		Model::getInstance()->printAbonents();

		while(!data)
		{
			cout << "Enter abonent id who starts call" << endl;
			cin >> id;
			while (cin.fail()) 
			{
				if (cin.fail()) 
				{
					cin.clear();
					cin.ignore( numeric_limits<streamsize>::max(), '\n');
				}
				cout << "Input error!" << endl;
				cout << "Enter abonent id who to start call" <<endl;
				cin >> id;
			}

			data = Model::getInstance()->getAbonentWithId(id);
			if (!data)
				cout  << "No such abonent with id = " << id << endl;
		}

		abonent = new Abonent(data);
		ActiveCall* activeCall = new ActiveCall(abonent , "0508341916");
		abonent->startCall(activeCall);

		unsigned duration = 0;
		cin.ignore( numeric_limits<streamsize>::max(), '\n');
		cin.clear();

		printf("\nEnter duration of call (seconds)\n");
		cin >> duration;
		while (cin.fail()) 
		{
			if (cin.fail()) 
			{
				cin.clear();
				cin.ignore( numeric_limits<streamsize>::max(), '\n');
				duration = 0;
			}
			cout << "Wrong duration of call!\n";
			printf("\nEnter duration of call (seconds)\n");
			cin >> duration;
		}

		if (duration > Model::MAX_SESSION_LENGTH)
			duration = Model::MAX_SESSION_LENGTH;

		//if abonent can speak for this long
		if (abonent->GetActiveCall()->setDuration(duration))
			abonent->hungUp();

		delete abonent;
		delete activeCall;
		cin.clear();
		cin.ignore( numeric_limits<streamsize>::max(), '\n');
		printf("To exit type 0\n");
		cin>> running;
		if (running)
		{
			cout << string( 100, '\n' );
		}
	}
}

BillingController::~BillingController()
{
	//nothing to do here
}
