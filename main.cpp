
#include "logic/Model.h"
#include "logic/BillingController.h"

#define _CRT_SECURE_NO_DEPRECATE // disable annoying warning in utils::getJson for fopen func

using namespace std;

int main (int argc, char* argv[])
{
	//init model singleton
	Model* model = Model::getInstance();
	
	//all data was loaded successfully
	if (model->init())
	{
		BillingController* controller = new BillingController();
		controller->init();
	}

	return 0;
}
