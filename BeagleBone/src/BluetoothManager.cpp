#include "BluetoothManager.hpp"
#include <iostream>

BluetoothManager::BluetoothManager():
m_UART(BlackLib::UART5)
{
	m_UART.open(BlackLib::ReadWrite | BlackLib::NonBlock);
	m_UART.setBaudRate(BlackLib::Baud19200,BlackLib::output,BlackLib::ApplyNow);
	m_UART.setBaudRate(BlackLib::Baud19200,BlackLib::input,BlackLib::ApplyNow);
}

BluetoothManager::~BluetoothManager()
{

}

void BluetoothManager::test()
{
	std::cout << "Test Complete!\n";
}
