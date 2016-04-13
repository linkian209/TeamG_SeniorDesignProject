#include "BluetoothManager.hpp"
#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <cstddef>
#include <termios.h>
#include <chrono>
#include <cstdlib>

BluetoothManager::BluetoothManager():
m_UART(BlackLib::UART5),
m_uartFD(m_UART.getFileDescriptor()),
packets(),
m_thread()
{
	// UART Setup
	m_UART.setParity(BlackLib::ParityOdd);
	m_UART.open(BlackLib::ReadWrite | BlackLib::NonBlock);
	m_UART.setBaudRate(BlackLib::Baud115200, BlackLib::output, BlackLib::ApplyNow);
	m_UART.setBaudRate(BlackLib::Baud115200, BlackLib::input, BlackLib::ApplyNow);	
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
	std::cout << "BluetoothManager: OK!" << std::endl;
}

bool BluetoothManager::sendString(std::string message)
{
	bool retval = m_UART.write(message);
	m_UART.flush(BlackLib::bothDirection);
	std::cout << message << "\b ";
	return retval;
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
			// Check and see if this is an ack packet
			std::size_t found = temp.find("ACK");
			if(found != std::string::npos)
			{
				std::cout << "Acked ";
				m_acked--;
			}
			else
			{
				std::cout << temp << std::endl;
				packets.push(temp);
				if(!m_newPackets)
				{
					m_newPackets = true;
				}
			}
			m_UART.flush(BlackLib::bothDirection);
		}
	}

	return true;
}

bool BluetoothManager::checkPackets()
{
	return m_newPackets;
}

bool BluetoothManager::sendPicture()
{
	// Open file
	std::ifstream photoFile;
	std::size_t size= 0;
	photoFile.open("capture.jpg", std::ios::in | std::ios::binary | std::ios::ate);

	// Calculate how many packets will be needed
	size = photoFile.tellg();
	int numPackets = size / 256;
	numPackets = (numPackets % 256 == 0) ? numPackets : numPackets + 1;

	//Let the app know how many packets are coming for the picture
	std::string temp = "$PACKETS";
	temp += std::to_string(numPackets);
	temp += "#\n";
	if(!sendString(temp))
	{
		std::cout << "Send failed!" << std::endl;
	}
	m_acked++;
	// Wait for the ack
	while(m_acked != 0);

	// Set pointer back to beginning
	photoFile.seekg(0, std::ios::beg);

	/*
	//for(int i = 0; i < numPackets; ++i)
	char c[257];
	int len;
	while((len = photoFile.readsome(c,256)) > 0)
	{
		// Create packet
		std::string pack = "<";

		std::cout << c << std::endl;
		pack += c;

		// Once we have all chars of the packet, add the end char and send
		pack += '>';
		pack += '\n';
		sendString(pack);
		std::this_thread::sleep_for(std::chrono::microseconds(500));
		m_acked++;
		// Make sure we have less than 5 unacked packets
		//while(m_acked > 5);
	}
	*/

	system("cat capture.jpg > /dev/ttyO5");

	sendString("$TRANSMISSION%DONE#\n");

}
