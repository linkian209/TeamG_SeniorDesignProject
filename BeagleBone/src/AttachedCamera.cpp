#include "AttachedCamera.hpp"
#include "BluetoothManager.hpp"
#include <fstream>

AttachedCamera::AttachedCamera() :
m_thread()
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

	bool retval = true;

/*
	// Send picture to app
	while(!BTMgr().Lock());
	bool retval = BTMgr().sendPicture();
	BTMgr().Unlock();

	system("rm capture.jpg");
*/
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

void AttachedCamera::startThread()
{
	m_stopThread = false;
	m_thread = std::thread(&AttachedCamera::ThreadMain, this);
}

void AttachedCamera::stopThread()
{
	m_stopThread = true;
	if(m_thread.joinable())
	{
		m_thread.join();
	}

	m_threadRunning = false;
}

bool AttachedCamera::ThreadMain()
{
	m_threadRunning = true;
	std::cout << "Att Cam Thread running! " << m_threadRunning << std::endl;

	system("gphoto2 --capture-movie --stdout | ffmpeg -f mjpeg -i pipe:0 -f mpeg1video -r 20 http://localhost:82/1234/500/284 &");

	while(!m_stopThread);

	// Kill Stream
	system("ps aux | grep gphoto2 > out");

	std::ifstream file("out");
	std::string temp, last;

	while(file >> temp)
	{
		if(last == "root")
		{
			std::string cmd = "kill -9 "+ temp + " &";
			system(const_cast<char*>(cmd.c_str()));
		}

		last = temp;
	}

	file.close();

	std::remove("out");

	system("ps aux | grep ffmpeg > out");

	file.open("out");
	temp = "";
	last = "";

	while(file >> temp)
	{
		if(last == "root")
		{
			std::string cmd = "kill -9 "+ temp + " &";
			system(const_cast<char*>(cmd.c_str()));
		}

		last = temp;
	}

	file.close();
	std::remove("out");

	return true;
}
