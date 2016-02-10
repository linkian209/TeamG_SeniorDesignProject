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

	private:
		// Constructor and Destructor
		BluetoothManager();
		~BluetoothManager();
};

// Declare Singleton Access Function
BluetoothManager& BTMgr();

#endif
