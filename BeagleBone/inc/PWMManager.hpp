/*************************
* BeagleBone PWM Manager *
* Author: Ian Drake      *
* Copyright: 2016        *
*************************/
#ifndef PWMMANAGER__HPP
#define PWMMANAGER__HPP

#include "BlackPWM.h"
#include "BlackADC.h"

// Constants
const int DEFAULT_PITCH = 65.0;
const int DEFAULT_YAW 	= 83.0;

const int MAX_PITCH 	= 86.0;
const int MAX_YAW 	= 170.0;

const int MIN_PITCH 	= 39.0;
const int MIN_YAW	= 11.0;

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
		float getCurrentPitch();
		bool setYaw(float angle);
		float getCurrentYaw();

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
		BlackLib::BlackADC m_pitchFB;
		BlackLib::BlackADC m_yawFB;
		// Member Variables
		float m_currentPitch 	= 0;	// Current Angle of Pitch
		float m_currentYaw	= 0;	// Current Angle of Yaw
		// Duty Cycle Calculation variables
		float m_dutyMin = 2.00;
		float m_dutyMax = 9.00;
		float m_dutySpan = 11.00;
		float m_yawDefault = 92.5;
};

// Declare the friend function
PWMManager& PWMMgr();

#endif
