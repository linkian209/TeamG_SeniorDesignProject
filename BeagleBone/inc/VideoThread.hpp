/*********************
 * Video Thread      *
 * Author: Ian Drake *
 * Copyright: 2016   *
 *********************/
#ifndef VIDEOTHREAD__HPP
#define VIDEOTHREAD__HPP

#include <thread>

class VideoThread
{
	private:
		// Thread variables
		std::thread m_thread;
		bool m_stopThread = false; // Thread stopper defaults to false

	public:
		// Constructor and Destructor
		VideoThread();
		~VideoThread();
		// Thread Functions
		void startThread();
		void stopThread();
		bool ThreadMain();
};

#endif
