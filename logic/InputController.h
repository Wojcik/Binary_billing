#ifndef I_CONTROLLER
#define I_CONTROLLER

class CallsManager;
//controls user input
class InputController
{
private:
	bool running;
public:
	InputController();
	~InputController();
	void init();
};
#endif
