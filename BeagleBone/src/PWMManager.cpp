#include "PWMManager.hpp"

PWMManager::PWMManager() :
yaw(BlackLib::P9_14),
pitch(BlackLib::P9_16)
{

}

PWMManager::~PWMManager()
{

}

PWMManager& getPWMMgr()
{
	static PWMManager theManager;
	return theManager;
}
