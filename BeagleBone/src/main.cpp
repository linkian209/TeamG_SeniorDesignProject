#include <iostream>
#include "PWMManager.hpp"
#include "AttachedCamera.hpp"
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

	cout << "Getting Attached Camera Singleton..." << endl;
	AttCam().test();
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
	
	do
	{
		cout << "Setting to 0..." << endl;
		PWMMgr().setPitch(0);
		PWMMgr().setYaw(20);
		cout << "==========================" << endl;
		sleep(2);
		cout << "Setting to max..." << endl;
		PWMMgr().setPitch(90);
		PWMMgr().setYaw(90);
		cout << "==========================" << endl;
		sleep(2);
	}while(false);
	
	// Camera test
	cout << "Gphoto does " << (AttCam().takePicture() ? "" : "not ") << "work!\n";

	return 0;
}
