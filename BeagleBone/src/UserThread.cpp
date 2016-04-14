#include "UserThread.hpp"
#include "BluetoothManager.hpp"
#include "PWMManager.hpp"
#include "AttachedCamera.hpp"
#include <iostream>
#include <thread>
#include <chrono>

UserThread::UserThread() : m_thread()
{

}

UserThread::~UserThread()
{

}

void UserThread::startThread()
{
	m_thread = std::thread(&UserThread::ThreadMain,this);
}

void UserThread::stopThread()
{
	m_stopThread = true;
	if(m_thread.joinable())
	{
		m_thread.join();
	}

}

bool UserThread::ThreadMain()
{
	while(!m_stopThread)
	{
		// Wait for a new packet
		while(!BTMgr().checkPackets());

		while(BTMgr().checkPackets())
		{
			// Decode Packet
			std::string pack = BTMgr().readString();
			PacketType type = decodePacket(pack);

			bool response = false;

			switch(type)
			{
				case PWMPacket:
					response = decodePWMPacket(pack);
					break;
				case CameraPacket:
					response = decodeCameraPacket(pack);
					break;
				case SwitchPacket:
					response = decodeSwitchPacket(pack);
					break;
				case BadPacket:
					// Ignore this Packet
					continue;
				default:
					// What????
					continue;
			}
			// Create Response
			std::string ackPack = "$%RESPONSE%";
			ackPack +=  response ? "TRUE" : "FALSE";
			ackPack += "#\n";
			// Send packet return packet
			while(!BTMgr().Lock());
			// Send it
			BTMgr().sendString(ackPack);
			BTMgr().Unlock();
		}
	}

	return true;
}

bool UserThread::isStopped()
{
	return m_stopThread;
}

// Packets look like this:
// $[TYPE][DATA......]#
// They start and end with '$'
PacketType UserThread::decodePacket(std::string packet)
{
	std::size_t found = packet.find("%PWM");

	// PWM Packet
	if(found != std::string::npos)
	{
		return PWMPacket;
	}

	found = packet.find("%CAMERA");

	// Camera Packet
	if(found != std::string::npos)
	{
		return CameraPacket;
	}

	found = packet.find("%CHANGE");

	// Switch Packet
	if(found != std::string::npos)
	{
		return SwitchPacket;
	}

	// Else return bad packet
	return BadPacket;
}

// PWM Packet
// $%PWM%PITCH[ANGLE]%YAW[ANGLE]#
bool UserThread::decodePWMPacket(std::string packet)
{
	try
	{
		// Get Locations
		std::size_t start = packet.find("$");
		std::size_t stop = packet.substr(start+1).find("#") + 1;
		std::size_t pitchLoc = packet.find("%PITCH");
		std::size_t yawLoc = packet.find("%YAW");

		// Strings of the new angles, defaults to current angles
		std::string pitch = std::to_string(PWMMgr().getCurrentPitch());
		std::string yaw = std::to_string(PWMMgr().getCurrentYaw());

		// Return value, just to know if we got a good packet and made changes accordingly
		bool retval = true;

		if(pitchLoc != std::string::npos && yawLoc != std::string::npos)
		{
			// Length is the difference between the beginning of the angle (pitchLoc + 6)
			// and beginning of %YAW
			try
			{
				pitch = packet.substr(pitchLoc + 6,(yawLoc - (pitchLoc + 6)));
			}
			catch(...)
			{
				std::cerr << "Bad set!" << std::endl;
			}
		}
		else
		{
			retval = false;
		}

		if(stop != std::string::npos)
		{
			// Length of Yaw is beginning of angle until final '$'
			try
			{
				yaw = packet.substr(yawLoc + 4,(stop - (yawLoc + 4)));
			}
			catch(...)
			{
				std::cerr << "Bad Cast!" << std::endl;
			}
		}
		else
		{
			retval = false;	
		}

		// Try to change angles
		try
		{
			PWMMgr().setYaw(std::stof(yaw));
		}
		catch(std::bad_cast& bc)
		{
			std::cerr << "bad_cast caught: " << bc.what() << std::endl;
		}

		try
		{
			PWMMgr().setPitch(std::stof(pitch));
		}
		catch(std::bad_cast& bc)
		{
			std::cerr << "bad_cast caught: " << bc.what() << std::endl;
		}

		return retval;
	
	}
	catch(...)
	{
		return false;
	}
}

// Camera Packet
// $%CAMERA%DOWNLOAD[True '1' or false '0']#
bool UserThread::decodeCameraPacket(std::string packet)
{
	try
	{
		// See if we need to send the picture we take
		std::size_t down = packet.find("%DOWNLOAD");
		bool download = false;
		bool retval = true;

		if(down != std::string::npos)
		{
			std::string temp = packet.substr(down + 9, 1);

			download = (temp == "1") ? true : false;
		}

		if(download)
		{
			// Capture and Download
			while(!AttCam().Lock());
			bool running = AttCam().isRunning();
			if(running)
			{
				AttCam().Halt();
				AttCam().stopThread();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			retval = AttCam().takePictureAndDownload();
			if(running)
			{
				AttCam().startThread();
				AttCam().Start();
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			AttCam().Unlock();
		
		}
		else
		{
			// Just Capture
			while(!AttCam().Lock());
			bool running = AttCam().isRunning();
			if(running)
			{
				AttCam().Halt();
				AttCam().stopThread();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			retval = AttCam().takePicture();
			if(running)
			{
				AttCam().startThread();
				AttCam().Start();
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			AttCam().Unlock();
		}
	
		return retval;
	}
	catch(...)
	{
		return false;
	}
}

// Switch Packet
// $%CHANGE[Embedded '1' or Attached '0']#
bool UserThread::decodeSwitchPacket(std::string packet)
{
	try
	{
		// Switch the camera we are using
		std::size_t change = packet.find("E");

		if(change != std::string::npos)
		{
			std::string temp = packet.substr(change + 1,1);
		
			while(!AttCam().Lock());
			AttCam().switchCamera(((temp == "1") ? true : false));
			AttCam().Unlock();

			return true;
		}

		return false;
	}
	catch(...)
	{
		return false;
	}
}
