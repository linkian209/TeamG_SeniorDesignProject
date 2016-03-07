/*********************
 * Base Thread       *
 * Author: Ian Drake *
 * Copyright: 2016   *
 *********************/
#ifndef USERTHREAD__HPP
#define USERTHREAD__HPP

#include <thread>

enum PacketType
{
	PWMPacket	= 1,
	CameraPacket	= 2,
	BadPacket	= 3
};

class UserThread
{
	private:
		// Thread variables
		std::thread m_thread;
		bool m_stopThread = false; // Thread stopper defaults to false

		PacketType decodePacket(std::string packet);
		bool decodePWMPacket(std::string packet);
		bool decodeCameraPacket(std::string packet);

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
