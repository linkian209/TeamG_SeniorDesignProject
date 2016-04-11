#include "PWMManager.hpp"
#include <iostream>
#include <chrono>
#include <thread>

PWMManager::PWMManager() :
m_pitch(BlackLib::P8_13),
m_yaw(BlackLib::P9_22),
m_pitchFB(BlackLib::AIN4),
m_yawFB(BlackLib::AIN6)
{
	// Set up duty
	m_pitch.setPeriodTime(20,BlackLib::milisecond);
	m_yaw.setPeriodTime(20,BlackLib::milisecond);
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
	setYaw(MIN_YAW);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	setYaw(MAX_YAW);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	setYaw(DEFAULT_YAW);
	setPitch(MIN_PITCH);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	setPitch(MAX_PITCH);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	setPitch(DEFAULT_PITCH);
	std::cout << "PWMManager: OK!" << std::endl;
}

bool PWMManager::setPitch(float angle)
{
	if(angle > MAX_PITCH || angle < MIN_PITCH)
	{
		angle = (angle > MAX_PITCH ? MAX_PITCH : MIN_PITCH);
	}

	float newPitch = 100 - ((angle / 180) * m_dutySpan + m_dutyMin);
	m_currentPitch = newPitch;
	bool retval = m_pitch.setDutyPercent(newPitch);
	return retval;
}

bool PWMManager::setYaw(float angle)
{
	if(angle > MAX_YAW || angle < MIN_YAW)
	{
		angle = (angle > MAX_YAW ? MAX_YAW : MIN_YAW);
	}

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
