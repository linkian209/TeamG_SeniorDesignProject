#include <iostream>
#include "PWMManager.hpp"
#include "AttachedCamera.hpp"
#include "BluetoothManager.hpp"
#include "UserThread.hpp"
#include "VideoThread.hpp"

using namespace std;

int main()
{
	// Initialize Singletons
	PWMMgr().test();
	BTMgr().test();
	AttCam().test();
	
	// Initialize Threads
	UserThread userThread;
	VideoThread videoThread;
	testThread.startThread();
	testThread2.startThread();
	
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

	// UART Test
	do
	{
		cout << (BTMgr().sendString("Yosh!") ? "True!" : "False!") << endl;
		BTMgr().readString();
		sleep(1);
	}while(true);

	return 0;
}
