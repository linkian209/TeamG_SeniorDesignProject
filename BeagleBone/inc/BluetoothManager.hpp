/***************************
 * Bluetooth Manager Class *
 * Author: Ian Drake       *
 * Copyright: 2016         *
 ***************************/
#ifndef BLUETOOTHMANAGER__HPP
#define BLUETOOTHMANAGER__HPP

#include "BlackUART.h"
#include <mutex>

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
		bool sendString

	private:
		// Constructor and Destructor
		BluetoothManager();
		~BluetoothManager();

		// UART Member
		BlackLib::BlackUART m_UART;
};

// Declare Singleton Access Function
BluetoothManager& BTMgr();

#endif
