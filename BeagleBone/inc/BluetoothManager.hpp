/***************************
 * Bluetooth Manager Class *
 * Author: Ian Drake       *
 * Copyright: 2016         *
 ***************************/
#ifndef BLUETOOTHMANAGER__HPP
#define BLUETOOTHMANAGER__HPP

#include "BlackUART.h"

class BluetoothManager
{
	public:
		friend BluetoothManager& BTMgr()
		{
			static BluetoothManager theManager;
			return theManager;
		}

	private:
		// Constructor and Destructor
		BluetoothManager();
		~BluetoothManager();
};

// Declare Singleton Access Function
BluetoothManager& BTMgr();

#endif
