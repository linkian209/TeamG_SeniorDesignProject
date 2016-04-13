#include <iostream>
#include "PWMManager.hpp"
#include "AttachedCamera.hpp"
#include "EmbeddedCamera.hpp"
#include "BluetoothManager.hpp"
#include "UserThread.hpp"
#include "VideoThread.hpp"

using namespace std;

int main()
{
	// Initialize Singletons
	BTMgr().test();
	AttCam().test();
	EmbCam().test();
	PWMMgr().test();

	// Initialize Threads
	UserThread userThread;
	VideoThread videoThread;
	userThread.startThread();
	videoThread.startThread();

	while(!userThread.isStopped() && !videoThread.isStopped());

	return 0;
}
