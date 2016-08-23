#include "stdafx.h"
#include "FishRobot.h"


char* FishRobot::packCommand(char* command)
{
	const char HEAD = 0xaa;
	const char FINAL = 0xfc;
	char* ret = (char*)malloc(4 * sizeof(char));
	ret[0] = HEAD;
	ret[1] = command[0];
	ret[2] = command[1];
	ret[3] = FINAL;
	return ret;
}

void FishRobot::sendCommand(char* command)
{
	this->_serialPort->write(command);
}

FishRobot::FishRobot(unsigned short int fishID, FishRobotSerialPort* serialPort):_fishID(fishID), _serialPort(serialPort), _isConnected(false)
{
}

bool FishRobot::connectFish()
{
	bool opened = this->_serialPort->open();
	return opened;
}

bool FishRobot::setDirection(FishDirections direction)
{
	char command[2] = {0};
	command[0] = 0x90 + this->_fishID;
	command[1] = 0xe0 + direction;
	char* packedCommand = this->packCommand(command);
	this->sendCommand(packedCommand);
	this->_direction = direction;
	//free allocated memory
	free(packedCommand);
	//stub return for future use
	return false;
}

const FishDirections FishRobot::getFishDirection()
{
	return FishDirections();
}

bool FishRobot::setSpeed(FishSpeed speed)
{
	char command[2] = {0};
	command[0] = 0x90 + this->_fishID;
	command[1] = 0xd0 + speed;
	char* packedCommand = this->packCommand(command);
	this->sendCommand(packedCommand);
	this->_speed = speed;
	//free allocated memory
	free(packedCommand);
	//stub return for futre use
	return false;
}


const FishSpeed FishRobot::getSpeed()
{
	return FishSpeed();
}

FishRobot::~FishRobot()
{
}
