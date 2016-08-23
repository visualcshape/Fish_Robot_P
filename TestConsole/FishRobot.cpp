#include "stdafx.h"
#include "FishRobot.h"


char* FishRobot::packCommand(char command)
{
	const char HEAD = 0xaa;
	const char FINAL = 0xfc;
	const char FISH_ID = 0x90 + this->_fishID;
	//malloc to reserve the memory for packed command.
	char* ret = (char*)malloc(4 * sizeof(char));
	ret[0] = HEAD;
	ret[1] = FISH_ID;
	ret[2] = command;
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
	char command = 0;
	const char DIRECTION_BASE_COMMAND = 0xe0;
	command = DIRECTION_BASE_COMMAND+ direction;
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
	return this->_direction;
}

bool FishRobot::setSpeed(FishSpeed speed)
{
	const char SPEED_BASE_COMMAND = 0xd0;
	char command = 0;
	command = SPEED_BASE_COMMAND + speed;
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
	return this->_speed;
}

FishRobot::~FishRobot()
{
}
