#include "EmbeddedCamera.hpp"
#include <fstream>

EmbeddedCamera::EmbeddedCamera() :
m_thread(),
m_Cam(false)
{

}

EmbeddedCamera::~EmbeddedCamera()
{
	// Stop Thread
	stopThread();
}

void EmbeddedCamera::test()
{
	int ret = system("ls /dev/ | grep video0");
	m_Cam = ret == 0 ? true : false;
	std::cout << "Embedded Camera: " << (m_Cam ? "OK!\n" : "NOT OK!\n");
}

void EmbeddedCamera::startThread()
{
	m_stopThread = false;
	m_thread = std::thread(&EmbeddedCamera::ThreadMain, this);
}

void EmbeddedCamera::stopThread()
{
	m_stopThread = true;
	if(m_thread.joinable())
	{
		m_thread.join();
	}
}

bool EmbeddedCamera::ThreadMain()
{
	m_threadRunning = true;

	system("ffmpeg -s 500x284 -f video4linux2 -i /dev/video0 -f mpeg1video -r 20 http://localhost:82/1234/500/284 &");
	
	while(!m_stopThread);

	// Kill stream
	system("ps aux | grep ffmpeg > out");

	std::ifstream file("out");

	std::string temp, last;
	while(file >> temp)
	{
		if(last == "root")
		{
			std::string cmd = "kill -9 " + temp + " &";
			system(const_cast<char*>(cmd.c_str()));
		}

		last = temp;
	}

	std::remove("out");

	return true;
}
