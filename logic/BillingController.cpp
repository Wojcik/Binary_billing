#include <iomanip>
#include <sstream>
#include <iostream>
#include <ctime>
#include <conio.h>

#include "BillingController.h"
#include "Abonent.h"
#include "..\DataTypes\AbonentData.h"
#include "Model.h"
#include "Utils.h"

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
		// get user data for start session
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

		//get phone to call -----------------------------------------------------------------
		cin.clear();
		cin.ignore( numeric_limits<streamsize>::max(), '\n');
		std::string number;

		while (true) 
		{
			cout << "Enter phone number to call (10 symbols, only digits)" << endl;
			getline(cin, number);

			if (number.length() == 10 && Utils::is_digits(number)) {
				break;
			}

			cout << "Invalid number, must contains only digits and  ==10 symbols length" << endl;
		}
		//-----------------------------------------------------------------------------------
		abonent = new Abonent(data);
		ActiveCall* activeCall = new ActiveCall(abonent , number);
		abonent->startCall(activeCall);

		unsigned duration = 0;

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

		//if abonent can speak for this long
		if (abonent->GetActiveCall()->setDuration(duration))
			abonent->hungUp();

		delete abonent;
		delete activeCall;
		cin.clear();
		cin.ignore( numeric_limits<streamsize>::max(), '\n');
		printf("To exit type 0\n or any digit for continue");
		cin >> running;
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
