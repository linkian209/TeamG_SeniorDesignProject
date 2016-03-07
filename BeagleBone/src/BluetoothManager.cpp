#include "BluetoothManager.hpp"
#include <iostream>
#include <termios.h>

BluetoothManager::BluetoothManager():
m_UART(BlackLib::UART5) , 
m_uartFD(m_UART.getFileDescriptor()),
packets(),
m_thread()
{
	// UART Setup
	m_UART.open(BlackLib::ReadWrite | BlackLib::NonBlock);
	m_UART.flush(BlackLib::bothDirection);
	// Thread Startup
	startThread();
}

BluetoothManager::~BluetoothManager()
{
	// Stop Thread
	stopThread();
}

void BluetoothManager::test()
{
	std::cout << m_UART.getPortName() << std::endl;
}

bool BluetoothManager::sendString(char* message)
{
	return m_UART.write(message, sizeof(message));
}

std::string BluetoothManager::readString()
{
	if(!packets.empty())
	{
		std::string retval = packets.front();
		packets.pop();
		if(packets.empty() && m_newPackets)
		{
			m_newPackets = false;
		}
		return retval;
	}

	return "";
}

void BluetoothManager::startThread()
{
	m_thread = std::thread(&BluetoothManager::ThreadMain,this);
}

void BluetoothManager::stopThread()
{
	m_stopThread = true;
	if(m_thread.joinable())
	{
		m_thread.join();
	}
}

bool BluetoothManager::ThreadMain()
{
	std::cout << "Reading UART line...\n";
	while(!m_stopThread)
	{
		std::string temp = m_UART.read();
		if(temp != BlackLib::UART_READ_FAILED)
		{
			packets.push(temp);
			if(!m_newPackets)
			{
				m_newPackets = true;
			}
		}
	}
}

bool BluetoothManager::checkPackets()
{
	return m_newPackets;
}
