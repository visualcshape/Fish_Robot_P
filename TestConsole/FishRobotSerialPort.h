#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "AbstractSerialPort.h"
class FishRobotSerialPort : public  AbstractSerialPort{
private:
	HANDLE comHandle;

	COMSTAT comStatus;

	DWORD errors;

	LPCWSTR portName;

	bool isOpen;
	
	void configuration();
public:
	FishRobotSerialPort(LPCWSTR portName);

	virtual ~FishRobotSerialPort();

	bool open();

	bool write(char* buffer, unsigned int nbChar);

	int read(char* buffer, unsigned int nbChar);
};

#endif