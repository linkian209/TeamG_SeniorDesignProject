/***************************
 * Attached Camera Control *
 * Author: Ian Drake       *
 * Copyright 2016          *
 ***************************/
#ifndef ATTACHEDCAMERA_HPP
#define ATTACHEDCAMERA_HPP

#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>

// Attached Camera Class
class AttachedCamera
{
	public:
		// Singleton Access Function
		friend AttachedCamera& AttCam()
		{
			static AttachedCamera theCamera;
			return theCamera;
		}

		// Mutex
		std::mutex lock;
		bool Lock() { return lock.try_lock(); }
		void Unlock() { lock.unlock(); }

		// Camera Functions
		bool takePicture();
		bool takePictureAndDownload();

		void test();

		// Thread Stuff
		void startThread();
		void stopThread();
		bool isRunning() { return m_threadRunning; }
		bool ThreadMain();
		bool useEmbedded() { return m_useEmbedded; }
		void switchCamera(bool embedded) { m_useEmbedded = embedded; }
		void Halt() { m_run = false; }
		void Start() { m_run = true; }
		bool GoOrNo() { return m_run; }
		

	private:
		// Constructor and Destructor
		AttachedCamera();
		~AttachedCamera();

		// Picture Stuff
		int m_currentPic = 0;

		// Thread Stuff
		std::thread m_thread;
		bool m_stopThread = false;
		bool m_threadRunning = false;
		bool m_useEmbedded = false;
		bool m_run = true;
};

//Declare Singleton Access Function
AttachedCamera& AttCam();

#endif
