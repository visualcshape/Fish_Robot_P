#include "stdafx.h"
#include "FishRobot.h"
#include "Utility.h"
#include <chrono>
#include <thread>

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

FishRobot::FishRobot(unsigned short int fishID, RFTransmittorSerialPort* serialPort):_fishID(fishID), _serialPort(serialPort), _isConnected(false)
{
}

bool FishRobot::connectFish()
{
	bool opened = this->_serialPort->open();
	this->_isConnected = opened;
	return opened;
}

bool FishRobot::setDirection(FishDirections direction)
{
	char command = 0;
	const char DIRECTION_BASE_COMMAND = 0xe0;
	//Check range if in range
	if(!Utility::isInRange(FishDirections::RIGHT_6, FishDirections::LEFT_6, direction) || !this->_isConnected)
		return false;
	command = DIRECTION_BASE_COMMAND+ direction;
	char* packedCommand = this->packCommand(command);
	this->sendCommand(packedCommand);
	this->_direction = direction;
	//free allocated memory
	free(packedCommand);

	return true;
}

const FishDirections FishRobot::getFishDirection()
{
	return this->_direction;
}

bool FishRobot::setSpeed(FishSpeed speed)
{
	const char SPEED_BASE_COMMAND = 0xd0;
	char command = 0;
	//Check speed in range.
	if (!Utility::isInRange(FishSpeed::LEVEL_15, FishSpeed::LEVEL_1, speed) || !this->_isConnected)
		return false;
	command = SPEED_BASE_COMMAND + speed;
	char* packedCommand = this->packCommand(command);
	this->sendCommand(packedCommand);
	this->_speed = speed;
	//free allocated memory
	free(packedCommand);
	//stub return for futre use
	return true;
}


const FishSpeed FishRobot::getSpeed()
{
	return this->_speed;
}

bool FishRobot::enableJoint(bool joint1, bool joint2, bool joint3, bool joint4)
{
	if (!this->_isConnected)
		return false;
	const char ENABLE_JOINT_BASE_COMMAND = 0x60;
	char result = 0x0;
	char command = 0x0;
	if (joint1)
		result |= ENABLE_JOINT_1;
	if (joint2)
		result |= ENABLE_JOINT_2;
	if (joint3)
		result |= ENABLE_JOINT_3;
	if (joint4)
		result |= ENABLE_JOINT_4;
	command = ENABLE_JOINT_BASE_COMMAND + result;
	char* packedCommand = this->packCommand(command);
	this->sendCommand(packedCommand);
	this->_joint1Enable = joint1;
	this->_joint2Enable = joint2;
	this->_joint3Enable = joint3;
	this->_joint4Enable = joint4;
	//free allocated memory.
	free(packedCommand);

	return true;
}

const std::array<bool, 4> FishRobot::getJointStatus()
{
	return{_joint1Enable, _joint2Enable, _joint3Enable, _joint4Enable};
}

bool FishRobot::setDepthControl(int depth)
{
	if (!Utility::isInRange(MAX_DEPTH, MIN_DEPTH, depth) || !this->_isConnected)
		return false;

	const char DEPTH_CONTROL_COMMAND_BASE = 0x40;
	char command = DEPTH_CONTROL_COMMAND_BASE + depth;
	char* packedCommand = this->packCommand(command);
	this->sendCommand(packedCommand);
	//
	free(packedCommand);
	
	return true;
}

int FishRobot::getDepthControl()
{
	return this->_depth;
}

bool FishRobot::stopActions()
{
	this->setDirection(FishDirections::MID);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	this->setSpeed(FishSpeed::LEVEL_1);
	return false;
}

void FishRobot::printFishConfiguration()
{
	if (!this->_isConnected) {
		printf("Please connect fish first!\n");
	}
	
	const char GET_CONFIGURATION_COMMAND = 0x55;
	char* packedCommand = this->packCommand(GET_CONFIGURATION_COMMAND);
	this->sendCommand(packedCommand);

}

FishRobot::~FishRobot()
{
	this->stopActions();
}
