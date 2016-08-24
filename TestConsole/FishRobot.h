#ifndef _FISH_ENUMERATION_H_
#define _FISH_ENUMERATION_H_

#include "FishEnumerations.h"
#include "FishRobotSerialPort.h"

class FishRobot
{

private:
	unsigned short int _fishID;
	
	bool _isConnected;

	FishDirections _direction;

	FishSpeed _speed;

	FishRobotSerialPort *_serialPort;
protected:
	char* packCommand(char command);

	void sendCommand(char* command);
public:
	
	FishRobot(unsigned short int fishID, FishRobotSerialPort *serialPort);

	bool connectFish();

	//Set fish's direction.
	//If successfully set, returns true, otherwise returns false.
	bool setDirection(FishDirections direction);

	const FishDirections getFishDirection();

	//Set fish swimming speed.
	//If successfully set, returns true, otherwise returns false.
	bool setSpeed(FishSpeed speed);

	const FishSpeed getSpeed();

	~FishRobot();
};

#endif