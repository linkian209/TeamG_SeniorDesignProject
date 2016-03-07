#include "PWMManager.hpp"
#include <iostream>

PWMManager::PWMManager() :
m_pitch(BlackLib::P8_13),
m_yaw(BlackLib::P9_22),
m_pitchFB(BlackLib::AIN4),
m_yawFB(BlackLib::AIN6)
{
	// Set up duty
	m_pitch.setPeriodTime(20,BlackLib::milisecond);
	m_yaw.setPeriodTime(20,BlackLib::milisecond);
	std::cout << "Period of Yaw: " << m_yaw.getPeriodValue() << "ns\n"; 
	std::cout << "Period of Pitch: " << m_pitch.getPeriodValue() << "ns\n";
	m_pitch.setPolarity(BlackLib::straight);
	m_yaw.setPolarity(BlackLib::straight);
	setPitch(DEFAULT_PITCH);
	setYaw(DEFAULT_YAW);

}

PWMManager::~PWMManager()
{

}

void PWMManager::test()
{
	std::cout << "PWMManager: OK!\n";
}

bool PWMManager::setPitch(float angle)
{
	float newPitch = 100 - ((angle / 180) * m_dutySpan + m_dutyMin);
	m_currentPitch = newPitch;
	bool retval = m_pitch.setDutyPercent(newPitch);
	return retval;
}

bool PWMManager::setYaw(float angle)
{
	float newYaw = 100 - ((angle / 180) * m_dutySpan + m_dutyMin);
	m_currentYaw = newYaw;
	bool retval = m_yaw.setDutyPercent(newYaw);
	return retval;
}

float PWMManager::getCurrentPitch()
{
	return m_currentPitch;
}

float PWMManager::getCurrentYaw()
{
	return m_currentYaw;
}
