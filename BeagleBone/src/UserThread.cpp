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
		while(!BTMgr().checkPackets());

		while(BTMgr().checkPackets())
		{
			// Decode Packet
			std::string pack = BTMgr().readString();
			PacketType type = decodePacket(pack);

			switch(type)
			{
				case PWMPacket:
					decodePWMPacket(pack);
					break;
				case CameraPacket:
					decodeCameraPacket(pack);
					break;
				case BadPacket:
					// Ignore this Packet
					continue;
				default:
					// What????
					continue;
			}
			// Create Response
			
			// Send packet
			while(!BTMgr().Lock());
			// Send it
			BTMgr().Unlock();
		}
	}

	return true;
}

bool UserThread::isStopped()
{
	return m_stopThread;
}

PacketType UserThread::decodePacket(std::string packet)
{
	std::size_t found = packet.find("%PWM");

	// PWM Packet
	if(found != std::string::npos)
	{
		return PacketType::PWMPacket;
	}

	found = packet.find("%CAMERA");

	// Camera Packet
	if(found != std::string:npos)
	{
		return PacketType::CameraPacket;
	}

	// Else return bad packet
	return PacketType::BadPacket;
}

bool UserThread::decodePWMPacket(std::string packet)
{
	std::size_t pitch = packet.find("%PITCH");

	if(
}

bool UserThread::decodeCameraPacket(std::string packet)
{

}
