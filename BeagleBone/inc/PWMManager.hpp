/*************************
* BeagleBone PWM Manager *
* Author: Ian Drake      *
* Copyright: 2016        *
*************************/
#include "BlackPWM.h"

class PWMManager
{
	public:
		// Return Singleton of PWMManager Class
		friend PWMManager& getPWMMgr();
	private:
		// Constructor and Destructor
		PWMManager();
		~PWMManager();
};

// Get the Singleton
PWMManager& getPWMMgr()
{
	static PWMManager PWMMgr;
	return PWMMgr;
}
