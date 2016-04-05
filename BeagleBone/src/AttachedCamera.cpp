#include "AttachedCamera.hpp"
#include "BluetoothManager.hpp"

AttachedCamera::AttachedCamera()
{

}

AttachedCamera::~AttachedCamera()
{

}

void AttachedCamera::test()
{
	std::cout << "Successfully accessed Attached Camera!" << std::endl;
}

bool AttachedCamera::takePicture()
{
	// Take the picture
	std::string cmd = "gphoto2 --capture-image-and-download --filename \'capture.jpg\' --keep";

	int ret = system(cmd.c_str());
	if(ret != 0)
	{
		return false;
	}

	// Send picture to app
	while(!BTMgr().Lock());
	bool retval = BTMgr().sendPicture();
	BTMgr().Unlock();

	system("rm capture.jpg");

	return retval;
}
