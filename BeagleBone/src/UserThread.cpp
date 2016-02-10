#include "UserThread.hpp"
#include "BluetoothManager.hpp"
#include <iostream>
#include <thread>
#include <chrono>

UserThread::UserThread() : m_thread()
{

}

UserThread::~UserThread()
{

}

void UserThread::startThread()
{
	m_thread = std::thread(&UserThread::ThreadMain,this);
}

void UserThread::stopThread()
{
	m_stopThread = true;
	if(m_thread.joinable())
	{
		m_thread.join();
	}

}

bool UserThread::ThreadMain()
{
	while(!m_stopThread)
	{
		// Wait for a new packet

		// Decode Packet

		// Do packet thing

		// Create Response

		// Send packet
		while(!BTMgr().Lock());
		// Send it
		BTMgr().Unlock();
	}

	return true;
}
