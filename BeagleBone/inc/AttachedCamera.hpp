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

	private:
		// Constructor and Destructor
		AttachedCamera();
		~AttachedCamera();
};

//Declare Singleton Access Function
AttachedCamera& AttCam();

#endif
