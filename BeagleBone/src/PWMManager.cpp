#include "PWMManager.hpp"
#include <iostream>

PWMManager::PWMManager() :
m_pitch(BlackLib::P9_14),
m_yaw(BlackLib::P9_16),
m_pitchFB(BlackLib::AIN4),
m_yawFB(BlackLib::AIN6)
{
	std::cout << "Creating PWMManager.\n";
	// Set up duty
	m_pitch.setDutyPercent(100-m_dutyMin);
	m_yaw.setDutyPercent(100-m_dutyMin);
}

PWMManager::~PWMManager()
{
	std::cout << "Destroying PWMManager.\n";
}

void PWMManager::test()
{
	std::cout << "Successfully called the singleton!\n";
}

bool PWMManager::setPitch(float angle)
{
	float newPitch = 100 - ((angle / 180) * m_dutySpan + m_dutyMin);
	m_currentPitch = newPitch;
	return m_pitch.setDutyPercent(newPitch);
 
}

bool PWMManager::setYaw(float angle)
{
	float newYaw = 100 - ((angle / 180) * m_dutySpan + m_dutyMin);
	m_currentYaw = newYaw;
	return m_yaw.setDutyPercent(newYaw);
}

float PWMManager::getCurrentPitch()
{
	return m_currentPitch;
}

float PWMManager::getCurrentYaw()
{
	return m_currentYaw;
}
