#include "BluetoothManager.hpp"
#include <iostream>
#include <termios.h>

BluetoothManager::BluetoothManager():
m_UART(BlackLib::UART5) , 
m_uartFD(m_UART.getFileDescriptor())
{
	m_UART.open(BlackLib::ReadWrite | BlackLib::NonBlock);
	m_UART.setBaudRate(B115200,BlackLib::output,BlackLib::ApplyNow);
	m_UART.setBaudRate(B115200,BlackLib::input,BlackLib::ApplyNow);
	
	// Set Baud Rate
	termios tempProps;
	tcgetattr(m_uartFD,&tempProps);
	cfsetispeed(&tempProps, B115200);
	cfsetospeed(&tempProps, B115200);
	m_UART.flush(BlackLib::bothDirection);
}

BluetoothManager::~BluetoothManager()
{

}

void BluetoothManager::test()
{
	//std::cout << "Test Complete!\n";
	std::cout << m_UART.getPortName() << std::endl;
}

bool BluetoothManager::sendString(/*std::string*/char* message)
{
	return m_UART.write(message, sizeof(message));
}

bool BluetoothManager::readString()
{
	char buff[10];
	while(!m_UART.read(buff,sizeof(buff)));
	std::cout << buff << std::endl;
	m_UART.flush(BlackLib::bothDirection);
}
