/***************************
 * Embedded Camera Control *
 * Author: Ian Drake       *
 * Copyright 2016          *
 ***************************/
#ifndef EMBEDDEDCAMERA_HPP
#define EMBEDDEDCAMERA_HPP

#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>

// Embedded Camera Class
class EmbeddedCamera
{
	public:
		// Singleton Access Function
		friend EmbeddedCamera& EmbCam()
		{
			static EmbeddedCamera theCamera;
			return theCamera;
		}

		// Mutex
		bool Lock() { return lock.try_lock(); }
		void Unlock() { lock.unlock(); }

		// Camera Functions
		void test();

		// Thread Functions
		void startThread();
		void stopThread();
		bool ThreadMain();
		bool isRunning() { return m_threadRunning; }

	private:
		// Constructor and Destructor
		EmbeddedCamera();
		~EmbeddedCamera();
		
		// Thread
		std::thread m_thread;
		bool m_stopThread = false;
		bool m_threadRunning = false;

		// Mutex
		std::mutex lock;
		bool m_Cam;

};

//Declare Singleton Access Function
EmbeddedCamera& EmbCam();

#endif
