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
	while(!m_stopThread)
	{
		while(!AttCam().Lock());
		m_useEmbedded = AttCam().useEmbedded();
		AttCam().Unlock();
		if(!m_useEmbedded)
		{
			if(!AttCam().isRunning())
			{
				if(EmbCam().isRunning())
				{
					EmbCam().stopThread();
				}
				AttCam().startThread();
			}
		}
		else
		{
			if(!EmbCam().isRunning())
			{
				if(AttCam().isRunning())
				{
					AttCam().stopThread();
				}
				EmbCam().startThread();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));		

	}

	return true;
}

bool VideoThread::isStopped()
{
	return m_stopThread;
}
