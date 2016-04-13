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
	std::cout << "AttachedCamera: OK!" << std::endl;
}

bool AttachedCamera::takePictureAndDownload()
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

bool AttachedCamera::takePicture()
{
	//Take the picture
	std::string cmd = "gphoto2 --capture-image";
	int ret = system(cmd.c_str());
	if(ret != 0)
	{
		return false;	
	}
	
	return true;
}
