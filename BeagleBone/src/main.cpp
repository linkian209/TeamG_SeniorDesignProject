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
	userThread.startThread();
	videoThread.startThread();

	while(!userThread.isStopped() && !videoThread.isStopped());

	return 0;
}
