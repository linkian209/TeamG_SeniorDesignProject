#include <iostream>
#include "PWMManager.hpp"
#include "BluetoothManager.hpp"
#include "UserThread.hpp"
#include "VideoThread.hpp"

using namespace std;

int main()
{
	cout << "Getting PWM Singleton..." << endl;
	PWMMgr().test();
	cout << "Done!" << endl;

	cout << "Getting Bluetooth Singleton..." << endl;
	BTMgr().test();
	cout << "Done!" << endl;

	// Thread Test
	cout << "Staring Thread Test..." << endl;
	UserThread testThread;
	VideoThread testThread2;
	testThread.startThread();
	testThread2.startThread();
	sleep(10);
	testThread.stopThread();
	testThread2.stopThread();
	cout << "Thread Test End!" << endl;

	// PWM Test
	cout << "Starting PWM Test..." << endl;
	while(true)
	{
		cout << "Setting to 0..." << endl;
		PWMMgr().setPitch(0);
		PWMMgr().setYaw(0);
		cout << "==========================" << endl;
		sleep(2);
		cout << "Setting to max..." << endl;
		PWMMgr().setPitch(180);
		PWMMgr().setYaw(90);
		cout << "==========================" << endl;
		sleep(2);
	}
	
	return 0;
}
