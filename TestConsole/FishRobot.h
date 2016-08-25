#ifndef _FISH_ENUMERATION_H_
#define _FISH_ENUMERATION_H_

#include "FishEnumerations.h"
#include "RFTransmittorSerialPort.h"
#include <array>

class FishRobot
{
private:
	unsigned short int _fishID;
	
	bool _isConnected;

	FishDirections _direction;

	FishSpeed _speed;

	RFTransmittorSerialPort *_serialPort;

	//Default enable status = all enable
	bool _joint1Enable = true;

	bool _joint2Enable = true;

	bool _joint3Enable = true;

	bool _joint4Enable = true;

	//Default depth (15)
	int _depth = 15;
protected:
	char* packCommand(char command);

	void sendCommand(char* command);
public:
	
	FishRobot(unsigned short int fishID, RFTransmittorSerialPort *serialPort);

	bool connectFish();

	//Set fish's direction.
	//If successfully set, returns true, otherwise returns false.
	bool setDirection(FishDirections direction);

	const FishDirections getFishDirection();

	//Set fish swimming speed.
	//If successfully set, returns true, otherwise returns false.
	bool setSpeed(FishSpeed speed);

	const FishSpeed getSpeed();

	//Enable joint(s), default is all enabled.
	//Please refer to readme.md
	bool enableJoint(bool joint1, bool joint2, bool joint3, bool joint4);

	//Returns an array that contains enable status of 4 joints. (std array of boolean)
	const std::array<bool,4> getJointStatus();

	//Control depth of the fish, range 11 ~ 150, or 0 = disable.
	bool setDepthControl(int depth);

	int getDepthControl();

	bool stopActions();

	void printFishConfiguration();

	~FishRobot();
};

#endif