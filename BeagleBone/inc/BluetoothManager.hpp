/***************************
 * Bluetooth Manager Class *
 * Author: Ian Drake       *
 * Copyright: 2016         *
 ***************************/
#ifndef BLUETOOTHMANAGER__HPP
#define BLUETOOTHMANAGER__HPP

#include "BlackUART.h"
#include <mutex>
#include <string>

class BluetoothManager
{
	public:
		// Singleton Access Function
		friend BluetoothManager& BTMgr()
		{
			static BluetoothManager theManager;
			return theManager;
		}

		// Mutex
		std::mutex lock;
		bool Lock() {return lock.try_lock();}
		void Unlock() {lock.unlock();}

		// Functions
		void test();
		bool sendString(/*std::string*/char* message);
		bool readString();

	private:
		// Constructor and Destructor
		BluetoothManager();
		~BluetoothManager();

		// UART Member
		BlackLib::BlackUART m_UART;
		int m_uartFD = -1;
};

// Declare Singleton Access Function
BluetoothManager& BTMgr();

#endif
