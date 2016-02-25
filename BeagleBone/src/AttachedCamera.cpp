#include "AttachedCamera.hpp"

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
	int ret = system("gphoto2 --capture-image");
	if(ret != 0)
	{
		return false;
	}

	return true;
}
