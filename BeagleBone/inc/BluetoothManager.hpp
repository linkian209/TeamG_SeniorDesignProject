/***************************
 * Bluetooth Manager Class *
 * Author: Ian Drake       *
 * Copyright: 2016         *
 ***************************/
#ifndef BLUETOOTHMANAGER__HPP
#define BLUETOOTHMANAGER__HPP

#include "BlackUART.h"
#include <queue>
#include <mutex>
#include <string>
#include <thread>

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
		bool sendString(char* message);
		std::string readString();

		// Thread Functions
		void startThread();
		void stopThread();
		bool ThreadMain();

	private:
		// Constructor and Destructor
		BluetoothManager();
		~BluetoothManager();

		// UART Member
		BlackLib::BlackUART m_UART;
		int m_uartFD = -1;

		// Queue of Packets and thread to fill it
		std::queue<std::string> packets;
		bool m_newPackets = false;
		bool checkPackets();
		std::thread m_thread;
		bool m_stopThread = false;
};

// Declare Singleton Access Function
BluetoothManager& BTMgr();

#endif
