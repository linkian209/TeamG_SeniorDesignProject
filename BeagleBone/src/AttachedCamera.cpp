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

	std::string rmv = "rm /www/pages/img/current" + std::to_string(m_currentPic) + ".jpg";
	system(const_cast<char*>(rmv.c_str()));
	std::string mv = "mv capture.jpg /www/pages/img/current" + std::to_string(++m_currentPic) + ".jpg";
	system(const_cast<char*>(mv.c_str()));
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

	system("gphoto2 --capture-movie --stdout | ffmpeg -f mjpeg -i pipe:0 -f mpeg1video -r 20 http://localhost:82/1234/320/240 > log.txt &");

	while(!m_stopThread);

	// Kill Stream
	system("ps aux | pgrep gphoto2 > out");

	std::ifstream file("out");
	std::string temp;

	while(file >> temp)
	{
		std::string cmd = "kill -9 "+ temp ;
		system(const_cast<char*>(cmd.c_str()));
	}

	file.close();

	std::remove("out");

	system("ps aux | pgrep ffmpeg > out");

	file.open("out");
	temp = "";

	while(file >> temp)
	{
		std::string cmd = "kill -9 "+ temp;
		system(const_cast<char*>(cmd.c_str()));
	}

	file.close();
	std::remove("out");

	return true;
}
