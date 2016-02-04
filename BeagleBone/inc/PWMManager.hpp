/*************************
* BeagleBone PWM Manager *
* Author: Ian Drake      *
* Copyright: 2016        *
*************************/
#ifndef PWMMANAGER__HPP
#define PWMMANAGER__HPP

#include "BlackPWM.h"
#include "BlackADC.h"

class PWMManager
{
	public:
		// Return Singleton of PWMManager Class
		friend PWMManager& PWMMgr()
		{
			static PWMManager theManager;
			return theManager;
		}
		
		// PWM functions
		bool setPitch(float angle);
		bool setYaw(float angle);

		// Test function
		void test();
	private:
		// Constructor and Destructor
		PWMManager();
		~PWMManager();

		// PWM Modules
		BlackLib::BlackPWM m_pitch;	// up down
		BlackLib::BlackPWM m_yaw;	// left right
		// ADC Feedback Pins
		BlackLib::BlackADC m_pitchFB
		BlackLib::BlackADC m_yawFB
		// Member Variables
		float currentPitch = 0;	// Current Angle of Pitch
		float currentYaw	 = 0;	// Current Angle of Yaw
		// Duty Cycle Calculation variables
		int m_dutyMin = 3;
		float m_dutySpan = 11.5;
};

// Declare the friend function
PWMManager& PWMMgr();

#endif
