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
	m_pitch.setPeriodTime(8,BlackLib::milisecond);
	m_yaw.setPeriodTime(8,BlackLib::milisecond);
	m_pitch.setPolarity(BlackLib::reverse);
	m_yaw.setPolarity(BlackLib::reverse);
	//m_pitch.setPolarity(BlackLib::straight);
	//m_yaw.setPolarity(BlackLib::straight);
	m_pitch.setDutyPercent(100-m_dutyMin);
	m_yaw.setDutyPercent(100-m_dutyMin);
	//m_pitch.setDutyPercent(m_dutyMin);
	//m_yaw.setDutyPercent(m_dutyMin);

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
	//float newPitch = angle;
	m_currentPitch = newPitch;
	bool retval = m_pitch.setDutyPercent(newPitch);
	std::cout << m_pitch.getValue() << std::endl;
	return retval;
}

bool PWMManager::setYaw(float angle)
{
	float newYaw = 100 - ((angle / 180) * m_dutySpan + m_dutyMin);
	//float newYaw = angle;
	m_currentYaw = newYaw;
	bool retval = m_yaw.setDutyPercent(newYaw);
	std::cout << m_yaw.getValue() << std::endl;
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
