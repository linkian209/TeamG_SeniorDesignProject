/*************************
* BeagleBone PWM Manager *
* Author: Ian Drake      *
* Copyright: 2016        *
*************************/
#ifndef PWMMANAGER__HPP
#define PWMMANAGER__HPP

#include "BlackPWM.h"
#include "BlackGPIO.h"

class PWMManager
{
	public:
		// Return Singleton of PWMManager Class
		friend PWMManager& PWMMgr();
	private:
		// Constructor and Destructor
		PWMManager();
		~PWMManager();

		// PWM Modules
		BlackLib::BlackPWM pitch;	// up down
		BlackLib::BlackPWM yaw;		// left right
		int currentPitch = 0;	// Current Angle of Pitch
		int currentYaw	 = 0;	// Current Angle of Yaw

		// PWM functions
		void setPitch(int angle);
		void setYaw(int angle);
};

#endif
