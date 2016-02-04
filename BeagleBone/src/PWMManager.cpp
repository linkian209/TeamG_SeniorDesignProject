#include "PWMManager.hpp"
#include <iostream>

PWMManager::PWMManager() :
m_pitch(BlackLib::P9_14),
m_yaw(BlackLib::P9_16)
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
	if(!m_pitch)
	{
		
	}
}
