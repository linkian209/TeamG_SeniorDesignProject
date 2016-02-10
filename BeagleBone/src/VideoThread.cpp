#include "VideoThread.hpp"
#include "BluetoothManager.hpp"
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
		// Package Video

		// Send Video
		while(!BTMgr().Lock());
		// Send feed
		BTMgr().Unlock();
	}

	return true;
}
