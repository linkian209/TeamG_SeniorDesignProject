/*********************
 * Base Thread       *
 * Author: Ian Drake *
 * Copyright: 2016   *
 *********************/
#ifndef USERTHREAD__HPP
#define USERTHREAD__HPP

#include <thread>

class UserThread
{
	private:
		// Thread variables
		std::thread m_thread;
		bool m_stopThread = false; // Thread stopper defaults to false

	public:
		// Constructor and Destructor
		UserThread();
		~UserThread();
		// Thread Functions
		void startThread();
		void stopThread();
		bool ThreadMain();
		bool isStopped();
};

#endif
