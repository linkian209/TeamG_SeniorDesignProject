#include "VideoThread.hpp"
#include "BluetoothManager.hpp"
#include "AttachedCamera.hpp"
#include "EmbeddedCamera.hpp"
#include <iostream>
#include <chrono>

VideoThread::VideoThread() : m_thread()
{

}

VideoThread::~VideoThread()
{

}

void VideoThread::startThread()
{
	m_thread = std::thread(&VideoThread::ThreadMain,this);
}

void VideoThread::stopThread()
{
	m_stopThread = true;
	if(m_thread.joinable())
	{
		m_thread.join();
	}

}

bool VideoThread::ThreadMain()
{
	std::cout << "starting thread\n";
	while(!m_stopThread)
	{
		while(!AttCam().GoOrNo());

		while(!AttCam().Lock());
		m_useEmbedded = AttCam().useEmbedded();
		AttCam().Unlock();

		if(!m_useEmbedded)
		{
			std::cout << "Using Attached. AttCam: " << AttCam().isRunning() << std::endl;
			if(!AttCam().isRunning())
			{
				if(EmbCam().isRunning())
				{
					std::cout << "Stopping Embedded..." << std::endl;
					EmbCam().stopThread();
				}
				std::this_thread::sleep_for(std::chrono::seconds(2));
				AttCam().startThread();
			}
		}
		else
		{
			std::cout << "Using Embedded. EmbCam: " << EmbCam().isRunning() << std::endl;
			if(!EmbCam().isRunning())
			{
				if(AttCam().isRunning())
				{
					std::cout << "Stopping Attached..." << std::endl;
					AttCam().stopThread();
				}
				std::this_thread::sleep_for(std::chrono::seconds(2));
				EmbCam().startThread();
			}
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));		

	}

	return true;
}

bool VideoThread::isStopped()
{
	return m_stopThread;
}
