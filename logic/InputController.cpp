#include <iomanip>
#include <sstream>
#include <iostream>
#include <ctime>
#include <conio.h>

#include "InputController.h"
#include "..\DataTypes\Abonent.h"
#include "..\DataTypes\AbonentData.h"
#include "..\Data\Model.h"
#include "..\logic\Utils.h"
#include "..\logic\CallsManager.h"

InputController::InputController()
{
	running = false;
}


//main loop
void InputController::init()
{
	using namespace std;

	Abonent* abonent;
	AbonentData* data;
	CallsManager* callsManager = new CallsManager();
	int id;
	running = true;
	//start input data
	while(running)
	{
		abonent = NULL;
		data = NULL;
		id = 0;
		AbonentsModel::getInstance()->printAbonents();
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

			data = AbonentsModel::getInstance()->getAbonentWithId(id);
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
		callsManager->addCall(abonent, number);

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
		callsManager->endCall(duration);

		delete abonent;
		printf("To exit type 0. To continue type any other symbol");
		cin >> running;
		if (running)
		{
			cout << string( 100, '\n' );
		}
		cin.clear();
		cin.ignore( numeric_limits<streamsize>::max(), '\n');
	}
}

InputController::~InputController()
{
	//nothing to do here
}
